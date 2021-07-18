#include "drv_button.h"
#include <AceButton.h>
#include <stdint.h>
using namespace ace_button;

AceButton buttonA(13);
AceButton buttonB(15);
AceButton buttonL(39);

typedef void (*FP_callback)(uint8_t, uint8_t, uint8_t);
volatile uint8_t _drv_BUTTON_appid = 0;
FP_callback _drv_BUTTON_callbacks[256];

void _drv_BUTTON_handleEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {

  // Print out a message for all events, for both buttons.
  Serial.print(F("handleEvent(): pin: "));
  Serial.print(button->getPin());
  Serial.print(F("; eventType: "));
  Serial.print(eventType);
  Serial.print(F("; buttonState: "));
  Serial.println(buttonState);

  uint8_t keyid = 0;

  switch (button->getPin()) {
    case 13:
      keyid = 1;
      break;
    case 15:
      keyid = 2;
      break;
    case 39:
      keyid = 3;
      break;
  }
  if (_drv_BUTTON_callbacks[_drv_BUTTON_appid] != NULL) {
    _drv_BUTTON_callbacks[_drv_BUTTON_appid](keyid, eventType, buttonState);
  }
}

void _drv_BUTTON_looper(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  for (;;) // A Task shall never return or exit.
  {
    buttonL.check();
    buttonA.check();
    buttonB.check();
    vTaskDelay(5);
  }
}

void drv_initBUTTON() {
  pinMode(13, INPUT);
  pinMode(15, INPUT);
  pinMode(39, INPUT);
  ButtonConfig* buttonConfig = ButtonConfig::getSystemButtonConfig();
  buttonConfig->setEventHandler(_drv_BUTTON_handleEvent);
  buttonConfig->setFeature(ButtonConfig::kFeatureClick);
  buttonConfig->setFeature(ButtonConfig::kFeatureDoubleClick);
  buttonConfig->setFeature(ButtonConfig::kFeatureLongPress);
  buttonConfig->setFeature(ButtonConfig::kFeatureRepeatPress);
  buttonConfig->setClickDelay(500);
  xTaskCreatePinnedToCore(
    _drv_BUTTON_looper
    ,  "_drv_BUTTON_looper"   // A name just for humans
    ,  1024  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL
    ,  ARDUINO_RUNNING_CORE);
}
void drv_BUTTON_setcallback(uint8_t appid, void (*Callback)(uint8_t, uint8_t, uint8_t)) {
  _drv_BUTTON_callbacks[appid] = Callback;
}

void drv_BUTTON_setapp(uint8_t appid) {
  _drv_BUTTON_appid = appid;
}
