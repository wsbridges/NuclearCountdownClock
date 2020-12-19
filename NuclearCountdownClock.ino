#include <Wire.h>
#include "Displays.h"
#include "Clock.h"

Displays* display;
Clock* clock;

//Set which pin correlates to which input on
//the Arduino
const int SETUP_BUTTON=9;
const int PLUS_BUTTON=10;
const int MINUS_BUTTON=11;
const int COUNTDOWN_SWITCH=12;

//Sets interval (in ms) to poll for button presses
const uint16_t BUTTON_INTERVAL = 200;

//Sets interval (in ms) to poll Real Time Clock
const uint16_t CLOCK_INTERVAL = 250;

//Requires Set Button to be held for 2 seconds (2000ms) 
//before it turns the setup menu on
const uint16_t SETUP_BUTTON_INTERVAL = 2000;

//Specifies if we are in the countdown clock
//mode or regular clock mode
bool countdownMode = false;

//Specifies if the menu should be displayed
bool setupMode = false;

//Stores whether button was pressed vs held
bool setupButtonPressed = false;

//Stores the last time the RTC was polled
unsigned long lastClockPoll = 0;

//Stores the current time in milliseconds
unsigned long currMillis = 0;

//Stores the time in milliseconds of the last instance
//the Set button was read as NOT pressed
unsigned long lastSetupLow = 0;

//Stores the time in milliseconds of the last instance
//the Set button was read as pressed
unsigned long lastSetupHigh = 0;

//Stores the time in milliseconds of the last instance
//the Plus button was read as pressed
unsigned long lastPlusHigh = 0;

//Stores the time in milliseconds of the last instance
//the Minus button was read as pressed
unsigned long lastMinusHigh = 0;

bool lastCountdownHigh = false;

void setup() {
  //For debugging
  Serial.begin(57600);

  //Initialize displays and RTC
  display = new Displays();
  clock = new Clock();

  //If RTC could not be read, display an error and abort
  if(!clock->initialized()) {
    display->write("  RTC    ERROR  ");
    delay(5000);
    abort();
  }

  //Initialize the buttons
  pinMode(SETUP_BUTTON, INPUT);
  pinMode(PLUS_BUTTON, INPUT);
  pinMode(MINUS_BUTTON, INPUT);
  pinMode(COUNTDOWN_SWITCH, INPUT);
}

void loop() {
  //Get current time in milliseconds
  currMillis = millis();

  //Read the state of all buttons and switches
  readSecretCode();
  readCountdownSwitch();
  readPlusButton();
  readMinusButton();
  readSetButton();

  //Determine which state we are in. Possibilities are:
  //  1. Countdown Clock Mode
  //  2. Regular Clock Mode
  //  3. Countdown Clock Setup Menu
  //  4. Regular Clock Setup Menu
  if(!setupMode && countdownMode) {
    //Serial.println("Display Countdown"); //debug message
    displayCountdown();
  }
  else if(!setupMode && !countdownMode) {
    //Serial.println("Display Time"); //debug message
    displayTime();
  }
  else if(setupMode && countdownMode) {
    displayCountdownMenu();
  }
  else {
    displayTimeMenu();
  }
}

//Top secret code. If you push all 3 buttons at once,
//get a super cool message
void readSecretCode() {
  if(digitalRead(MINUS_BUTTON) == HIGH && digitalRead(PLUS_BUTTON) == HIGH && digitalRead(SETUP_BUTTON) == HIGH) {
    display->write("  BILL    RULES ");
    delay(3000);

    //Blink FAV SON-IN-LAW 6 times
    for(int i = 0; i < 6; i++) {
      display->write("                ");
      delay(250);
      display->write("FAV SON- IN-LAW ");
      delay(250);
    }
  }
}

//Reads the state of the Launch switch.
//NOTE: this may still read LOW even if the Launch Switch
//      is up if the Initiate key is not engaged. This is
//      because the Initiate key provides voltage to the
//      Launch Switch
void readCountdownSwitch() {
  if(digitalRead(COUNTDOWN_SWITCH) == HIGH) {
    //Serial.println("Countdown Switch"); //debug message
    countdownMode = true;
    
    //exit setup if we switch in or out of countdown mode
    if(!lastCountdownHigh && setupMode) {
      setupMode = false;
    }
    lastCountdownHigh = true;
  }
  else {
    countdownMode = false;

    //exit setup if we switch in or out of countdown mode
    if(lastCountdownHigh && setupMode) {
      setupMode = false;
    }
    lastCountdownHigh = false;
  }
}

//Reads the state of the Minus button
void readMinusButton() {
  if(digitalRead(MINUS_BUTTON) == HIGH) {
    //Serial.println("Minus button"); //debug message
    //Make sure some time time has passed since the last read to
    //prevent multiple presses from registering
    if(currMillis - lastMinusHigh >= BUTTON_INTERVAL) {
      if(setupMode) {
        char displayBuff[16]; //Stores text to display
        if(!countdownMode) {
          clock->decreaseTime(displayBuff);
        }
        else {
          clock->decreaseCountdownTime(displayBuff);
        }
        display->write(displayBuff); //Show updated value on display
      }
      //Store the time we registered the button press
      lastMinusHigh = currMillis;
    }
  }
}

//Reads the state of the Plus button
void readPlusButton() {
  if(digitalRead(PLUS_BUTTON) == HIGH) {
    //Serial.println("Plus button"); //debug message
    //Make sure some time time has passed since the last read to
    //prevent multiple presses from registering
    if(currMillis - lastPlusHigh >= BUTTON_INTERVAL) {
      if(setupMode) {
        char displayBuff[16]; //Stores text to display
        if(!countdownMode) {
          clock->increaseTime(displayBuff);
        }
        else {
          clock->increaseCountdownTime(displayBuff);
        }
        display->write(displayBuff); //Show updated value on display
      }
      //Store the time we registered the button press
      lastPlusHigh = currMillis;
    }
  }
}

//Reads the state of the Set button
void readSetButton() {
  if(digitalRead(SETUP_BUTTON) == HIGH) {
    //Serial.println("Setup Button"); //debug message
    //Only enter or exit setup mode if Set button has been held for 2 seconds
    if(currMillis - lastSetupLow >= SETUP_BUTTON_INTERVAL) {
      setupMode = !setupMode; //toggle setup mode
      clock->resetMenu(); //reset back to start of menu
      
      //Display splash screen for 2 seconds
      if(setupMode && !countdownMode) {
        display->write("  TIME   SETUP  ");
        delay(2000);
      }
      else if(setupMode && countdownMode) {
        display->write(" RETIRE DT SETUP");
        delay(2000);
      } 
      else {
        display->write(" SETUP   SAVED  ");
        delay(1000);
      }
      setupButtonPressed = false;
    }
    else {
      //Save that the Set button was pressed
      lastSetupHigh = currMillis;
      setupButtonPressed = true;
    }
  }
  else {
    //Save when button was released
    lastSetupLow = currMillis;

    //If set button was pressed, but not held for 2 sec, and we
    //in Setup Mode, advance the menu
    if(setupMode && setupButtonPressed && currMillis - lastSetupHigh >= BUTTON_INTERVAL) {
      clock->nextMenuItem(countdownMode);
      setupButtonPressed = false;
    }

  }
}

//Displays countdown time
void displayCountdown() {
  //Poll clock every 200 ms. Do not want to poll the RTC every loop or 
  //the clock will get bogged down and time will not be accurate
  if(currMillis - lastClockPoll >= CLOCK_INTERVAL) {
    char displayBuff[16]; //Stores text to display
    bool countdownPassed = clock->getCountdownTime(displayBuff); //Get countdown time to display
    if(countdownPassed) {
      display->displayCongratsAnimation();
    }
    else {
      display->write(displayBuff); //Display countdown time
    }
    lastClockPoll = currMillis; //Save when we polled the clock
  }
}

//Displays time like a normal clock
void displayTime() {
  //Poll clock every 200 ms. Do not want to poll the RTC every loop or 
  //the clock will get bogged down and time will not be accurate
  //Serial.println((currMillis - lastClockPoll));
  if((currMillis - lastClockPoll) >= CLOCK_INTERVAL) {
    //Serial.println("Polling RTC"); //debug message
    char displayBuff[16]; //Stores text to display
    clock->getCurrentTime(displayBuff); //Get time to display
    display->write(displayBuff); //Display time
    lastClockPoll = currMillis; //Save when we polled the clock
  }
}

//Display Setup Menu for normal clock mode
void displayTimeMenu() {
  char displayBuff[16]; //Stores text to display
  clock->showTimeSetup(displayBuff);
  display->write(displayBuff); //Display menu
}

//Display Setup Menu for Countdown mode
void displayCountdownMenu() {
  char displayBuff[16]; //Stores text to display
  clock->showCountdownSetup(displayBuff);
  display->write(displayBuff); //Display menu
}
