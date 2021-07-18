#include <AceButton.h>
#include <stdint.h>
using namespace ace_button;

void drv_initBUTTON();
void drv_BUTTON_setcallback(uint8_t appid, void (*Callback)(uint8_t, uint8_t, uint8_t));
void drv_BUTTON_setapp(uint8_t appid);
