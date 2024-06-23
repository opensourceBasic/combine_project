#pragma once

#include "data_handler.h"

typedef struct {
    int box_x;
    int box_y;
    DataHandler* DB;
} Display;

void Display_Init(Display* display, DataHandler* handler);
void Display_SetCursorPosition(int x, int y);
void Display_ShowMenu(Display* display);
void Display_ShowClientMenu(Display* display);
void Display_ShowMileageMenu(Display* display);
void Display_ShowHistoryMenu(Display* display);
void Display_DailyMenu(Display* display);
void Display_Register(Display* display);
void Display_CleanDisplay();