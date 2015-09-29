#include "sonar_driver.h"

void (*SonarCallback)(int) = NULL; 

TM_HCSR04_t HCSR04;
void SonarInit() {
    int res = TM_HCSR04_Init(
            &HCSR04, 
            HCSR04_ECHO_GPIO,
            HCSR04_ECHO_PIN,
            HCSR04_TRIG_GPIO,
            HCSR04_TRIG_PIN
        );
    if (!res) {
        printf("[Error] Sonar init failed...\r\n");
    }
}

int SonarRead() {
    TM_HCSR04_Read(&HCSR04);
    int res = (int)(1.6666f * HCSR04.Distance);
    if (res > HCSR04_MIN_DIS && res < HCSR04_MAX_DIS) {
        printf("[Sonar] Get dis = %d\r\n", res);
        return res;
    }
    return -1;
}

void SonarSetCallback(void (*cbFunc)(int)) {
    SonarCallback = cbFunc;
}

void SonarScanTask(void* p) {
    while (1) {
        int t = SonarRead();
        if (t > 0 && t < HCSR04_VALID_DIS) {
            if (SonarCallback) {
                SonarCallback(t);
                vTaskDelete(NULL);
            }
        }
        vTaskDelay(50);
    }
}

