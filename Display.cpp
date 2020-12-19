#include "Display.h"

Display::Display(uint8_t addr) {
  disp.begin(addr);
}

Display::~Display() {
  //No memory allocated. Do nothing.
}

void Display::write(const char str[]) {
  for(uint8_t i = 0; i < 4; i++) {
    //The default '5' looks weird. Using the same as 
    //'S' because it looks like what I want it to.
    if(str[i] == '5') {
      disp.writeDigitAscii(i, 'S');
    }
    else {
      disp.writeDigitAscii(i, str[i]);
    }
  }
  disp.writeDisplay();
}



/************************************************
 * Each number below represents which bit (from
 * left to right) of the 16 digit bitmask 
 * corresponds to which segment of the LED. For 
 * example to display the number 7, we need a 1 
 * in digits 16, 15, and 14. This corresponds to 
 * the value 0b0000000000000111
 * 
 *                     16
 *  -------          ------         8  7  6
 * | \ | / |     11 |      | 15      \ | /
 * |  \|/  |  =>    |      |          \|/
 *  --- ---   =>                 10 --- --- 9
 * |  /|\  |  => 12 |      | 14       /|\
 * | / | \ |        |      |         / | \
 *  -------          ------         5  4  3
 *                     13
 *************************************************
 */
void Display::writeRaw(uint8_t pos, uint16_t bitmask) {
  disp.writeDigitRaw(pos, bitmask);
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
