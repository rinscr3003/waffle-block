#include <stdint.h>
const uint8_t BQ24296M_I2C_ADDR = 0x6B;

void drv_initCharge();
void drv_CHARGE_setcharge(bool ce);
uint8_t drv_CHARGE_getstatusreg();
uint8_t drv_CHARGE_getfaultreg();
