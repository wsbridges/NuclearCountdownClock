#ifndef CLOCK_H
#define CLOCK_H

#include "RTClib.h"

class Clock {
  
  private:
    RTC_DS3231 rtc;
    DateTime retireDate;
    uint8_t setupMenuCounter;
    bool militaryTime;
    bool error;
  
  protected:
    uint8_t determineMaxDayOfMonth(uint8_t month, uint16_t year);
    DateTime setupMenu(char* displayBuff, DateTime date, bool plus, bool minus);
    void setCountdownTime(char* displayBuff, bool plus, bool minus);
    void changeBrightness(char* displayBuff, bool plus, bool minus);
    void adjustCountdownTime(char* displayBuff, bool plus, bool minus);
    void adjustTime(char* displayBuff, bool plus, bool minus);
  
  public:
    Clock();
    bool initialized();
    bool getCountdownTime(char* displayBuff);
    void getCurrentTime(char* displayBuff);
    void nextMenuItem(bool countdownMode);
    void resetMenu();
    void increaseTime(char* displayBuff);
    void decreaseTime(char* displayBuff);
    void showTimeSetup(char* displayBuff);
    void increaseCountdownTime(char* displayBuff);
    void decreaseCountdownTime(char* displayBuff);
    void showCountdownSetup(char* displayBuff);

    static const char* MONTH_NAME[];
    
};

#endif
