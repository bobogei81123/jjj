#include "gui_main.h"

int curId;
void GUITask() {

    curId = GUI_ID_USER;
    GUIConfig();
    GUICreate();

    while (1) {
        WM_Exec();
        GUI_Delay(100);
    }
    /*GUI_BMP_Draw(&bmpfile, 0, 0);*/
}

static void GUIConfig() {
    WIDGET_SetDefaultEffect(&WIDGET_Effect_Simple);
    GUI_SetBkColor(0xF9F9F9);
    GUI_Clear();
    GUI_SetDefaultFont(&GUI_FontComic18B_ASCII);
    TEXT_SetDefaultFont(&GUI_FontComic18B_ASCII);
    TEXT_SetDefaultTextColor(GUI_BLACK);

#define SET_DEFAULT_FLEX_SKIN(widget) widget##_SetDefaultSkin(widget##_SKIN_FLEX)
    /*SET_DEFAULT_FLEX_SKIN(BUTTON);*/
    /*SET_DEFAULT_FLEX_SKIN(MULTIPAGE);*/

    WM_SetCallback(WM_HBKWIN, _cbBkWin);
}

static void GUICreate(void) {

    GUITitleCreate();
    GUIIconViewCreate();
    GUISubWindowCreate();

    /*BUTTON_Handle hButton;*/

    /*hButton = BUTTON_Create(110, 140, 100, 40, GUI_ID_OK, WM_CF_SHOW);*/
    /*BUTTON_SetFont(hButton, &GUI_FontComic18B_ASCII);*/
    /*BUTTON_SetText(hButton, "Click me...");*/
    /*extern const GUI_BITMAP bmgonext;*/
    /*BUTTON_SetBitmap(hButton, BUTTON_BI_UNPRESSED, &bmgonext);*/
    /*WM_SetCallback(hButton, _cbButton);*/



}

static void GUITitleCreate() {
    GUI_SetColor(GUI_BLACK);
    GUI_SetFont(&GUI_FontComic24B_ASCII);
    GUI_DispStringHCenterAt("Smart Wardrobe", 120, 6);
}

ICONVIEW_Handle hIconView;
static void GUIIconViewCreate() {
    hIconView = ICONVIEW_CreateEx(40, 40, 165, 85, NULL, WM_CF_SHOW, 0, ++curId, 75, 75);
    ICONVIEW_SetTextColor(hIconView, ICONVIEW_CI_UNSEL, GUI_BLACK);
    ICONVIEW_SetTextColor(hIconView, ICONVIEW_CI_SEL, 0x00FFFF);
    ICONVIEW_SetBkColor(hIconView, ICONVIEW_CI_BK, 0xE0E0E0);
    extern GUI_BITMAP bmshirtin, bmshirtout;
    ICONVIEW_AddBitmapItem(hIconView, &bmshirtin,  "Put in");
    ICONVIEW_AddBitmapItem(hIconView, &bmshirtout,  "Take out");
}

WM_HWIN hWinIn, hWinOut;
static void GUISubWindowCreate() {
    GUIMakeWinIn();
    GUIMakeWinOut();
}


static void GUIMakeWinIn() {
    hWinIn = WINDOW_CreateEx(
        20, 140, 200, 150,
        0,
        WM_CF_SHOW,
        0,
        ++curId,
        0
    );
    TEXT_CreateEx(
        40, 50, 120, 50,
        hWinIn,
        WM_CF_SHOW,
        TEXT_CF_HCENTER, 
        ++curId,
        "Please put in\r\nyour clothes!"
    );
}

MULTIPAGE_Handle hMultipage;
LISTVIEW_Handle hListview;
static void GUIMakeWinOut() {
    hWinOut = WINDOW_CreateEx(
        20, 140, 200, 150,
        0,
        WM_CF_SHOW,
        0,
        ++curId,
        0
    );
    hMultipage = MULTIPAGE_CreateEx(
        10, 10, 180, 130,
        hWinOut,
        WM_CF_SHOW,
        0,
        ++curId
    );
    MULTIPAGE_SetSkin(hMultipage, MULTIPAGE_SKIN_FLEX);

    WM_HWIN hMultipageWindow1 = WINDOW_CreateEx(
        0, 0, 180, 110,
        hMultipage,
        0,
        0,
        ++curId,
        _cbPage1
    );
    WINDOW_SetBkColor(hMultipageWindow1, GUI_RED);
    MULTIPAGE_AddPage(hMultipage, hMultipageWindow1, "Custom");

    hListview = LISTVIEW_CreateEx(0, 0, 180, 130,
        hMultipageWindow1,
        WM_CF_SHOW,
        0,
        ++curId
    );
    LISTVIEW_AddColumn( hListview, 120 ,
            "Cloth",
            GUI_TA_HCENTER | GUI_TA_VCENTER );
    LISTVIEW_AddColumn( hListview, 60 ,
            "Position",
            GUI_TA_HCENTER | GUI_TA_VCENTER );

    const char* name[][2] = {
        {"Polka dot long dress", "40"},
        {"White Shirt", "60"}
    };
    LISTVIEW_AddRow( hListview, (GUI_ConstString*)name[0] );
    LISTVIEW_AddRow( hListview, (GUI_ConstString*)name[1] );


    WM_HWIN hMultipageWindow2 = WINDOW_CreateEx(
        0, 0, 180, 110,
        hMultipage,
        0,
        0,
        ++curId,
        NULL
    );
    WINDOW_SetBkColor(hMultipageWindow2, GUI_BLUE);
    MULTIPAGE_AddPage(hMultipage, hMultipageWindow2, "Suggest");
}

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
                case WM_NOTIFICATION_SEL_CHANGED:
                    printf("Selected Changed\r\n");
                    ProcSelectChanged();
                    break;
                case WM_NOTIFICATION_CLICKED:
                    printf("Child Clicked\r\n");
                    break;
            }
            break;
        default:
            WM_DefaultProc(pMsg);
    }
}

void _cbPage1(WM_MESSAGE *pMsg) {
    switch (pMsg->MsgId) {
        case WM_NOTIFY_PARENT:;
            int code = pMsg->Data.v;
            switch (code) {
                case WM_NOTIFICATION_SEL_CHANGED:
                    ProcListviewChanged();
                    break;
            }
            break;
        default:
            WM_DefaultProc(pMsg);
    }
}

void ProcListviewChanged() {
    int currentSelected = LISTVIEW_GetSel(hListview);
    char buf[10];
    LISTVIEW_GetItemText(hListview, 1, currentSelected, buf, 10);
    int dis;
    int res = sscanf(buf, "%d", &dis);
    if (res == 1) {
        printf("[Listview] sel = %d, dis = %d\r\n",
                currentSelected,
                dis);
        int led = (dis / 10) - 1;
        if (led >= 0 && led < 6) {
            LEDDecoderSet(led);
        }
    }
}

void ProcSelectChanged() {
    int currentSelected = ICONVIEW_GetSel(hIconView);
    if (currentSelected == 0) {
        WM_BringToTop(hWinIn);
        WM_Paint(hWinIn);
        /*xTaskCreate(scanClothesChanged, "clothes", 300, NULL, 1, NULL);*/
    } else {
        WM_BringToTop(hWinOut);
        WM_Paint(hWinOut);
    }
}
