#include "drv_tft.h"
#include <FS.h>
#include <LITTLEFS.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <stdint.h>

TFT_eSPI _drv_tft = TFT_eSPI();

void drv_initTFT() {
  _drv_tft.init();
  _drv_tft.setRotation(3);
  _drv_tft.fillScreen(TFT_BLACK);
  pinMode(LCD_BL, OUTPUT);
  digitalWrite(LCD_BL, HIGH);
  _drv_tft.setTextColor(TFT_WHITE, TFT_BLACK);
}

TFT_eSPI drv_TFT_getinstance() {
  return _drv_tft;
}

void drv_TFT_setbacklight(bool s) {
  digitalWrite(LCD_BL, s ? HIGH : LOW);
}

void drv_TFT_drawtime60px(uint8_t y, uint8_t h, uint8_t m) {
  _drv_tft.drawXBitmap(5, y, _drv_TFT_srcs60num + 240 * ((h / 10) % 10), 30, 60, TFT_WHITE);
  _drv_tft.drawXBitmap(35, y, _drv_TFT_srcs60num + 240 * (h % 10), 30, 60, TFT_WHITE);
  _drv_tft.drawXBitmap(65, y, _drv_TFT_srcs60num + 240 * 10, 30, 60, TFT_WHITE);
  _drv_tft.drawXBitmap(95, y, _drv_TFT_srcs60num + 240 * ((m / 10) % 10), 30, 60, TFT_WHITE);
  _drv_tft.drawXBitmap(125, y, _drv_TFT_srcs60num + 240 * (m % 10), 30, 60, TFT_WHITE);
}

void drv_TFT_loadfont() {
  if (!LITTLEFS.begin()) {
    Serial.println("Flash FS initialisation failed!");
    while (1) yield(); // Stay here twiddling thumbs waiting
  }
  _drv_tft.loadFont("SRCS18", LITTLEFS);
}

void drv_TFT_unloadfont() {
  _drv_tft.unloadFont();
}
