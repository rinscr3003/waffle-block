#include "drv_misc.h"
#include <Arduino.h>

void drv_initMisc() {
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, HIGH);
}
void drv_MISC_settopled(bool s) {
  digitalWrite(LED1, s ? LOW : HIGH);
}
