#include "heartbeat.h"

void heartbeat(void* p) {
    while (1) {
        LEDBlink(LED1);
        vTaskDelay(1000);
    }
    vTaskDelete(NULL);
}
