#include <TFT_eSPI.h>
#include "drv_rgbled.h"
#include <Wire.h>
#include <LITTLEFS.h>
#include "drv_charge.h"
#include "drv_rtc.h"
#include "drv_sht.h"
#include "drv_button.h"
#include "drv_misc.h"
#include "drv_tft.h"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  if (!LITTLEFS.begin()) {
    Serial.println("Flash FS initialisation failed!");
    while (1); // Stay here twiddling thumbs waiting
  }
  drv_initCharge();
  drv_initRGBLED();
  drv_initRTC();
  drv_initSHT3X();
  drv_initBUTTON();
  drv_initTFT();
  drv_initMisc();

  drv_TFT_getinstance().drawCentreString("LOADING...", 79, 25, 4);
  drv_TFT_loadfont();
  drv_TFT_getinstance().fillScreen(TFT_BLACK);

  drv_RGBLED_setbrightness(20);
  drv_RGBLED_setcolor(0, 0, 255, 255);
  drv_RGBLED_setcolor(1, 255, 64, 64);
  drv_MISC_settopled(true);

  //drv_TFT_drawtime60px(0, 7, 31);
  //drv_TFT_getinstance().drawCentreString("2021-07-23 星期五", 79, 60, 1);
  //delay(5000);
  //uint16_t* buf = (uint16_t *)heap_caps_malloc(4096 * 2, MALLOC_CAP_SPIRAM);
  //memset(buf, 0xff, 4096 * 2);
  //drv_TFT_drawraw(8, 8, 64, 64, buf);
  //drv_TFT_getinstance().pushImageDMA(8, 8, 64, 64, buf, NULL);
  //drv_TFT_draw16b(8, 8, 64, 64, "/color-64/104.png.16b");
  drv_TFT_drawpng(0, 16, "/color-64/104.png");
  drv_TFT_getinstance().drawCentreString("阴", 79, 2, 1);
  drv_TFT_getinstance().drawCentreString("29度", 110, 22, 1);
  drv_TFT_getinstance().drawCentreString("61%", 110, 42, 1);
  drv_TFT_getinstance().drawCentreString("AQI 良", 110, 62, 1);
  //heap_caps_free(buf);
}

void loop() {
  // put your main code here, to run repeatedly:

}
