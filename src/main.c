#include "main.h"

void MainTask(void) {

    /*GUI_Init();*/
    WIDGET_SetDefaultEffect(&WIDGET_Effect_Simple);
    GUI_SetBkColor(0xF9F9F9);
    GUI_Clear();
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_FontComic24B_ASCII);
    GUI_DispStringHCenterAt("Smart Wardrobe", 120, 6);

    while (1) {
        GUI_Exec();
        GUI_Delay(100);
    }
    /*GUI_BMP_Draw(&bmpfile, 0, 0);*/
}


char bmpfile[4000];
UINT rd;
void _file_system_init() {
    FATFS FatFs;
    FRESULT res;
    if ((res = f_mount(&FatFs, "", 0)) == FR_OK) {
        printf("[FS] Mount Success\r\n");
    FIL fil;
    int res;
    if ((res = f_open(&fil, "shirtouts.gif", FA_READ)) == FR_OK) {

        res = f_read(&fil, bmpfile, 4000, &rd);
        if (!res) {

            printf("Read %d bytes\r\n", (int)rd);
        } else {
            printf("Err = %d\r\n", (int)res);
        }

        f_close(&fil);
    } else {
        char x[30];
        printf("Open File Err = %d\n", res);
    }
    } else {
        printf("[FS] File Mount Err = %d\r\n", res);
    }
}

void _cbRFID(int res) {
    printf("[Callback RFID] Get = %d\r\n", res);
}

void _cbSonar(int res) {
    printf("[Callback Sonar] Get = %d\r\n", res);
}

int main()
{

    init();
    printf("System On and Finish Init\r\n");
    LEDOn(LED1);
    LEDOn(LED2);


    _file_system_init();

    printf("Init done\r\n");
    SonarInit();
    RFIDSendCommand(kRFIDOn);
    RFIDSetCallback(_cbRFID);
    RFIDSetCallback(_cbSonar);

    /*LEDDecoderSet(1);*/

    /*while (1) {*/
        
        /*printf("Dis = %d\r\n", SonarRead());*/
        
        /*sleep(100);*/
    /*}*/


    /*int res = GUI_GIF_Draw((const void*) bmpfile, rd, 50, 50);*/

    /* Tasks */
    xTaskCreate(heartbeat, "heartbeat", 200, NULL, 1, NULL);
    xTaskCreate(readUART1, "UART1", 300, NULL, 1, NULL);
    xTaskCreate(readUART3, "UART3", 300, NULL, 1, NULL);
    /*xTaskCreate(SonarScanTask, "sonar", 200, NULL, 1, NULL);*/
    xTaskCreate(GUITask, "gui_main", 1000, NULL, 1, NULL);
    xTaskCreate(touchScreenUpdate, "touch", 200, NULL, 1, NULL);
    
    vTaskStartScheduler();  
}

