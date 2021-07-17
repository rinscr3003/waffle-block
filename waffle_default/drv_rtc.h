#include <time.h>

void drv_initRTC();
void drv_RTC_settime(struct tm *timePtr);
struct tm *drv_RTC_gettime();
void drv_RTC_synctime();
void drv_RTC_setram(uint8_t b);
uint8_t drv_RTC_getram();
void drv_RTC_synctime();
void drv_RTC_setminalarm(int minute);
void drv_RTC_sethouralarm(int hour);
//void drv_RTC_setweekalarm(int weekday);
//void drv_RTC_setdayalarm(int day);
void drv_RTC_clearalarm();
bool drv_RTC_getalarmflag();
void drv_RTC_clearalarmflag();
void drv_RTC_getvlowflag(); // 电压过低以至于停振
void drv_RTC_getvdetflag(); // 电压不足以开启温补
