#include "Displays.h"
#include "Brightness.h"
#include <Adafruit_GFX.h>

Displays::Displays() {
  //Display addresses are set by soldering jumpers
  //on the backpack board
  disp1 = new Display(0x70);
  disp2 = new Display(0x71);
  disp3 = new Display(0x72);
  disp4 = new Display(0x73);
  
  //Default values
  writeAnimationDelay = 50;
}

Displays::~Displays() {
  delete disp1;
  delete disp2;
  delete disp3;
  delete disp4;
}

//Shows a 16 character String on the displays
void Displays::write(const char str[]) {
  //Update brightness setting if it has changed
  if(Brightness::BRIGHTNESS_CHANGED) {
    changeBrightness(Brightness::BRIGHTNESS);
    //Resets flag so we don't do this every time
    Brightness::BRIGHTNESS_CHANGED = false;
  }
  
  char disp1Text[4]; //Text for first Display
  char disp2Text[4]; //Text for second Display
  char disp3Text[4]; //Text for third Display
  char disp4Text[4]; //Text for fourth Display

  //Split 16 characters into 4 characters for
  //each Display
  for(uint8_t i = 0; i < 4; i++) {
    disp1Text[i] = str[i];
    disp2Text[i] = str[i+4];
    disp3Text[i] = str[i+8];
    disp4Text[i] = str[i+12];
  }

  //Show text on displays
  disp1->write(disp1Text);
  disp2->write(disp2Text);
  disp3->write(disp3Text);
  disp4->write(disp4Text);
}

//Turns off all displays
void Displays::clearScreen() {
  write("                ");
}

//Looks like a writing animation. Lights 1 segment at a time
//disp is which disp# object to reference.
//pos is which position (0-3) to write to on the display
void Displays::writeCAnimation(uint8_t disp, uint8_t pos) {
  writeRaw(disp, pos, 0b0000000000000001);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000000100001);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000000110001);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000000111001);
  delay(writeAnimationDelay);
}

//Looks like a writing animation. Lights 1 segment at a time
//disp is which disp# object to reference.
//pos is which position (0-3) to write to on the display
void Displays::writeOAnimation(uint8_t disp, uint8_t pos) {
  writeRaw(disp, pos, 0b0000000000000001);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000000100001);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000000110001);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000000111001);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000000111101);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000000111111);
  delay(writeAnimationDelay);
}

//Looks like a writing animation. Lights 1 segment at a time
//disp is which disp# object to reference.
//pos is which position (0-3) to write to on the display
void Displays::writeNAnimation(uint8_t disp, uint8_t pos) {
  writeRaw(disp, pos, 0b0000000000010000);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000000110000);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000100110000);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0010000100110000);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0010000100110100);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0010000100110110);
  delay(writeAnimationDelay);
}

//Looks like a writing animation. Lights 1 segment at a time
//disp is which disp# object to reference.
//pos is which position (0-3) to write to on the display
void Displays::writeGAnimation(uint8_t disp, uint8_t pos) {
  writeRaw(disp, pos, 0b0000000000000001);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000000100001);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000000110001);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000000111001);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000000111101);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000010111101);
  delay(writeAnimationDelay);
}

//Looks like a writing animation. Lights 1 segment at a time
//disp is which disp# object to reference.
//pos is which position (0-3) to write to on the display
void Displays::writeRAnimation(uint8_t disp, uint8_t pos) {
  writeRaw(disp, pos, 0b0000000000010000);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000000110000);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000000110001);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000000110011);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000011110011);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0010000011110011);
  delay(writeAnimationDelay);
}

//Looks like a writing animation. Lights 1 segment at a time
//disp is which disp# object to reference.
//pos is which position (0-3) to write to on the display
void Displays::writeAAnimation(uint8_t disp, uint8_t pos) {
  writeRaw(disp, pos, 0b0000000000010000);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000000110000);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000000110001);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000000110011);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000000110111);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000011110111);
  delay(writeAnimationDelay);
}

//Looks like a writing animation. Lights 1 segment at a time
//disp is which disp# object to reference.
//pos is which position (0-3) to write to on the display
void Displays::writeTAnimation(uint8_t disp, uint8_t pos) {
  writeRaw(disp, pos, 0b0000000000000001);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000001000000001);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0001001000000001);
  delay(writeAnimationDelay);
}

//Looks like a writing animation. Lights 1 segment at a time
//disp is which disp# object to reference.
//pos is which position (0-3) to write to on the display
void Displays::writeSAnimation(uint8_t disp, uint8_t pos) {
  writeRaw(disp, pos, 0b0000000000000001);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000000100001);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000011100001);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000011100101);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000011101101);
  delay(writeAnimationDelay);
}

//Looks like a writing animation. Lights 1 segment at a time
//disp is which disp# object to reference.
//pos is which position (0-3) to write to on the display
void Displays::writeJAnimation(uint8_t disp, uint8_t pos) {
  writeRaw(disp, pos, 0b0000000000000010);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000000000110);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000000001110);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000000011110);
  delay(writeAnimationDelay);
}

//Looks like a writing animation. Lights 1 segment at a time
//disp is which disp# object to reference.
//pos is which position (0-3) to write to on the display
void Displays::writeHAnimation(uint8_t disp, uint8_t pos) {
  writeRaw(disp, pos, 0b0000000000100000);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000000110000);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000011110000);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000011110010);
  delay(writeAnimationDelay);
  writeRaw(disp, pos, 0b0000000011110110);
  delay(writeAnimationDelay);
}

//Displays a series of Congratulations animations
void Displays::displayCongratsAnimation() {
  clearScreen();

  //Write letter animations
  writeCAnimation(1, 0);
  writeOAnimation(1, 1);
  writeNAnimation(1, 2);
  writeGAnimation(1, 3);
  writeRAnimation(2, 0);
  writeAAnimation(2, 1);
  writeTAnimation(2, 2);
  writeSAnimation(2, 3);
  
  writeJAnimation(3, 2);
  writeOAnimation(3, 3);
  writeHAnimation(4, 0);
  writeNAnimation(4, 1);

  //Flash CONGRATS JOHN 5 times
  uint16_t blinkDelay = 250;
  for(uint8_t i = 0; i < 5; i++) {
    clearScreen();
    delay(blinkDelay);
    write("CONGRATS  JOHN  ");
    delay(blinkDelay);
  }

  //Spinning animation next to the Congrats message
  spinningAnimation();
  
  //Final message before it loops
  write("CONGRATS**JOHN**");
  delay(1000);
  
}

//Does a spinning animation around the Congrats message
void Displays::spinningAnimation() {
  uint16_t spinDelay = 100;
  
  //start with 1 spinning animation on either side
  for(int i = 0; i < 3; i++) {
    write("CONGRATS\\ JOHN /");
    delay(spinDelay);
  
    write("CONGRATS| JOHN |");
    delay(spinDelay);
    
    write("CONGRATS/ JOHN \\");
    delay(spinDelay);
    
    write("CONGRATS- JOHN -");
    delay(spinDelay);
  }
  
  //bump up to 2 spinning animations on either side
  for(int i = 0; i < 4; i++) {
    write("CONGRATS\\/JOHN\\/");
    delay(spinDelay);
  
    write("CONGRATS|-JOHN-|");
    delay(spinDelay);
    
    write("CONGRATS/\\JOHN/\\");
    delay(spinDelay);
    
    write("CONGRATS-|JOHN|-");
    delay(spinDelay);
  }
  
}

//Helper method for writing raw bitmask for the array of displays
void Displays::writeRaw(uint8_t disp, uint8_t pos, uint16_t bitmask) {
  if(disp == 1) {
    disp1->writeRaw(pos, bitmask);
  }
  if(disp == 2) {
    disp2->writeRaw(pos, bitmask);
  }
  if(disp == 3) {
    disp3->writeRaw(pos, bitmask);
  }
  if(disp == 4) {
    disp4->writeRaw(pos, bitmask);
  }
}

//Changes brightness level (0-15) on all displays
void Displays::changeBrightness(uint8_t b) {
  disp1->setBrightness(b);
  disp2->setBrightness(b);
  disp3->setBrightness(b);
  disp4->setBrightness(b);
}
