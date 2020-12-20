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
    uint8_t writeAnimationDelay;
    
  protected: 
    void clearScreen();
    void spinningAnimation();
    void writeCAnimation(uint8_t disp, uint8_t pos);
    void writeOAnimation(uint8_t disp, uint8_t pos);
    void writeNAnimation(uint8_t disp, uint8_t pos);
    void writeGAnimation(uint8_t disp, uint8_t pos);
    void writeRAnimation(uint8_t disp, uint8_t pos);
    void writeAAnimation(uint8_t disp, uint8_t pos);
    void writeTAnimation(uint8_t disp, uint8_t pos);
    void writeSAnimation(uint8_t disp, uint8_t pos);
    void writeJAnimation(uint8_t disp, uint8_t pos);
    void writeHAnimation(uint8_t disp, uint8_t pos);
    
  public:
    Displays();
    ~Displays();
    void write(const char str[]);
    void writeRaw(uint8_t disp, uint8_t pos, uint16_t bitmask);
    void displayCongratsAnimation();
    void changeBrightness(uint8_t b);
    
};

#endif
