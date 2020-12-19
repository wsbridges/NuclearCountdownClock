#include "Display.h"

Display::Display(uint8_t addr) {
  disp.begin(addr);
}

Display::~Display() {
  //No memory allocated. Do nothing.
}

void Display::write(const char str[]) {
  for(uint8_t i = 0; i < 4; i++) {
    disp.writeDigitAscii(i, str[i]);
  }
  disp.writeDisplay();
}

void Display::blink() {
  disp.blinkRate(HT16K33_BLINK_2HZ);
}

void Display::stopBlink() {
  disp.blinkRate(HT16K33_BLINK_DISPLAYON);
}

void Display::setBrightness(uint8_t b) {
  disp.setBrightness(b);
}
