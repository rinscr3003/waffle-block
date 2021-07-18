#include "drv_rgbled.h"
#include <FastLED.h>
CRGB leds[2];
void drv_initRGBLED() {
  FastLED.addLeds<NEOPIXEL, RGBLED>(leds, 2);
  drv_RGBLED_pwron();
  //drv_RGBLED_setbrightness(100);
  drv_RGBLED_setcolor(0, 0, 0, 0);
  drv_RGBLED_setcolor(1, 0, 0, 0);
}
void drv_RGBLED_pwron() {
  pinMode(BOEN, OUTPUT);
  digitalWrite(BOEN, LOW);
}
void drv_RGBLED_pwroff() {
  pinMode(BOEN, OUTPUT);
  digitalWrite(BOEN, HIGH);
}
void drv_RGBLED_setcolor(int n, uint8_t r, uint8_t g, uint8_t b) {
  if (n != 0 && n != 1)return;
  leds[n] = CRGB(r, g, b);;
  FastLED.show();
}
void drv_RGBLED_setbrightness(int b) {
  FastLED.setBrightness(b);
}
