#include <WiFi.h>
#include "time.h"
#include <AceButton.h>
using namespace ace_button;
AceButton buttonM(K3);
AceButton buttonA(K1);
AceButton buttonB(K2);

String ssid       = "wfyz-teacher";
String password   = "";

void handleEvent(AceButton*, uint8_t, uint8_t);

void TaskKey( void *pvParameters );
void TaskApp( void *pvParameters );
void TaskWifikeep( void *pvParameters );
void TaskNTP( void *pvParameters );
#include "looper.ino"

#include "apps.ino"

void setup() {
  // put your setup code here, to run once:

  //Init button pins
  pinMode(K1, INPUT);
  pinMode(K2, INPUT);
  pinMode(K3, INPUT);

  //Init button config
  ButtonConfig* buttonConfig = ButtonConfig::getSystemButtonConfig();
  buttonConfig->setEventHandler(handleEvent);
  buttonConfig->setFeature(ButtonConfig::kFeatureClick);
  buttonConfig->setFeature(ButtonConfig::kFeatureDoubleClick);
  buttonConfig->setFeature(ButtonConfig::kFeatureLongPress);
  buttonConfig->setFeature(ButtonConfig::kFeatureRepeatPress);
  buttonConfig->setClickDelay(500);//500ms for click
}

void loop() {
  // put your main code here, to run repeatedly:

}
