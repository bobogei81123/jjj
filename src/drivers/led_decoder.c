#include "led_decoder.h"
#include "stm32f4xx.h"

int LEDDecoderValue = 0;
void LEDDecoderInit() {
    int i;
    for (i = 0; i < 3; i++) {
        TM_GPIO_Init(
            DecoderGPIO[i],
            DecoderPin[i],
            TM_GPIO_Mode_OUT,
            TM_GPIO_OType_PP,
            TM_GPIO_PuPd_DOWN,
            TM_GPIO_Speed_Medium
        );
    }
}

void LEDDecoderSet(int v) {
    LEDDecoderValue = v;
    int i;
    for (i=0; i<3; i++) {
        if (v & (1<<i)) {
            TM_GPIO_SetPinHigh(DecoderGPIO[i], DecoderPin[i]);
        } else {
            TM_GPIO_SetPinLow(DecoderGPIO[i], DecoderPin[i]);
        }
    }
}
