#ifndef LED_DECODER_H
#define LED_DECODER_H

#include "tm_stm32f4_gpio.h"

GPIO_TypeDef* const DecoderGPIO[] = {GPIOG, GPIOG, GPIOG};
uint16_t const DecoderPin[] = {GPIO_PIN_5, GPIO_PIN_5, GPIO_PIN_5};

void LEDDecoderInit();
void LEDDecoderSet(int);

#endif
