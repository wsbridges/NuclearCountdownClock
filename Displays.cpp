#include "Displays.h"
#include "Brightness.h"
#include <Adafruit_GFX.h>

Displays::Displays() {
  disp1 = new Display(0x70);
  disp2 = new Display(0x71);
  disp3 = new Display(0x72);
  disp4 = new Display(0x73);
}

Displays::~Displays() {
  delete disp1;
  delete disp2;
  delete disp3;
  delete disp4;
}

void Displays::write(const char str[]) {
  if(Brightness::BRIGHTNESS_CHANGED) {
    changeBrightness(Brightness::BRIGHTNESS);
    Brightness::BRIGHTNESS_CHANGED = false;
  }
  char disp1Text[4];
  char disp2Text[4];
  char disp3Text[4];
  char disp4Text[4];
  
  for(uint8_t i = 0; i < 4; i++) {
    disp1Text[i] = str[i];
    disp2Text[i] = str[i+4];
    disp3Text[i] = str[i+8];
    disp4Text[i] = str[i+12];
  }
  
  disp1->write(disp1Text);
  disp2->write(disp2Text);
  disp3->write(disp3Text);
  disp4->write(disp4Text);
}

void Displays::clearScreen() {
  write("                ");
}

void Displays::displayCongratsAnimation() {
  uint8_t animationDelay = 50;
  clearScreen();

  //writing C
  writeRaw(1, 0, 0b0000000000000001);
  delay(animationDelay);
  writeRaw(1, 0, 0b0000000000100001);
  delay(animationDelay);
  writeRaw(1, 0, 0b0000000000110001);
  delay(animationDelay);
  writeRaw(1, 0, 0b0000000000111001);
  delay(animationDelay);

  //writing O
  writeRaw(1, 1, 0b0000000000000001);
  delay(animationDelay);
  writeRaw(1, 1, 0b0000000000100001);
  delay(animationDelay);
  writeRaw(1, 1, 0b0000000000110001);
  delay(animationDelay);
  writeRaw(1, 1, 0b0000000000111001);
  delay(animationDelay);
  writeRaw(1, 1, 0b0000000000111101);
  delay(animationDelay);
  writeRaw(1, 1, 0b0000000000111111);
  delay(animationDelay);

  //writing N
  writeRaw(1, 2, 0b0000000000010000);
  delay(animationDelay);
  writeRaw(1, 2, 0b0000000000110000);
  delay(animationDelay);
  writeRaw(1, 2, 0b0000000100110000);
  delay(animationDelay);
  writeRaw(1, 2, 0b0010000100110000);
  delay(animationDelay);
  writeRaw(1, 2, 0b0010000100110100);
  delay(animationDelay);
  writeRaw(1, 2, 0b0010000100110110);
  delay(animationDelay);

  //writing G
  writeRaw(1, 3, 0b0000000000000001);
  delay(animationDelay);
  writeRaw(1, 3, 0b0000000000100001);
  delay(animationDelay);
  writeRaw(1, 3, 0b0000000000110001);
  delay(animationDelay);
  writeRaw(1, 3, 0b0000000000111001);
  delay(animationDelay);
  writeRaw(1, 3, 0b0000000000111101);
  delay(animationDelay);
  writeRaw(1, 3, 0b0000000010111101);

  //writing R
  writeRaw(2, 0, 0b0000000000010000);
  delay(animationDelay);
  writeRaw(2, 0, 0b0000000000110000);
  delay(animationDelay);
  writeRaw(2, 0, 0b0000000000110001);
  delay(animationDelay);
  writeRaw(2, 0, 0b0000000000110011);
  delay(animationDelay);
  writeRaw(2, 0, 0b0000000011110011);
  delay(animationDelay);
  writeRaw(2, 0, 0b0010000011110011);
  delay(animationDelay);

  //writing A
  writeRaw(2, 1, 0b0000000000010000);
  delay(animationDelay);
  writeRaw(2, 1, 0b0000000000110000);
  delay(animationDelay);
  writeRaw(2, 1, 0b0000000000110001);
  delay(animationDelay);
  writeRaw(2, 1, 0b0000000000110011);
  delay(animationDelay);
  writeRaw(2, 1, 0b0000000000110111);
  delay(animationDelay);
  writeRaw(2, 1, 0b0000000011110111);

  //writing T
  writeRaw(2, 2, 0b0000000000000001);
  delay(animationDelay);
  writeRaw(2, 2, 0b0000001000000001);
  delay(animationDelay);
  writeRaw(2, 2, 0b0001001000000001);
  delay(animationDelay);

  //writing S
  writeRaw(2, 3, 0b0000000000000001);
  delay(animationDelay);
  writeRaw(2, 3, 0b0000000000100001);
  delay(animationDelay);
  writeRaw(2, 3, 0b0000000011100001);
  delay(animationDelay);
  writeRaw(2, 3, 0b0000000011100101);
  delay(animationDelay);
  writeRaw(2, 3, 0b0000000011101101);
  delay(animationDelay);

  //writing J
  writeRaw(3, 2, 0b0000000000000010);
  delay(animationDelay);
  writeRaw(3, 2, 0b0000000000000110);
  delay(animationDelay);
  writeRaw(3, 2, 0b0000000000001110);
  delay(animationDelay);
  writeRaw(3, 2, 0b0000000000011110);
  delay(animationDelay);

  //writing O
  writeRaw(3, 3, 0b0000000000000001);
  delay(animationDelay);
  writeRaw(3, 3, 0b0000000000100001);
  delay(animationDelay);
  writeRaw(3, 3, 0b0000000000110001);
  delay(animationDelay);
  writeRaw(3, 3, 0b0000000000111001);
  delay(animationDelay);
  writeRaw(3, 3, 0b0000000000111101);
  delay(animationDelay);
  writeRaw(3, 3, 0b0000000000111111);
  delay(animationDelay);

  //writing H
  writeRaw(4, 0, 0b0000000000100000);
  delay(animationDelay);
  writeRaw(4, 0, 0b0000000000110000);
  delay(animationDelay);
  writeRaw(4, 0, 0b0000000011110000);
  delay(animationDelay);
  writeRaw(4, 0, 0b0000000011110010);
  delay(animationDelay);
  writeRaw(4, 0, 0b0000000011110110);
  delay(animationDelay);

  //writing N
  writeRaw(4, 1, 0b0000000000010000);
  delay(animationDelay);
  writeRaw(4, 1, 0b0000000000110000);
  delay(animationDelay);
  writeRaw(4, 1, 0b0000000100110000);
  delay(animationDelay);
  writeRaw(4, 1, 0b0010000100110000);
  delay(animationDelay);
  writeRaw(4, 1, 0b0010000100110100);
  delay(animationDelay);
  writeRaw(4, 1, 0b0010000100110110);
  delay(animationDelay);

  uint16_t blinkDelay = 250;
  clearScreen();
  delay(blinkDelay);
  write("CONGRATS  JOHN  ");
  delay(blinkDelay);
  clearScreen();
  delay(blinkDelay);
  write("CONGRATS  JOHN  ");
  delay(blinkDelay);
  clearScreen();
  delay(blinkDelay);
  write("CONGRATS  JOHN  ");
  delay(blinkDelay);
  clearScreen();
  delay(blinkDelay);
  write("CONGRATS  JOHN  ");
  delay(blinkDelay);
  clearScreen();
  delay(blinkDelay);
  write("CONGRATS  JOHN  ");
  delay(blinkDelay);

  spinningAnimation();
  

  write("CONGRATS**JOHN**");
  delay(1000);
  
}

void Displays::spinningAnimation() {
  uint16_t spinDelay = 100;
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

void Displays::blink() {
  disp1->blink();
  disp2->blink();
  disp3->blink();
  disp4->blink();
}

void Displays::stopBlink() {
  disp1->stopBlink();
  disp2->stopBlink();
  disp3->stopBlink();
  disp4->stopBlink();
}

void Displays::blinkBottomRow() {
  disp3->blink();
  disp4->blink();
}

void Displays::changeBrightness(uint8_t b) {
  disp1->setBrightness(b);
  disp2->setBrightness(b);
  disp3->setBrightness(b);
  disp4->setBrightness(b);
}
