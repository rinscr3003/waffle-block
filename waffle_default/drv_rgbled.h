#include <FastLED.h>

void drv_initRGBLED();
void drv_RGBLED_pwron();
void drv_RGBLED_pwroff();
void drv_RGBLED_setcolor(int n, uint8_t r, uint8_t g, uint8_t b);
void drv_RGBLED_setbrightness(int b);
