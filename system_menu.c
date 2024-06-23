#include "system_menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

void Display_Init(Display* display, DataHandler* handler)
{
    display->box_x = 30;
    display->box_y = 10;
    display->DB = handler;
}

void Display_SetCursorPosition(int x, int y)
{
#ifdef _WIN32
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    printf("\033[%d;%dH", y + 1, x + 1);
#endif
}

void Display_CleanDisplay()
{
    system("cls");
}

void Display_ShowMenu(Display* display)
{
    Display_CleanDisplay();
    Display_SetCursorPosition(0, 0);
    printf("------------Menu-------------\n");
    printf("0. 프로그램 종료\n");
    printf("1. 고객관리\n");
    printf("2. 마일리지 관리\n");
    printf("3. 서비스 히스토리\n");
    // printf("4. 일정관리\n");

    Display_SetCursorPosition(0, 6);
    printf("---------오늘의 일정----------\n");

    Display_SetCursorPosition(0, 7);
    // 오늘의 일정 부분 출력

    char selection = 0;
    while (1)
    {
        while (!_kbhit()) {}
        selection = _getch();

        switch (selection) {
        case '0':
            return;
            break;
        case '1':
            Display_ShowClientMenu(display);
            break;
        case '2':
            Display_ShowMileageMenu(display);
            break;
        case '3':
            Display_ShowHistoryMenu(display);
            break;
        case '4':
            Display_DailyMenu(display);
            break;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
            Sleep(1000);
        }
    }
}

void Display_ShowClientMenu(Display* display)
{
    Display_CleanDisplay();
    printf("------------고객관리-------------\n");
    printf("1. 고객찾기\n");
    printf("2. 고객추가\n");
    printf("\n");

    int repeat = -1;
    char selection = 0;
    while (repeat == -1) {
        while (!_kbhit()) {}
        selection = _getch();

        char birthday[64];
        switch (selection)
        {
        case '1':
            printf("---------------------------------\n");
            printf("찾으려는 고객의 생년월일을 입력해주세요!!\n");
            printf("-> 메인으로 돌아가려면 'm'를 입력하세요\n");
            while (repeat == -1)
            {
                printf("\n");
                printf(">> ");
                scanf("%s", birthday);
                if (strcmp(birthday, "m") == 0)
                {
                    repeat = 0;
                    continue;
                }
                printf("\n");
                repeat = DataHandler_FindClient(display->DB, birthday);
                if (repeat != -1) {
                    printf("\n");
                    printf("메인으로 돌아가려면 'm'를 입력하세요>> ");
                    scanf("%s", birthday);
                    if (strcmp(birthday, "m") == 0) Display_ShowMenu(display);
                    else repeat = -1;
                }
            }
            break;
        case '2':
            printf("---------------------------------\n");
            printf("추가하려는 고객의 정보를 입력해주세요!!\n");
            DataHandler_AddClient(display->DB);
            repeat = 0;
            break;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
            Sleep(1000);
        }
    }
    Display_ShowMenu(display);
}

void Display_ShowMileageMenu(Display* display)
{
    Display_CleanDisplay();
    printf("----------마일리지 관리-----------\n");
    printf("1. 마일리지 추가\n");
    printf("2. 마일리지 사용\n");
    printf("\n");

    int repeat = -1;
    char selection = 0;
    while (repeat == -1)
    {
        while (!_kbhit()) {}
        selection = _getch();

        char birthday[64];
        switch (selection)
        {
        case '1':
            printf("---------------------------------\n");
            printf("찾으려는 고객의 생년월일을 입력해주세요!!\n");
            printf("-> 메인으로 돌아가려면 'm'를 입력하세요\n");
            while (repeat == -1)
            {
                printf("\n");
                printf(">> ");
                scanf("%s", birthday);
                if (strcmp(birthday, "m") == 0)
                {
                    repeat = 0;
                    continue;
                }
                printf("\n");
                repeat = DataHandler_FindClient(display->DB, birthday);
                printf("\n");
                printf("---------------------------------\n");
                int cost = 0;
                printf("비용을 입력해주세요 >> ");
                scanf("%d", &cost);
                DataHandler_ModifyClientMileage(display->DB, repeat, cost, 0);
            }
            break;
        case '2':
            printf("---------------------------------\n");
            printf("찾으려는 고객의 생년월일을 입력해주세요!!\n");
            printf("-> 메인으로 돌아가려면 'm'를 입력하세요\n");
            while (repeat == -1) {
                printf("\n");
                printf(">> ");
                scanf("%s", birthday);
                if (strcmp(birthday, "m") == 0)
                {
                    repeat = 0;
                    continue;
                }
                printf("\n");
                repeat = DataHandler_FindClient(display->DB, birthday);
                printf("\n");
                printf("---------------------------------\n");
                int cost = 0;
                printf("비용을 입력해주세요 >> ");
                scanf("%d", &cost);
                DataHandler_ModifyClientMileage(display->DB, repeat, cost, 1);
            }
            break;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
            Sleep(1000);
        }
    }
    Display_ShowMenu(display);
}

void Display_ShowHistoryMenu(Display* display) {
    int repeat = -1;
    char birthday[64];

    Display_CleanDisplay();
    printf("----------히스토리 관리-----------\n");
    printf("찾으려는 고객의 생년월일을 입력해주세요!!\n");
    printf("-> 메인으로 돌아가려면 'm'를 입력하세요\n");
    while (repeat == -1) {
        printf("\n");
        printf(">> ");
        scanf("%s", birthday);
        if (strcmp(birthday, "m") == 0)
        {
            repeat = 0;
            continue;
        }
        printf("\n");
        repeat = DataHandler_FindClient(display->DB, birthday);
        printf("\n");
        printf("---------------------------------\n");
        char history[256];
        printf("히스토리를 입력해주세요 >> ");
        scanf("%s", history);
        DataHandler_ModifyClientHistory(display->DB, repeat, history);
    }
    Display_ShowMenu(display);
}

void Display_DailyMenu(Display* display)
{
    // 추가할 부분
}

void Display_Register(Display* display)
{
    Display_SetCursorPosition(0, 5);
    printf("---------오늘의 일정----------\n");
    printf("┌");
    for (int i = 0; i < display->box_x; i++)
        printf("─");
    printf("┐");

    for (int i = 7; i < display->box_y + 10; i++) {
        Display_SetCursorPosition(0, i);
        printf("│");
        Display_SetCursorPosition(display->box_x + 1, i);
        printf("│");
    }

    Display_SetCursorPosition(0, display->box_y + 10);
    printf("└");
    for (int i = 0; i < display->box_x; i++)
        printf("─");
    printf("┘");
}