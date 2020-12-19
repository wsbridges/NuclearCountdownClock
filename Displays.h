#ifndef DISPLAYS_H
#define DISPLAYS_H

#include "Adafruit_LEDBackpack.h"
#include "Display.h"

class Displays {
  private:
    Display* disp1;
    Display* disp2;
    Display* disp3;
    Display* disp4;
  public:
    Displays();
    ~Displays();
    void write(const char str[]);
    void blink();
    void stopBlink();
    void blinkBottomRow();
    void changeBrightness(uint8_t b);
};

#endif
