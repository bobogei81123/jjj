#ifndef SONAR_DRIVER_H
#define SONAR_DRIVER_H

#include "tm_stm32f4_hcsr04.h"

#define HCSR04_ECHO_GPIO GPIOG
#define HCSR04_ECHO_PIN GPIO_PIN_13
#define HCSR04_TRIG_GPIO GPIOG
#define HCSR04_TRIG_PIN GPIO_PIN_14

#define HCSR04_MIN_DIS 10
#define HCSR04_MAX_DIS 300
#define HCSR04_VALID_DIS 200

void SonarInit();
int SonarRead();
void SonarScanTask(void*);

#endif
