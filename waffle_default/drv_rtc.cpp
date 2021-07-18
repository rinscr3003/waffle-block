#include "drv_rtc.h"
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <Wire.h>

uint8_t _drv_RTC_readbyte(uint8_t addr) {
  uint8_t rdData;
  uint8_t rdDataCount;
  do {
    Wire.beginTransmission(RX8025T_I2C_ADDR);
    Wire.write(addr);
    Wire.endTransmission(false); // Restart
    delay(10);
    rdDataCount = Wire.requestFrom(RX8025T_I2C_ADDR, 1);
  } while (rdDataCount == 0);
  while (Wire.available()) {
    rdData = Wire.read();
  }
  return rdData;
}

void _drv_RTC_writebyte(uint8_t addr, uint8_t data) {
  Wire.beginTransmission(RX8025T_I2C_ADDR);
  Wire.write(addr);
  Wire.write(data);
  Wire.endTransmission();
}
void _drv_RTC_onalarmint();
void drv_initRTC() {
  //Wire.begin();
  setenv("TZ", "CST-8", 1);
  tzset();
  if (!drv_RTC_getvlowflag()) {
    drv_RTC_syncouttime();
  } else {
    uint8_t buf = _drv_RTC_readbyte(0x0F);
    buf |= 0b00000001;
    _drv_RTC_writebyte(0x0F, buf);
    drv_RTC_clearallflags();
  }
  attachInterrupt(34, _drv_RTC_onalarmint, FALLING);
}
void drv_RTC_settime(struct tm *timePtr) {
  if (timePtr->tm_year + 1900 > 2099 || timePtr->tm_year + 1900 < 2000)return;
  if (mktime(timePtr) == -1)return;
  const uint8_t weekbcd[7] = {
    0b00000001,
    0b00000010,
    0b00000100,
    0b00001000,
    0b00010000,
    0b00100000,
    0b01000000
  };
  //_drv_RTC_writebyte(0x0f, 0b01000000); // temporarily disable Alarm INT
  _drv_RTC_writebyte(0x00, timePtr->tm_sec); // set second
  _drv_RTC_writebyte(0x01, timePtr->tm_min); // set minute
  _drv_RTC_writebyte(0x02, timePtr->tm_hour); // set hour
  _drv_RTC_writebyte(0x06, timePtr->tm_year + 1900 - 2000); // set year
  _drv_RTC_writebyte(0x05, timePtr->tm_mon + 1); // set month
  _drv_RTC_writebyte(0x04, timePtr->tm_mday); // set day
  _drv_RTC_writebyte(0x03, weekbcd[timePtr->tm_wday]); // set weekday
}
struct tm drv_RTC_gettime() {
  struct tm timePtr;
  timePtr.tm_year = _drv_RTC_readbyte(0x06) + 2000 - 1900;
  timePtr.tm_mon = _drv_RTC_readbyte(0x05) - 1;
  timePtr.tm_mday = _drv_RTC_readbyte(0x04);
  timePtr.tm_hour = _drv_RTC_readbyte(0x02);
  timePtr.tm_min = _drv_RTC_readbyte(0x01);
  timePtr.tm_sec = _drv_RTC_readbyte(0x00);
  return timePtr;
}
void drv_RTC_syncintime() {
  time_t nowtime = time(NULL);
  //localtime_r(&now, &timeinfo);
  struct tm *timePtr = localtime(&nowtime);
  drv_RTC_settime(timePtr);
}
void drv_RTC_syncouttime() {
  struct tm timePtr = drv_RTC_gettime();
  int ts = mktime(&timePtr);
  if (ts == -1) return;
  struct timeval val;
  val.tv_sec = ts;
  val.tv_usec = 0;
  settimeofday(&val, NULL);
}
void drv_RTC_setram(uint8_t b) {
  _drv_RTC_writebyte(0x07, b);
}
uint8_t drv_RTC_getram() {
  return _drv_RTC_readbyte(0x07);
}
void drv_RTC_setminalarm(int minute);
void drv_RTC_sethouralarm(int hour);
void drv_RTC_clearalarm();
bool drv_RTC_isalarmon() {
  uint8_t buf = _drv_RTC_readbyte(0x0F);
  if ((buf & 0b00001000) == 0b00001000)return true;
  return false;
}
bool drv_RTC_getalarmflag() {
  uint8_t buf = _drv_RTC_readbyte(0x0E);
  if ((buf & 0b00001000) == 0b00001000)return true;
  return false;
}
void drv_RTC_clearalarmflag() {
  uint8_t buf = _drv_RTC_readbyte(0x0E);
  buf &= 0b11110111;
  _drv_RTC_writebyte(0x0E, buf);
}
void (*_drv_RTC_alarmcallback)();
void drv_RTC_setalarmcallback(void (*Callback)()) {
  _drv_RTC_alarmcallback = Callback;
}
void _drv_RTC_onalarmint() {
  drv_RTC_clearalarmflag();
  if (_drv_RTC_alarmcallback != NULL) {
    _drv_RTC_alarmcallback();
  }
}
void drv_RTC_clearallflags() {
  _drv_RTC_writebyte(0x0E, 0x00);
}
bool drv_RTC_getvlowflag() {
  // 电压过低以至于停振
  uint8_t buf = _drv_RTC_readbyte(0x0E);
  if ((buf & 0b00000010) == 0b00000010) {
    return true;
  }
  return false;
}

bool drv_RTC_getvdetflag() {
  // 电压不足以开启温补
  uint8_t buf = _drv_RTC_readbyte(0x0E);
  if ((buf & 0b00000001) == 0b00000001) {
    return true;
  }
  return false;
}
