#include "read_uart.h"

/* Read From Computer UART for debugging..
 */
char buf1[100];
void readUART1(void* p) {
    while (1) {
        int t = TM_USART_Gets(USART1, buf1, 90);
        if (t) {
            printf("[UART1] get = %s\r\n", buf1);
        }
        vTaskDelay(100);
    }
    vTaskDelete(NULL);
}

/* Read From RFID UART for Data.
 */
char buf3[100];
void readUART3(void* p) {
    while (1) {
        int t = TM_USART_Gets(USART3, buf3, 90);
        if (t) {
            printf("[UART3] get = %s\r\n", buf3);
        }
        vTaskDelay(100);
    }
    vTaskDelete(NULL);
}
