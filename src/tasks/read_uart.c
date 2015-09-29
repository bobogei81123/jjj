#include <string.h>
#include "read_uart.h"

/* Read From Computer UART for debugging..
 */
char buf1[100];
void readUART1(void* p) {
    while (1) {
        int t = TM_USART_Gets(USART1, buf1, 90);
        if (t) {
            printf("[UART1] get = %s\r\n", buf1);
            int ret = strncmp(buf1, "send ", 5);
            if (!strncmp(buf1, "send ", 5)) {
                TM_USART_Puts(USART3, buf1+5);
                TM_USART_Putchar(USART3, '\r');
            }
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
            RFIDGets(buf3);
        }
        vTaskDelay(100);
    }
    vTaskDelete(NULL);
}
