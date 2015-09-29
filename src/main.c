#include "main.h"

void _cbButton(WM_MESSAGE *pMsg) {
    switch (pMsg->MsgId) {
        case WM_PID_STATE_CHANGED:;
            WM_PID_STATE_CHANGED_INFO* info = pMsg->Data.p;
            printf("Button state change - (%d, %d) %d\r\n", info->x, info->y, (int)info->State);
            break;
        case WM_NOTIFICATION_CLICKED:
            printf("Clicked \r\n");
            break;
        default:
            BUTTON_Callback(pMsg);
            break;
    }
}

void _cbBkWin(WM_MESSAGE *pMsg) {
    switch (pMsg->MsgId) {
        case WM_NOTIFY_PARENT:;
            int code = pMsg->Data.v;
            switch (code) {
                case WM_NOTIFICATION_CLICKED:
                    printf("Child Clicked\r\n");
                    break;
                case WM_NOTIFICATION_SEL_CHANGED:
                    printf("Selected Changed\r\n");
                    break;
            }
            break;
        default:
            WM_DefaultProc(pMsg);
    }
}

static void ButtonCreate(void) {
    WM_SetCallback(WM_HBKWIN, _cbBkWin);
    BUTTON_Handle hButton;
    GUI_SetDefaultFont(&GUI_FontComic18B_ASCII);

    hButton = BUTTON_Create(110, 140, 100, 40, GUI_ID_OK, WM_CF_SHOW);
    BUTTON_SetFont(hButton, &GUI_FontComic18B_ASCII);
    BUTTON_SetText(hButton, "Click me...");
    WM_SetCallback(hButton, _cbButton);

    /*LISTVIEW_Handle hListview;*/
    /*hListview = LISTVIEW_CreateEx(100, 40, 120, 80, NULL, WM_CF_SHOW, 0, 1234);*/
    /*LISTVIEW_AddColumn( hListview, 60 ,*/
            /*"Cloth",*/
            /*GUI_TA_HCENTER | GUI_TA_VCENTER );*/
    /*LISTVIEW_AddColumn( hListview, 60 ,*/
            /*"Position",*/
            /*GUI_TA_HCENTER | GUI_TA_VCENTER );*/

    /*const char* name[2] = {"123", "456"};*/
    /*LISTVIEW_AddRow( hListview, (GUI_ConstString*)name);*/

    ICONVIEW_Handle hIconView = ICONVIEW_CreateEx(40, 40, 165, 85, NULL, WM_CF_SHOW, 0, 2345, 75, 75);
    ICONVIEW_SetTextColor(hIconView, ICONVIEW_CI_UNSEL, GUI_BLACK);
    ICONVIEW_SetTextColor(hIconView, ICONVIEW_CI_SEL, 0x00FFFF);
    ICONVIEW_SetBkColor(hIconView, ICONVIEW_CI_BK, 0xE0E0E0);
    extern GUI_BITMAP bmshirtin, bmshirtout;
    ICONVIEW_AddBitmapItem(hIconView, &bmshirtin,  "hao123");
    ICONVIEW_AddBitmapItem(hIconView, &bmshirtout,  "hao321");

}

void MainTask(void) {

    /*GUI_Init();*/
    WIDGET_SetDefaultEffect(&WIDGET_Effect_Simple);
    GUI_SetBkColor(0xF9F9F9);
    GUI_Clear();
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_FontComic24B_ASCII);
    GUI_DispStringHCenterAt("ABC 123 456", 160, 5);
    ButtonCreate();

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
    printf("[Callback] Get = %d\r\n", res);
}


int main()
{
    printf("System On\r\n");

    init();
    LEDOn(LED1);
    LEDOn(LED2);

    _file_system_init();

    printf("Init done\r\n");
    SonarInit();
    RFIDSendCommand(kRFIDOn);
    RFIDSetCallback(_cbRFID);

    /*while (1) {*/
        
        /*printf("Dis = %d\r\n", SonarRead());*/
        
        /*sleep(100);*/
    /*}*/


    /*int res = GUI_GIF_Draw((const void*) bmpfile, rd, 50, 50);*/

    /* Tasks */
    xTaskCreate(heartbeat, "heartbeat", 200, NULL, 1, NULL);
    xTaskCreate(readUART1, "UART1", 200, NULL, 1, NULL);
    xTaskCreate(readUART3, "UART3", 300, NULL, 1, NULL);
    xTaskCreate(MainTask, "gui_main", 1000, NULL, 1, NULL);
    xTaskCreate(touchScreenUpdate, "touch", 200, NULL, 1, NULL);
    
    vTaskStartScheduler();  
}

