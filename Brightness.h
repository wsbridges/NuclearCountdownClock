#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H

#include <stdint.h>

/*
 * Collection of static variable pertaining to the Brightness
 * level of the LED displays.
 */
class Brightness {

  public:
    //Brightness of the LEDs. Can be 0-15
    static uint8_t BRIGHTNESS;

    //Stores if the Brightness has changed in
    //the clock menu, so that the brightness
    //can be updated in the display
    static bool BRIGHTNESS_CHANGED;
  
};

#endif
