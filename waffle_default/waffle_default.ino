#include "drv_rgbled.h"
#include <Wire.h>
#include "drv_charge.h"
#include "drv_rtc.h"
#include "drv_sht.h"
//#include "drv_led.h"
//#include "drv_tft.h"
//#include "drv_button.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  drv_initCharge();
  drv_initRGBLED();
  drv_initRTC();
  drv_initSHT3X();

  drv_RGBLED_setbrightness(150);
  drv_RGBLED_setcolor(0, 0, 255, 255);
  drv_RGBLED_setcolor(1, 255, 64, 64);

  struct tm timeptr;
  timeptr.tm_year = 2021 - 1900;
  timeptr.tm_mon = 7 - 1;
  timeptr.tm_mday = 18;
  timeptr.tm_hour = 11;
  timeptr.tm_min = 45;
  timeptr.tm_sec = 0;
  drv_RTC_settime(&timeptr);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (drv_SHT_readsample()) {
    Serial.print("SHT:\n");
    Serial.print("  RH: ");
    Serial.print(drv_SHT_readhumi(), 2);
    Serial.print("\n");
    Serial.print("  T:  ");
    Serial.print(drv_SHT_readtemp(), 2);
    Serial.print("\n");
  } else {
    Serial.print("Error in readSample()\n");
  }
  struct tm timeptr = drv_RTC_gettime();
  int t = mktime(&timeptr);
  Serial.printf("timestamp=%d\n", t);
  drv_RTC_syncouttime();
  t = time(NULL);
  Serial.printf("timestamplocal=%d\n", t);
  delay(2000);
}
