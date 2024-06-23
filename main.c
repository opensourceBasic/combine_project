#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "data_handler.h"
#include "system_menu.h"

// 해당 월의 일수를 계산하는 함수
int getNumberOfDays(int month, int year) {
    if (month == 2) {
        if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
            return 29;
        else
            return 28;
    }
    else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        return 31;
    else
        return 30;
}

// 달력을 그리는 함수
void printCalendar(const char* weekDays[], int firstWeekDayOfMonth, int numberOfDays) {
    int w, d;
    for (w = 0; w < 7; w++) {
        printf("%s    ", weekDays[w]);
    }
    printf("\n-------------------------------------------------\n\n");

    int tempBreak = 1;
    for (w = 0; w < firstWeekDayOfMonth; w++) {
        printf("       ");
        tempBreak++;
    }
    for (d = 1; d <= numberOfDays; d++) {
        printf("%2d     ", d);
        if (tempBreak >= 7) {
            printf("\n");
            tempBreak = 0;
        }
        tempBreak++;
    }
    printf("\n");
}

// 리마인더를 작성하는 함수
void writeReminder(int numberOfDays, int currentMonth, int currentYear) {
    int day;
    char reminder[100];

    while (1) {
        printf("날짜를 선택하세요: ");
        if (scanf("%d", &day) != 1) {
            printf("Invalid input. Please enter a valid day.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        if (day > 0 && day <= numberOfDays)
            break;
        else
            printf("1 and %d 사이의 날짜를 선택하세요.\n", numberOfDays);
    }

    printf("리마인더를 작성하세요: ");
    if (scanf("%s", reminder) != 1) {
        printf("잘못된 입력입니다.\n");
        return;
    }

    FILE* fp;
    fp = fopen("reminders.txt", "w");
    if (fp == NULL) {
        printf("파일 열기 실패\n");
        return;
    }
    fprintf(fp, "%d-%02d-%02d:%s\n", currentYear, currentMonth, day, reminder);

    fclose(fp);
}

void showCalendarMenu() {
    const char* months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    const char* weekDays[7] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

    time_t currentTime = time(0);   // 현재 시간 가져오기
    struct tm now;
    _localtime64_s(&now, &currentTime);

    int currentDay = now.tm_mday;
    int currentMonth = now.tm_mon + 1; // tm_mon은 0부터 시작하므로 1을 더해줌
    int currentYear = now.tm_year + 1900; // tm_year는 1900년부터의 년도 차이
    int numberOfDays = getNumberOfDays(currentMonth, currentYear);

    // 해당 월의 첫 번째 날짜의 요일 계산
    struct tm tFirst = { 0, 0, 0, 1, now.tm_mon, now.tm_year };
    time_t time_temp = mktime(&tFirst);
    struct tm firstTime;
    _localtime64_s(&firstTime, &time_temp);

    int firstWeekDayOfMonth = firstTime.tm_wday;

    printf("Current Date: %d-%s-%02d\n\n", currentYear, months[currentMonth - 1], currentDay);
    printf("%s\n\n", months[currentMonth - 1]);

    printCalendar(weekDays, firstWeekDayOfMonth, numberOfDays);

    int num;

    printf("1: 리마인더 작성\n2: 리마인더 보기\n3: 리마인더 삭제\n4: 종료\n선택하세요: ");
    scanf("%d", &num);

    switch (num) {
    case 1:
        writeReminder(numberOfDays, currentMonth, currentYear);
        break;
    case 4:
        system("python googleCalendar.py");
        return;
    default:
        printf("잘못된 선택입니다.\n");
        break;
    }
}

int main() {
    const char* filename = "clients.csv";
    const char* filename_t = "test.csv";

    // DataHandler 초기화
    DataHandler* handler = DataHandler_Create();
    DataHandler_ReadCSV(handler, filename);

    // Display 초기화
    Display display;
    Display_Init(&display, handler);

    while (1) {
        printf("메인 메뉴:\n");
        printf("1. 고객 관리\n");
        printf("2. 일정 관리\n");
        printf("0. 프로그램 종료\n");
        printf("선택하세요: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
        case 0:
            DataHandler_WriteCSV(handler, filename_t);
            DataHandler_Destroy(handler);
            return 0;
        case 1:
            Display_ShowMenu(&display);
            break;
        case 2:
            showCalendarMenu();
            break;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
            break;
        }
    }
}
