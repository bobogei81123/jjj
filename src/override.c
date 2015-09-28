#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "tm_stm32f4_usart.h"

// For overriding printf
int fputc(int c, FILE *f) {
    TM_USART_Putchar(USART1, (uint8_t)c);
    return c;
}

void Log (char *c) {
    printf("[Log] %s\r\n", c);
}

void assert_failed(uint8_t* file, uint32_t line) {
    printf("[Error] Assert failed at file (%s : %u)\r\n", file, line);
    while(1);
}

void vApplicationTickHook(void) {
}

void vApplicationMallocFailedHook(void) {
    taskDISABLE_INTERRUPTS();
    for(;;);
}

void vApplicationIdleHook(void) {
}

void vApplicationStackOverflowHook(xTaskHandle pxTask, signed char *pcTaskName) {
    (void) pcTaskName;
    (void) pxTask;
    printf("[Error] Task (%s) stack overflow\r\n", pcTaskName);
    taskDISABLE_INTERRUPTS();
    for(;;);
}

