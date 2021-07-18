#include <time.h>
#include <stdint.h>

const uint8_t RX8025T_I2C_ADDR = 0x32;

void drv_initRTC();
void drv_RTC_settime(struct tm *timePtr);
struct tm drv_RTC_gettime();
void drv_RTC_synctime();
void drv_RTC_setram(uint8_t b);
uint8_t drv_RTC_getram();
void drv_RTC_syncintime();
void drv_RTC_syncouttime();
//void drv_RTC_setminalarm(int minute);
//void drv_RTC_sethouralarm(int hour);
//void drv_RTC_setweekalarm(int weekday);
//void drv_RTC_setdayalarm(int day);
//bool drv_RTC_isalarmon();
//void drv_RTC_clearalarm();
//bool drv_RTC_getalarmflag();
//void drv_RTC_clearalarmflag();
//void drv_RTC_setalarmcallback(void (*Callback)());
void drv_RTC_clearallflags();
bool drv_RTC_getvlowflag(); // 电压过低以至于停振
bool drv_RTC_getvdetflag(); // 电压不足以开启温补
