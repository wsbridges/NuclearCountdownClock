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
