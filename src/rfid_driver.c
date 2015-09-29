#include "rfid_driver.h"

void (*RFIDCallback)(int) = NULL; 

static void RFIDPuts(char *str) {
    TM_USART_Puts(USART3, str);
    TM_USART_Putchar(USART3, '\r');
}

#define CTOI(a) (a&15)

void RFIDGets(char *str) {
    str ++;
    char buf[40];
    int ret = sscanf(str, "%40[^,]", buf);
    if (ret == 1) {
        int len = strlen(buf);
        int result = CTOI(buf[len-2]) * 10 + CTOI(buf[len-1]);
        printf("scan = %d\r\n", result);
        if (RFIDCallback) {
            RFIDCallback(result);
        }
    }
}

void RFIDSendCommand(RFIDCommand command) {
    switch (command) {
        case kRFIDOn:
            RFIDPuts("set readmode 2");
            RFIDPuts("set runmilisecond 1000");
            printf("Start RFID\r\n");
            break;
        case kRFIDOff:
            RFIDPuts("set readmode 0");
            printf("End RFID\r\n");
            break;
    }
}


void RFIDSetCallback(void (*cbFunc)(int)) {
    RFIDCallback = cbFunc;
}

