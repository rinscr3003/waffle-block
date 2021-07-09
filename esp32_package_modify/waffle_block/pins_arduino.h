#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>

#define EXTERNAL_NUM_INTERRUPTS 16
#define NUM_DIGITAL_PINS        40
#define NUM_ANALOG_INPUTS       16

#define analogInputToDigitalPin(p)  (((p)<20)?(esp32_adc2gpio[(p)]):-1)
#define digitalPinToInterrupt(p)    (((p)<40)?(p):-1)
#define digitalPinHasPWM(p)         (p < 34)

static const uint8_t TX = 1;
static const uint8_t RX = 3;

static const uint8_t SDA = 23;
static const uint8_t SCL = 22;

static const uint8_t SS    = 12;
static const uint8_t MOSI  = 26;
static const uint8_t MISO  = 27;
static const uint8_t SCK   = 14;

static const uint8_t LCD_CE     = 12;
static const uint8_t LCD_MOSI   = 26;
static const uint8_t SPI_MISO   = 27;
static const uint8_t LCD_SCK  	= 14;
static const uint8_t LCD_DC     = 25;
static const uint8_t LCD_RST    = 33;
static const uint8_t LCD_BL     = 32;

static const uint8_t BATADC = 35;
static const uint8_t RTCALM = 34;

static const uint8_t K1 = 13;
static const uint8_t K2 = 15;
static const uint8_t K3 = 39;

static const uint8_t LED1   = 2;
static const uint8_t RGBLED = 5;
static const uint8_t BOEN   = 4;

static const uint8_t PORTIO_A = 18;
static const uint8_t PORTIO_B = 19;

static const uint8_t BQ_CE = 21;

static const uint8_t I2C_ADDR_BQ  = 0x6b;
static const uint8_t I2C_ADDR_RTC = 0x32;
static const uint8_t I2C_ADDR_SHT = 0x44;

#endif /* Pins_Arduino_h */
