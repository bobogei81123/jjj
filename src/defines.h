#ifndef TM_DEFINES_H
#define TM_DEFINES_H

#define true 1
#define false 0
#define NULL 0

#define USART_BUFFER_SIZE 256

#define LEDOn(led) TM_GPIO_SetPinHigh(GPIOF, led)
#define LEDOff(led) TM_GPIO_SetPinLow(GPIOF, led)
#define LEDBlink(led) TM_GPIO_TogglePinValue(GPIOF, led)
#define LED1 GPIO_PIN_7
#define LED2 GPIO_PIN_8
#define LED3 GPIO_PIN_9
#define LED4 GPIO_PIN_10

#endif
