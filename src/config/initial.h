#ifndef INITIAL_H
#define INITIAL_H

#include "stm32f4_evb.h"
#include "stm32f4_evb_lcd.h"           
#include "tm_stm32f4_gpio.h"
#include "tm_stm32f4_usart.h"

#include "ff.h"

void CRC_Init();
void USART_Config();
void GPIO_Config();
void NVIC_Config();
void init();

#endif
