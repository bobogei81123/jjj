#include "touch_screen.h"

const int ScreenWidth = 240;
const int ScreenHeight = 320;
const int DeltaX = 0;
const int DeltaY = -9;

TSC_STATE *tsc_info;
void touchScreenUpdate(void* p) {
    while (1) {
        tsc_info = TSC_TS_GetState();
        int x, y;
        x = (tsc_info->Z > 30 ? 
                ScreenWidth - (int)(0.001 * ScreenWidth * tsc_info->X) + DeltaX : -1);
        y = (tsc_info->Z > 30 ? 
                (int)(0.001 * ScreenHeight * tsc_info->Y) + DeltaY : -1);
#ifdef TOUCH_SCREEN_DEBUG
        printf("[TouchScreen] (%d, %d)\r\n", x, y);
#endif
        GUI_TOUCH_StoreState(x, y);
        vTaskDelay(40);
    }
}
