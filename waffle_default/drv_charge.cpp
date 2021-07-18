#include "drv_charge.h"
#include <Wire.h>
#include <stdint.h>

uint8_t _drv_CHARGE_readbyte(uint8_t addr) {
  uint8_t rdData;
  uint8_t rdDataCount;
  do {
    Wire.beginTransmission(BQ24296M_I2C_ADDR);
    Wire.write(addr);
    Wire.endTransmission(false); // Restart
    delay(10);
    rdDataCount = Wire.requestFrom(BQ24296M_I2C_ADDR, 1);
  } while (rdDataCount == 0);
  while (Wire.available()) {
    rdData = Wire.read();
  }
  return rdData;
}

void _drv_CHARGE_writebyte(uint8_t addr, uint8_t data) {
  Wire.beginTransmission(BQ24296M_I2C_ADDR);
  Wire.write(addr);
  Wire.write(data);
  Wire.endTransmission();
}

void drv_initCharge() {
  //Wire.begin();
  _drv_CHARGE_writebyte(0x00, 0b00111100); // VINDPM=4.44V, IINLIM=1.0A
  _drv_CHARGE_writebyte(0x01, 0b00011011); // OTG DISABLED, CHARGE ENABLED, VSYSMIN=3.5V
  _drv_CHARGE_writebyte(0x02, 0b00000000); // ICHG=0.512A
  _drv_CHARGE_writebyte(0x03, 0b00010001); // IPRECHG=0.128A, ITERM=0.128A
  _drv_CHARGE_writebyte(0x04, 0b10111110); // VBAT=4.2V, VPRE=3.0V, VRECHG=0.1V
  _drv_CHARGE_writebyte(0x05, 0b10000010); // CHGTERM ENABLED, WDT DISABLED, TIM=12h
  _drv_CHARGE_writebyte(0x06, 0b01110001); // OTP=80
  _drv_CHARGE_writebyte(0x07, 0b01001011); // TIM*=2
}

void drv_CHARGE_setcharge(bool ce) {
  uint8_t buf = _drv_CHARGE_readbyte(0x01);
  buf &= 0b11101111;
  buf |= ((uint8_t)ce) << 4;
  _drv_CHARGE_writebyte(0x01, buf);
}

uint8_t drv_CHARGE_getstatusreg() {
  return _drv_CHARGE_readbyte(0x08);
}
uint8_t drv_CHARGE_getfaultreg() {
  return _drv_CHARGE_readbyte(0x09);
}
