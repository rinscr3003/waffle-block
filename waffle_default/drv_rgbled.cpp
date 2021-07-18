#include "drv_rgbled.h"
#include <FastLED.h>
CRGBArray<2>  leds;
void drv_initRGBLED() {
  FastLED.addLeds<WS2812, RGBLED>(leds, 2);
  drv_RGBLED_pwron();
  drv_RGBLED_setbrightness(100);
  drv_RGBLED_setcolor(0, CRGB(0, 0, 255));
  drv_RGBLED_setcolor(1, CRGB(0, 0, 255));
}
void drv_RGBLED_pwron() {
  pinMode(BOEN, OUTPUT);
  digitalWrite(BOEN, LOW);
}
void drv_RGBLED_pwroff() {
  pinMode(BOEN, OUTPUT);
  digitalWrite(BOEN, HIGH);
}
void drv_RGBLED_setcolor(int n, CRGB c) {
  if (n != 0 && n != 1)return;
  leds[n] = c;
  FastLED.show();
}
void drv_RGBLED_setbrightness(int b) {
  FastLED.setBrightness(b);
}
