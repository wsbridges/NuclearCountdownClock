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
    resetMenu();
  }
}

boolean Clock::initialized() {
  return !error;
}

void Clock::resetMenu() {
  setupMenuCounter = 0;
}

void Clock::nextMenuItem(bool countdownMode) {
  if(!countdownMode) {
    setupMenuCounter = (setupMenuCounter + 1) % 8;
  }
  else {
    setupMenuCounter = (setupMenuCounter + 1) % 7;
  }
}

void Clock::increaseCountdownTime(char* displayBuff) {
  setCountdownTime(displayBuff, true, false);
}

void Clock::decreaseCountdownTime(char* displayBuff) {
  setCountdownTime(displayBuff, false, true);
}

void Clock::showCountdownSetup(char* displayBuff) {
  setCountdownTime(displayBuff, false, false);
}

void Clock::setCountdownTime(char* displayBuff, bool plus, bool minus) {
  uint16_t year = retireDate.year();
  uint8_t month = retireDate.month();
  uint8_t day = retireDate.day();
  uint8_t hour = retireDate.hour();
  uint8_t minute = retireDate.minute();
  uint8_t second = retireDate.second();
  switch(setupMenuCounter) {
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
    case 1:
    {
      sprintf(displayBuff, " MONTH    %s   ", MONTH_NAME[month - 1]);
      bool monthChanged = false;
      if(plus) {
        month++;
        if(month == 13) {
          month = 1;
        }
        monthChanged = true;
      }
      else if(minus) {
        month--;
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
    case 2:
    {
      sprintf(displayBuff, "  DAY      %02d   ", day);
      if(plus) {
        day++;
        if(day > determineMaxDayOfMonth(month, year)) {
          day = 1;
        }
      }
      if(minus) {
        day--;
        if(day == 0) {
          day = determineMaxDayOfMonth(month, year);
        }
      }
      break;
    }
    case 3:
    {
      if(militaryTime) {
        sprintf(displayBuff, "  HOUR     %02d   ", hour);
      }
      else {
        uint8_t twelveHour = hour;
        bool pm = false;
        if(twelveHour >= 12) {
          pm = true;
          if(twelveHour > 13) {
            twelveHour -= 12;
          }
        }
        else if(hour == 0) {
          twelveHour = 12;
        }
        sprintf(displayBuff, "  HOUR    %02d%s  ", twelveHour, (pm ? "PM" : "AM"));
      }
      if(plus) {
        hour++;
        if(hour == 24) {
          hour = 0;
        }
      }
      if(minus) {
        //doing it this way since hour is unsigned and can't be negative
        if(hour == 0) {
          hour = 24;
        }
        hour--;
      }
      break;
    }
    case 4:
    {
      sprintf(displayBuff, " MINUTE    %02d   ", minute);
      if(plus) {
        minute++;
        if(minute == 60) {
          minute = 0;
        }
      }
      if(minus) {
        //doing it this way since minute is unsigned and can't be negative
        if(minute == 0) {
          minute = 60;
        }
        minute--;
      }
      break;
    }
    case 5:
    {
      sprintf(displayBuff, " SECOND    %02d   ", second);
      if(plus) {
        second++;
        if(second == 60) {
          second = 0;
        }
      }
      if(minus) {
        //doing it this way since minute is unsigned and can't be negative
        if(second == 0) {
          second = 60;
        }
        second--;
      }
      break;
    }
    case 6:
    {
      changeBrightness(displayBuff, plus, minus);
      break;
    }
  }
  retireDate = DateTime(year, month, day, hour, minute, second);
}

void Clock::increaseTime(char* displayBuff) {
  setTime(displayBuff, true, false);
}

void Clock::decreaseTime(char* displayBuff) {
  setTime(displayBuff, false, true);
}

void Clock::showTimeSetup(char* displayBuff) {
  setTime(displayBuff, false, false);
}

void Clock::setTime(char* displayBuff, bool plus, bool minus) {
  DateTime curTime = rtc.now();
  uint16_t year = curTime.year();
  uint8_t month = curTime.month();
  uint8_t day = curTime.day();
  uint8_t hour = curTime.hour();
  uint8_t minute = curTime.minute();
  uint8_t second = curTime.second();
  switch(setupMenuCounter) {
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
    case 1:
    {
      sprintf(displayBuff, " MONTH    %s   ", MONTH_NAME[month - 1]);
      bool monthChanged = false;
      if(plus) {
        month++;
        if(month == 13) {
          month = 1;
        }
        monthChanged = true;
      }
      else if(minus) {
        month--;
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
    case 2:
    {
      sprintf(displayBuff, "  DAY      %02d   ", day);
      if(plus == HIGH) {
        day++;
        if(day > determineMaxDayOfMonth(month, year)) {
          day = 1;
        }
      }
      if(minus == HIGH) {
        day--;
        if(day == 0) {
          day = determineMaxDayOfMonth(month, year);
        }
      }
      break;
    }
    case 3:
    {
      sprintf(displayBuff, " 12/24H    %02d   ", (militaryTime ? 24 : 12));
      if(plus == HIGH || minus == HIGH) {
        militaryTime = !militaryTime;
      }
      break;
    }
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
          if(twelveHour > 13) {
            twelveHour -= 12;
          }
        }
        else if(hour == 0) {
          twelveHour = 12;
        }
        sprintf(displayBuff, "  HOUR    %02d%s  ", twelveHour, (pm ? "PM" : "AM"));
      }
      if(plus) {
        hour++;
        if(hour == 24) {
          hour = 0;
        }
      }
      if(minus) {
        //doing it this way since hour is unsigned and can't be negative
        if(hour == 0) {
          hour = 24;
        }
        hour--;
      }
      break;
    }
    case 5:
    {
      sprintf(displayBuff, " MINUTE    %02d   ", minute);
      if(plus) {
        minute++;
        if(minute == 60) {
          minute = 0;
        }
      }
      if(minus) {
        //doing it this way since minute is unsigned and can't be negative
        if(minute == 0) {
          minute = 60;
        }
        minute--;
      }
      break;
    }
    case 6:
    {
      sprintf(displayBuff, " SECOND    %02d   ", second);
      if(plus) {
        second++;
        if(second == 60) {
          second = 0;
        }
      }
      if(minus) {
        //doing it this way since minute is unsigned and can't be negative
        if(second == 0) {
          second = 60;
        }
        second--;
      }
      break;
    }
    case 7:
    {
      changeBrightness(displayBuff, plus, minus);
      break;
    }
  }
  rtc.adjust(DateTime(year, month, day, hour, minute, second));
}

void Clock::changeBrightness(char* displayBuff, bool plus, bool minus) {
  sprintf(displayBuff, "BRGHTNSS   %02d   ", Brightness::BRIGHTNESS);
      if(plus) {
        Brightness::BRIGHTNESS++;
        if(Brightness::BRIGHTNESS > 15) {
          Brightness::BRIGHTNESS = 0;
        }
        Brightness::BRIGHTNESS_CHANGED = true;
      }
      if(minus) {
        Brightness::BRIGHTNESS--;
        if(Brightness::BRIGHTNESS < 0) {
          Brightness::BRIGHTNESS = 15;
        }
        Brightness::BRIGHTNESS_CHANGED = true;
      }
}

uint8_t Clock::determineMaxDayOfMonth(uint8_t month, uint16_t year) {
  if(month == 1 ||
     month == 3 ||
     month == 5 ||
     month == 7 ||
     month == 8 ||
     month == 10 ||
     month == 12 ) {
    return 31;
  }
  else if(month == 4 ||
          month == 6 ||
          month == 9 ||
          month == 11) {
    return 30;
  }
  else if(month == 2) {
    if(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
      return 29;
    }
    else {
      return 28;
    }
  }
}

void Clock::getCountdownTime(char* displayBuff) {
  DateTime curTime = rtc.now();
  if(retireDate.unixtime() > curTime.unixtime()){
    //subtract seconds
    Serial.print("Retire date seconds:");
    Serial.print(retireDate.second(), DEC);
    Serial.println();
    Serial.print("Current date seconds:");
    Serial.print(curTime.second(), DEC);
    Serial.println();
    int8_t secDiff = retireDate.second() - curTime.second();
    bool sub1 = false;
    if(secDiff < 0) {
      secDiff += 60;
      sub1 = true;
    }

    Serial.print("Diff:");
    Serial.print(secDiff);
    Serial.println();
    Serial.println();

    //subtract minutes
    Serial.print("Retire date minutes:");
    Serial.print(retireDate.minute(), DEC);
    Serial.println();
    Serial.print("Current date minutes:");
    Serial.print(curTime.minute(), DEC);
    Serial.println();
    int8_t minDiff = retireDate.minute() - curTime.minute();
    if(sub1) {
      minDiff--;
    }
    sub1 = false;
    if(minDiff < 0) {
      minDiff += 60;
      sub1=true;
    }

    Serial.print("Diff:");
    Serial.print(minDiff);
    Serial.println();
    Serial.println();

    //subtract hours
    Serial.print("Retire date hours:");
    Serial.print(retireDate.hour(), DEC);
    Serial.println();
    Serial.print("Current date minutes:");
    Serial.print(curTime.hour(), DEC);
    Serial.println();
    int8_t hourDiff = retireDate.hour() - curTime.hour();
    if(sub1) {
      hourDiff--;
    }
    sub1=false;
    if(hourDiff < 0) {
      hourDiff += 24;
      sub1=true;
    }

    Serial.print("Diff:");
    Serial.print(hourDiff);
    Serial.println();
    Serial.println();

    //subtract days
    Serial.print("Retire date days:");
    Serial.print(retireDate.day(), DEC);
    Serial.println();
    Serial.print("Current date days:");
    Serial.print(curTime.day(), DEC);
    Serial.println();
    int8_t dayDiff = retireDate.day() - curTime.day();
    if(sub1) {
      dayDiff--;
    }
    sub1=false;
    if(dayDiff < 0) {
      dayDiff += determineMaxDayOfMonth(curTime.month(), curTime.year());
      sub1=true;
    }

    Serial.print("Diff:");
    Serial.print(dayDiff);
    Serial.println();
    Serial.println();

    //subtract months
    Serial.print("Retire date months:");
    Serial.print(retireDate.month(), DEC);
    Serial.println();
    Serial.print("Current date months:");
    Serial.print(curTime.month(), DEC);
    Serial.println();
    int8_t monDiff = retireDate.month() - curTime.month();
    if(sub1) {
      monDiff--;
    }
    sub1=false;
    if(monDiff < 0) {
      monDiff += 12; 
      sub1=true;
    }

    //subtract years
    int8_t yearDiff = retireDate.year() - curTime.year();
    if(sub1) {
      yearDiff--;
    }
    monDiff += (yearDiff * 12);

    Serial.print("Diff:");
    Serial.print(monDiff);
    Serial.println();
    Serial.println();
    
    sprintf(displayBuff, "%02d    %02d%02d %02d %02d", monDiff, dayDiff, hourDiff, minDiff, secDiff);
  }

  else {
    sprintf(displayBuff, "CONGRATS  JOHN  ");
  }
}

void Clock::displayCongratsAnimation(char* displayBuff) {
  
}

void Clock::getCurrentTime(char* displayBuff) {
  DateTime curTime = rtc.now();
  uint8_t hour = curTime.hour();
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
