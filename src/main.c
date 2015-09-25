/* Headers */
#include <stdio.h>                     /* for sprintf */

/*-----------------------------------------------------------------------------
 *  stm32f4 related libraries
 *-----------------------------------------------------------------------------*/
#include "stm32f4_system.h"
#include "stm32f4_evb.h"
#include "stm32f4_evb_lcd.h"           

#include "misc.h"        

#include "stm32f4xx.h"       

#include "stm32f4_evb_i2c_ee.h"        /* I2C */
#include "stm32f4_evb_i2c_tsc.h"       /* Touch Screen */
#include "stm32f4_evb_sdio_sd.h"       /* SD Card */

/*#include "usbd_cdc_core.h"       */
/*#include "usbd_cdc_vcp.h"       */
/*#include "usbd_usr.h"       */

/*-----------------------------------------------------------------------------
 *  TM Libraries
 *-----------------------------------------------------------------------------*/
#include "tm_stm32f4_gpio.h"
#include "tm_stm32f4_usart.h"
#include "tm_stm32f4_adc.h"
#include "tm_stm32f4_usb_vcp.h"        /* Usb cdc */


/*-----------------------------------------------------------------------------
 *  FreeRTOS
 *-----------------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "fonts.h"

#include "GUI.h"
/*#include "WM.h"                        [> emWin <]*/

#include "main.h"


/*-----------------------------------------------------------------------------
 *  Some Defines
 *-----------------------------------------------------------------------------*/
#define LEDOn(led) TM_GPIO_SetPinHigh(GPIOF, led)
#define LEDOff(led) TM_GPIO_SetPinLow(GPIOF, led)
#define LEDBlink(led) TM_GPIO_TogglePinValue(GPIOF, led)
#define LED1 GPIO_PIN_7
#define LED2 GPIO_PIN_8
#define LED3 GPIO_PIN_9
#define LED4 GPIO_PIN_10


void init() {
    SystemInit();

    // Init the LEDs 
    GPIO_Config();                     

    // For FreeRTOS 
    NVIC_Config();

    // Init for debuging
    USART_Config();

    // Open CRC for emWin
    CRC_Init();    

    // LCD
    STM324xG_LCD_Init();
    sEE_Init();        

    // Touch Screen
    TSC_Config();     

    // emWin
    GUI_Init();      
}

void CRC_Init() {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
}

void NVIC_Config() {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);  
}

void USART_Config() {
    TM_USART_Init(USART1, TM_USART_PinsPack_1, 115200);
    TM_USART_SetCustomStringEndCharacter(USART1, '\r');
}

int a = 0;
void blink1(void* p) {
    char c[50];
    for (;;) {
        sprintf(c, "Hello = %d\n\r", a++);
        TM_USART_Puts(USART1, c);
        vTaskDelay(1000);
    }
    vTaskDelete(NULL);
}

char buf[100];
void blink2(void* p) {
    for (;;) {
        /*TM_GPIO_TogglePinValue(GPIOF, GPIO_PIN_9);*/
        int t = TM_USART_Gets(USART1, buf, 90);
        if (t) {
            printf("get %s\r\n", buf);
        }
        // TODO some other test
        vTaskDelay(500);
    }
    vTaskDelete(NULL);
}

void blink3(void* p) {
    for (;;) {
        /*TM_GPIO_TogglePinValue(GPIOF, GPIO_PIN_9);*/
        GUI_DispString("Haha\n");
        // TODO some other test
        vTaskDelay(4000);
    }
    vTaskDelete(NULL);
}

// For overriding printf
int fputc(int c, FILE *f) {
    TM_USART_Putchar(USART1, (uint8_t)c);
    return c;
}


int main()
{

    init();
    LEDOn(LED1);
    LEDOn(LED2);

    /*GUI_DispString("OK!");*/

    /*USBD_Init(&USB_OTG_dev, USB_OTG_HS_CORE_ID, &USR_desc, &USBD_CDC_cb, &USR_cb);*/

    printf("On %d\r\n", 123);

    /*TM_USB_VCP_Init();*/
    /*while(1);*/

    uint8_t ret1 = xTaskCreate(blink1, "blink1", 200, NULL, 1, NULL);
    uint8_t ret2 = xTaskCreate(blink2, "blink2", 200, NULL, 1, NULL);
    uint8_t ret3 = xTaskCreate(blink3, "blink3", 200, NULL, 1, NULL);
    
    vTaskStartScheduler();  // should never return
        
    /*while(1) {*/
        /*LEDBlink(LED3);*/
        /*GUI_DispString("Hello World!");*/
        /*sleep(1000);*/
    /*}*/
}

void assert_failed(uint8_t* file, uint32_t line) {
    printf("[Error] Assert failed at file (%s : %u)\r\n", file, line);
    while(1);
}

void Log (char *c) {
    printf("[Log] %s\r\n", c);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  GPIO_Config
 *  Description:  Init GPIO
 *                GPIOF |  7  |  8  |  9  |  10  |
 *                       LED1  LED2  LED3   LED4
 * =====================================================================================
 */
void GPIO_Config()
{
    TM_GPIO_Init(GPIOF, 
            GPIO_PIN_10 | GPIO_PIN_9 | GPIO_PIN_8 | GPIO_PIN_7, 
            TM_GPIO_Mode_OUT, 
            TM_GPIO_OType_PP, 
            TM_GPIO_PuPd_NOPULL, 
            TM_GPIO_Speed_High);  
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

