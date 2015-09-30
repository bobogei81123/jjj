#ifndef GUI_MAIN_H
#define GUI_MAIN_H

#include "defines.h"
#include "GUI.h"
#include "WM.h"                        
#include "BUTTON.h"                   
#include "LISTVIEW.h"                
#include "TEXT.h"                
#include "DIALOG.h"

void GUITask();
static void GUIConfig();
static void GUICreate();
void _cbBkWin(WM_MESSAGE*);
void _cbPage1(WM_MESSAGE*);
void _cbButton(WM_MESSAGE*);
static void GUITitleCreate();
static void GUIIconViewCreate();
static void GUISubWindowCreate();
static void GUIMakeWinIn();
static void GUIMakeWinOut();
void ProcListviewChanged();

#endif
