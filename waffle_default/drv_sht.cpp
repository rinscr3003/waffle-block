#include "drv_sht.h"
#include <Wire.h>
#include "SHTSensor.h"

SHTSensor sht(SHTSensor::SHT3X);

void drv_initSHT3X() {
  //Wire.begin();
  sht.init();
  sht.setAccuracy(SHTSensor::SHT_ACCURACY_MEDIUM);
  Wire.beginTransmission(0x44);
  Wire.write(0x30);
  Wire.write(0x66);
  Wire.endTransmission();

}

bool drv_SHT_readsample() {
  return sht.readSample();
}


double drv_SHT_readhumi() {
  return sht.getHumidity();
}

double drv_SHT_readtemp() {
  return sht.getTemperature();
}
