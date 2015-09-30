#include "initial.h"

void CRC_Init() {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
}

void NVIC_Config() {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);  
}

void USART_Config() {
    TM_USART_Init(USART1, TM_USART_PinsPack_1, 115200);
    TM_USART_SetCustomStringEndCharacter(USART1, '\r');
    TM_USART_Init(USART3, TM_USART_PinsPack_1, 115200);
    TM_USART_SetCustomStringEndCharacter(USART3, '\r');
}

// Mount the file system
void file_system_init() {
    return;
    FATFS FatFs;
    FRESULT res;
    if ((res = f_mount(&FatFs, "", 0)) == FR_OK) {
        printf("[FS] Mount Success\r\n");
    } else {
        printf("[FS] File Mount Err = %d\r\n", res);
    }
}

void GPIO_Config()
{
    TM_GPIO_Init(GPIOF, 
            GPIO_PIN_10 | GPIO_PIN_9 | GPIO_PIN_8 | GPIO_PIN_7, 
            TM_GPIO_Mode_OUT, 
            TM_GPIO_OType_PP, 
            TM_GPIO_PuPd_NOPULL, 
            TM_GPIO_Speed_High);  
}

void init() {
    SystemInit();

    // Init the LEDs 
    GPIO_Config();                     

    // For FreeRTOS 
    NVIC_Config();

    // Init for debuging
    USART_Config();

    // LED Controller Init
    LEDDecoderInit();

    // Open CRC for emWin
    CRC_Init();    

    // LCD
    STM324xG_LCD_Init();
    sEE_Init();        

    // Touch Screen
    TSC_Config();     

    // emWin
    GUI_Init();      

    // File System
    file_system_init();
}
