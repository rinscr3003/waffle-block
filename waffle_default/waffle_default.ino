#include <TFT_eSPI.h>
#include "drv_rgbled.h"
#include <Wire.h>
#include "drv_charge.h"
#include "drv_rtc.h"
#include "drv_sht.h"
#include "drv_button.h"
//#include "drv_misc.h"
#include "drv_tft.h"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  drv_initCharge();
  drv_initRGBLED();
  drv_initRTC();
  drv_initSHT3X();
  drv_initBUTTON();
  drv_initTFT();
  drv_TFT_getinstance().drawCentreString("LOADING...", 79, 25, 4);
  drv_TFT_loadfont();
  drv_TFT_getinstance().fillScreen(TFT_BLACK);

  drv_RGBLED_setbrightness(20);
  drv_RGBLED_setcolor(0, 0, 255, 255);
  drv_RGBLED_setcolor(1, 255, 64, 64);

  drv_TFT_drawtime60px(0, 7, 31);
  drv_TFT_getinstance().drawCentreString("2021-07-23 星期五", 79, 60, 1);
}

void loop() {
  // put your main code here, to run repeatedly:

}
