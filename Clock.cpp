#include "Clock.h"
#include "Displays.h"
#include "Brightness.h"

//Display text for month names
const char* Clock::MONTH_NAME[]={"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};

Clock::Clock() {
  //initialize the real time clock
  if(!rtc.begin()) {
    error = true;
  }
  else 
  {
    error = false;
    if (rtc.lostPower()) {
      // When time needs to be set on a new device, or after a power loss, the
      // following line sets the RTC Christmas 2020
      rtc.adjust(DateTime(2020,12,25,0,0,0));
    }
    //Retirement date: Jan 5 2022 6:00 AM
    retireDate = DateTime(2022, 1, 5, 6, 0, 0);
    militaryTime = false;
    resetMenu(); //initializes menu
  }
}

//Returns true if communication is established with the
//RTC
bool Clock::initialized() {
  return !error;
}

//Resets menu to the first option which is the
//Year adjustment
void Clock::resetMenu() {
  setupMenuCounter = 0;
}

//Advance the menu to the next item
void Clock::nextMenuItem(bool countdownMode) {
  //Setup menu has 8 Menu items
  setupMenuCounter = (setupMenuCounter + 1) % 8;
}

//Helper method to make main code more readable.
//Adds 1 to the value of the current menu item
void Clock::increaseCountdownTime(char* displayBuff) {
  adjustCountdownTime(displayBuff, true, false);
}

//Helper method to make main code more readable.
//Subtracts 1 from the value of the current menu item
void Clock::decreaseCountdownTime(char* displayBuff) {
  adjustCountdownTime(displayBuff, false, true);
}

//Helper method to make main code more readable.
//Shows Countdown setup menu without changing values
void Clock::showCountdownSetup(char* displayBuff) {
  adjustCountdownTime(displayBuff, false, false);
}

//Displays Countdown setup menu and processes adjustments
void Clock::adjustCountdownTime(char* displayBuff, bool plus, bool minus) {
  retireDate = setupMenu(displayBuff, retireDate, plus, minus);
}

//Helper method to make main code more readable
//Adds 1 to the value of the current menu item
void Clock::increaseTime(char* displayBuff) {
  adjustTime(displayBuff, true, false);
}

//Helper method to make main code more readable
//Subtracts 1 from the value of the current menu item
void Clock::decreaseTime(char* displayBuff) {
  adjustTime(displayBuff, false, true);
}

//Helper method to make main code more readable.
//Shows Time setup menu without changing values
void Clock::showTimeSetup(char* displayBuff) {
  adjustTime(displayBuff, false, false);
}

//Displays the Setup Menu and makes changes from menu to the RTC
void Clock::adjustTime(char* displayBuff, bool plus, bool minus) {
  DateTime curTime = rtc.now();
  DateTime updatedTime = setupMenu(displayBuff, curTime, plus, minus);
  rtc.adjust(updatedTime);
}

//This is the heart of the Setup Menu for both regular Clock Mode
//and Countdown Mode. The date passed in is what is being manipulated
//and then returned. For Clock Mode adjustment, the time is passed in
//from the RTC. For Countdown Mode adjustment, the time is passed in 
//from the retireDate member variable. If plus is true, adds 1 to current
//value. If minus is true, subtracts 1 from current value. If neither
//are true, it just displays the menu which is passed back via displayBuff
DateTime Clock::setupMenu(char* displayBuff, DateTime date, bool plus, bool minus) {
  uint16_t year = date.year();
  uint8_t month = date.month();
  uint8_t day = date.day();
  uint8_t hour = date.hour();
  uint8_t minute = date.minute();
  uint8_t second = date.second();
  
  switch(setupMenuCounter) {
    
    //Year adjustment
    case 0:
    {
      sprintf(displayBuff, "  YEAR    %04d  ", year);
      bool yearChanged = false;
      if(plus) {
        year++;
        yearChanged = true;
      }
      else if(minus) {
        year--;
        yearChanged = true;
      }
      if(yearChanged) {
        //prevent invalid date from adjusting time on leap day
        if(month == 2 && day == 29) {
          day = 28;
        }
      }
      break;
    }
    
    //Month adjustment
    case 1:
    {
      sprintf(displayBuff, " MONTH    %s   ", MONTH_NAME[month - 1]);
      bool monthChanged = false;
      if(plus) {
        month++;
        //DEC->JAN
        if(month == 13) {
          month = 1;
        }
        monthChanged = true;
      }
      else if(minus) {
        month--;
        //JAN->DEC
        if(month == 0) {
          month = 12;
        }
        monthChanged = true;
      }
      if(monthChanged) {
        //prevent invalid date from switch from month with last day of 31
        //to a month with a last day of less than 31
        if(day > determineMaxDayOfMonth(month, year)) {
          day = determineMaxDayOfMonth(month, year);
        }
      }
      break;
    }

    //Day adjustment
    case 2:
    {
      sprintf(displayBuff, "  DAY      %02d   ", day);
      if(plus) {
        day++;
        //last day of month->1
        if(day > determineMaxDayOfMonth(month, year)) {
          day = 1;
        }
      }
      if(minus) {
        day--;
        //1->last day of month
        if(day == 0) {
          day = determineMaxDayOfMonth(month, year);
        }
      }
      break;
    }
    
    //Military time adjustment
    case 3:
    {
      sprintf(displayBuff, " 12/24H    %02d   ", (militaryTime ? 24 : 12));
      //toggle military time
      if(plus || minus) {
        militaryTime = !militaryTime;
      }
      break;
    }

    //Hour adjustment
    case 4:
    {
      if(militaryTime) {
        sprintf(displayBuff, "  HOUR     %02d   ", hour);
      }
      else {
        uint8_t twelveHour = hour;
        bool pm = false;
        if(twelveHour >= 12) {
          pm = true;
          if(twelveHour >= 13) {
            twelveHour -= 12;
          }
        }
        else if(hour == 0) {
          twelveHour = 12;
        }
        sprintf(displayBuff, "  HOUR    %02d%s  ", twelveHour, (pm ? "PM" : "AM"));
      }

      //Perform all operations on 24 hour time, then when the loop comes 
      //back around the above code will handle the display of the time
      //in 12H or 24H
      if(plus) {
        hour++;
        //23->0
        if(hour == 24) {
          hour = 0;
        }
      }
      if(minus) {
        //0->23
        //doing it this way since hour is unsigned and can't be negative
        if(hour == 0) {
          hour = 24;
        }
        hour--;
      }
      break;
    }

    //Minute adjustment
    case 5:
    {
      sprintf(displayBuff, " MINUTE    %02d   ", minute);
      if(plus) {
        minute++;
        //59->0
        if(minute == 60) {
          minute = 0;
        }
      }
      if(minus) {
        //0->59
        //doing it this way since minute is unsigned and can't be negative
        if(minute == 0) {
          minute = 60;
        }
        minute--;
      }
      break;
    }

    //Second adjustment
    case 6:
    {
      sprintf(displayBuff, " SECOND    %02d   ", second);
      if(plus) {
        second++;
        //59->0
        if(second == 60) {
          second = 0;
        }
      }
      if(minus) {
        //0->59
        //doing it this way since minute is unsigned and can't be negative
        if(second == 0) {
          second = 60;
        }
        second--;
      }
      break;
    }

    //Brightness adjustment
    case 7:
    {
      changeBrightness(displayBuff, plus, minus);
      break;
    }
  }
  return DateTime(year, month, day, hour, minute, second);
}

void Clock::changeBrightness(char* displayBuff, bool plus, bool minus) {
  sprintf(displayBuff, "BRGHTNSS   %02d   ", Brightness::BRIGHTNESS);
      if(plus) {
        Brightness::BRIGHTNESS++;
        //15->0
        if(Brightness::BRIGHTNESS > 15) {
          Brightness::BRIGHTNESS = 0;
        }
        //This tells the display to update the brightness
        Brightness::BRIGHTNESS_CHANGED = true;
      }
      if(minus) {
        //0->15
        //Doing it like this because BRIGHTNESS is unsigned and can't be negative
        if(Brightness::BRIGHTNESS == 0) {
          Brightness::BRIGHTNESS = 16;
        }
        Brightness::BRIGHTNESS--;
        //This tells the display to update the brightness
        Brightness::BRIGHTNESS_CHANGED = true;
      }
}

//Determines the last day of the Month
uint8_t Clock::determineMaxDayOfMonth(uint8_t month, uint16_t year) {
  //Jan, Mar, May, July, Aug, Oct, and Dec have 31 days
  if(month == 1 ||
     month == 3 ||
     month == 5 ||
     month == 7 ||
     month == 8 ||
     month == 10 ||
     month == 12 ) {
    return 31;
  }
  //Apr, June, Sept, and Nov have 30 days
  else if(month == 4 ||
          month == 6 ||
          month == 9 ||
          month == 11) {
    return 30;
  }
  //Determine leap year
  else if(month == 2) {
    if(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
      return 29;
    }
    else {
      return 28;
    }
  }
}

//Displays countdown
bool Clock::getCountdownTime(char* displayBuff) {
  DateTime curTime = rtc.now();
  if(retireDate.unixtime() > curTime.unixtime()){
    //subtract seconds
    int8_t secDiff = retireDate.second() - curTime.second();

    //indicates if we are borrowing one from the next
    //value to do the subtraction
    bool sub1 = false;
    if(secDiff < 0) {
      //borrow from minutes
      secDiff += 60;
      sub1 = true;
    }

    //subtract minutes
    int8_t minDiff = retireDate.minute() - curTime.minute();
    //seconds subtraction had to borrow 
    if(sub1) {
      minDiff--;
    }
    sub1 = false;
    if(minDiff < 0) {
      //borrow from hours
      minDiff += 60;
      sub1=true;
    }
    
    //subtract hours
    int8_t hourDiff = retireDate.hour() - curTime.hour();
    //minutes subtraction had to borrow
    if(sub1) {
      hourDiff--;
    }
    sub1=false;
    if(hourDiff < 0) {
      //borrow from days
      hourDiff += 24;
      sub1=true;
    }

    //subtract days
    int8_t dayDiff = retireDate.day() - curTime.day();
    //hours subtraction had to borrow
    if(sub1) {
      dayDiff--;
    }
    sub1=false;
    if(dayDiff < 0) {
      //borrow from months
      dayDiff += determineMaxDayOfMonth(curTime.month(), curTime.year());
      sub1=true;
    }

    //subtract months
    int8_t monDiff = retireDate.month() - curTime.month();
    //days subtraction had to borrow
    if(sub1) {
      monDiff--;
    }
    sub1=false;
    if(monDiff < 0) {
      //borrow from months
      monDiff += 12; 
      sub1=true;
    }

    //subtract years
    int8_t yearDiff = retireDate.year() - curTime.year();
    //months subtraction had to borrow
    if(sub1) {
      yearDiff--;
    }
    monDiff += (yearDiff * 12);

    sprintf(displayBuff, "%02d    %02d%02d %02d %02d", monDiff, dayDiff, hourDiff, minDiff, secDiff);
    return false; //this indicates we have not reached the countdown date yet
  }

  else {
    return true; //this indicates we have passed the countdown date
  }
}

//Prints current time to display buffer
void Clock::getCurrentTime(char* displayBuff) {
  DateTime curTime = rtc.now();
  uint8_t hour = curTime.hour();

  //12H time
  if(!militaryTime) {
    if(hour > 12) {
      hour -= 12;
    }
    else if(hour == 0) {
      hour = 12;
    }
  }
  sprintf(displayBuff, "%s   %02d%02d %02d %02d", MONTH_NAME[curTime.month() - 1], curTime.day(), hour, curTime.minute(), curTime.second());
}
