#include "Brightness.h"

//Defaulting Brightness level to 5. Anything over about
//10 and the LEDs have a weird flicker. Setting it at 5
//provides good visibility without the annoying flicker.
uint8_t Brightness::BRIGHTNESS = 5;

//Defaulting this to true so when the clock starts up 
//it will change the brightness to 5. Otherwise, 
//the displays default to 15.
bool Brightness::BRIGHTNESS_CHANGED = true;
