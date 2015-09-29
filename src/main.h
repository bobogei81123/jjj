#ifndef MAIN_H

#define MAIN_H

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
/*-----------------------------------------------------------------------------
 *  TM Libraries
 *-----------------------------------------------------------------------------*/
#include "tm_stm32f4_gpio.h"
#include "tm_stm32f4_usart.h"
#include "tm_stm32f4_adc.h"
#include "tm_stm32f4_hcsr04.h"
/*-----------------------------------------------------------------------------
 *  FreeRTOS
 *-----------------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "fonts.h"
/*-----------------------------------------------------------------------------
 *  FreeRTOS
 *-----------------------------------------------------------------------------*/
#include "GUI.h"
#include "WM.h"                        
#include "BUTTON.h"                   
#include "LISTVIEW.h"                
/*-----------------------------------------------------------------------------
 *  File System
 *-----------------------------------------------------------------------------*/
#include "ff.h"                     

#include "defines.h"
#include "initial.h"
#include "mytasks.h"
#include "rfid_driver.h"
#include "sonar_driver.h"

#endif /* end of include guard: MAIN_H */
