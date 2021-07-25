#include "drv_tft.h"
#include <TFT_eSPI.h>
#include <SPI.h>
#include <stdint.h>
#include "lodepng.h"
#include <iostream>
#include <Arduino.h>
#include <FS.h>
#include <LITTLEFS.h>

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
  _drv_tft.loadFont("SRCS18", LITTLEFS);
}

void drv_TFT_unloadfont() {
  _drv_tft.unloadFont();
}

void drv_TFT_drawraw(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t *raw) {
  _drv_tft.startWrite();
  _drv_tft.setAddrWindow(x, y, w, h);
  for (int i = 0; i < h * w; i++) {
    _drv_tft.pushBlock(raw[i], 1);
  }
  _drv_tft.endWrite();
}

void drv_TFT_drawraw8(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t *raw) {
  _drv_tft.startWrite();
  _drv_tft.setAddrWindow(x, y, w, h);
  for (int i = 0; i < h * w * 2; i += 2) {
    _drv_tft.pushBlock((raw[i] << 8 || raw[i + 1]), 1);
  }
  _drv_tft.endWrite();
}

void drv_TFT_draw16b(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const char* filepath) {
  uint8_t* buf = (uint8_t *)heap_caps_malloc(w * h * 2, MALLOC_CAP_SPIRAM);
  //  if (!LITTLEFS.begin()) {
  //    Serial.println("Flash FS initialisation failed!");
  //    while (1) yield(); // Stay here twiddling thumbs waiting
  //  }
  //  Serial.println("begin good.");
  fs::File file = LITTLEFS.open(filepath, "r");
  if (!file) {
    heap_caps_free(buf);
    return;
  }
  uint32_t bufsize = file.size();
  file.read(buf, bufsize);
  file.close();

  //_drv_tft.pushImageDMA(x, y, w, h, _drv_TFT_Pixels, NULL);
  drv_TFT_drawraw8(x, y, w, h, buf);

  heap_caps_free(buf);
}

void drv_TFT_drawpng(uint8_t x, uint8_t y, const char* filepath) {
  uint8_t* buf = (uint8_t *)heap_caps_malloc(4096, MALLOC_CAP_SPIRAM);
  for (int i = 0; i < 100; i++) {
    Serial.println(i);
    delay(20);
  }
  //  if (!LITTLEFS.begin()) {
  //    Serial.println("Flash FS initialisation failed!");
  //    while (1) yield(); // Stay here twiddling thumbs waiting
  //  }
  //  Serial.println("begin good.");
  fs::File file = LITTLEFS.open(filepath, "r");
  if (!file) {
    Serial.println("Failed to open file for reading");
    heap_caps_free(buf);
    return;
  }
  Serial.println("Open good.");
  uint32_t bufsize = file.size();
  file.read(buf, bufsize);
  file.close();
  Serial.println(bufsize);
  Serial.println("Read good.");

  unsigned w, h;
  uint8_t* png = (uint8_t *)heap_caps_malloc(4 * 160 * 80, MALLOC_CAP_SPIRAM);
  Serial.println("Malloc good.");
  int err = lodepng_decode32(&png, &w, &h, buf, bufsize);
  heap_caps_free(buf);
  if (!err) {
    Serial.println("Decode good.");
    Serial.println(w * h);
    uint16_t *_drv_TFT_Pixels = (uint16_t *)heap_caps_malloc(2 * 160 * 80, MALLOC_CAP_SPIRAM);
    for (uint32_t i = 0; i < w * h * 4; i += 4)
    {
      _drv_TFT_Pixels[i / 4] = _drv_tft.color565(png[i], png[i + 1], png[i + 2]);;
    }
    Serial.println("Convert good.");
    //_drv_tft.pushImageDMA(x, y, w, h, _drv_TFT_Pixels, NULL);
    drv_TFT_drawraw(x, y, w, h, _drv_TFT_Pixels);
    heap_caps_free(_drv_TFT_Pixels);
  } else {
    Serial.println("Failed to decode");
    Serial.println(err);
  }
  heap_caps_free(png);
}
