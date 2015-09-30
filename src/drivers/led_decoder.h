#ifndef LED_DECODER_H
#define LED_DECODER_H

#include "tm_stm32f4_gpio.h"

GPIO_TypeDef* const DecoderGPIO[] = {GPIOH, GPIOH, GPIOH};
uint16_t const DecoderPin[] = {GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11};

void LEDDecoderInit();
void LEDDecoderSet(int);

#endif
