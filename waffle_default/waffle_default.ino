#include "drv_rgbled.h"
#include "drv_charge.h"
#include "drv_rtc.h"
//#include "drv_sht.h"
//#include "drv_led.h"
//#include "drv_tft.h"

void setup() {
  // put your setup code here, to run once:
  drv_initCharge();
  drv_initRGBLED();
  drv_initRTC();
}

void loop() {
  // put your main code here, to run repeatedly:

}
