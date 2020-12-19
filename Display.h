#ifndef DISPLAY_H
#define DISPLAY_H

#include "Adafruit_LEDBackpack.h"

class Display {
  private:
    Adafruit_AlphaNum4 disp;
  public:
    Display(uint8_t addr);
    ~Display();
    void write(const char str[]);
    void writeRaw(uint8_t pos, uint16_t bitmask);
    void blink();
    void stopBlink();
    void setBrightness(uint8_t b);
};

#endif
