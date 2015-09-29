#ifndef RFID_DRIVER_H
#define RFID_DRIVER_H

#include "defines.h"
#include "tm_stm32f4_usart.h"

typedef enum {
    kRFIDOn,
    kRFIDOff,
} RFIDCommand;

static void RFIDPuts(char*);
void RFIDGets(char*);
void RFIDSendCommand(RFIDCommand);

#endif

