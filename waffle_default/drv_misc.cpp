#include "drv_misc.h"

void drv_initMisc() {
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, HIGH);
}
void drv_MISC_settoplight(bool s) {
  digitalWrite(LED1, s ? LOW : HIGH);
}
void drv_MISC_setwifi(String ssid, String pass) {
  ;
}
