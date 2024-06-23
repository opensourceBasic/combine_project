#include "data_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WORNINGS

// DataHandler 생성
DataHandler* DataHandler_Create()
{
    DataHandler* handler = (DataHandler*)malloc(sizeof(DataHandler));
    handler->head = NULL;
    return handler;
}

// DataHandler 소멸
void DataHandler_Destroy(DataHandler* handler)
{
    ClientNode* current = handler->head;
    ClientNode* next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    free(handler);
}

// CSV 파일 읽기
void DataHandler_ReadCSV(DataHandler* handler, const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (!file)
    {
        perror("Unable to open file");
        return;
    }

    char line[1024];
    int k = 0;

    while (fgets(line, sizeof(line), file)) {
        if (k != 0) {
            ClientNode* newNode = (ClientNode*)malloc(sizeof(ClientNode));
            Client_Init(&newNode->client);

            char* token = strtok(line, ",");
            int col = 0;
            while (token != NULL) {
                if (col == ID) Client_PutIntData(&newNode->client, ID, atoi(token));
                else if (col == NAME) Client_PutStringData(&newNode->client, NAME, token);
                else if (col == GENDER) Client_PutStringData(&newNode->client, GENDER, token);
                else if (col == BIRTHDAY) Client_PutStringData(&newNode->client, BIRTHDAY, token);
                else if (col == PHONE_NUMBER) Client_PutStringData(&newNode->client, PHONE_NUMBER, token);
                else if (col == VISIT) Client_PutIntData(&newNode->client, VISIT, atoi(token));
                else if (col == MILEAGE) Client_PutIntData(&newNode->client, MILEAGE, atoi(token));
                else if (col == SERVICE_HISTORY) Client_PutStringData(&newNode->client, SERVICE_HISTORY, token);

                token = strtok(NULL, ",");
                col++;
            }

            newNode->next = handler->head;
            handler->head = newNode;
        }
        k++;
    }

    fclose(file);
}

// CSV 파일 쓰기
void DataHandler_WriteCSV(DataHandler* handler, const char* filename)
{
    FILE* file = fopen(filename, "w");
    if (!file)
    {
        perror("Unable to open file");
        return;
    }

    fprintf(file, "번호,이름,성별,생일,전화번호,방문횟수,마일리지,서비스 기록\n");

    Client* reversedHead = reverseList(handler->head);
    ClientNode* current = reversedHead;

    while (current != NULL)
    {
        char* csvString = Client_ToCSV(&current->client);
        fprintf(file, "%s\n", csvString);
        free(csvString);
        current = current->next;
    }

    fclose(file);
}

// 클라이언트 추가
void DataHandler_AddClient(DataHandler* handler)
{
    ClientNode* newNode = (ClientNode*)malloc(sizeof(ClientNode));
    Client_Init(&newNode->client);

    char input[256];
    printf("ex) 이름, 성별, 생일, 전화번호, 방문횟수, 마일리지, 서비스 기록\n");
    printf("ex) 홍길동,남,010101,000-0000-0000,1,1000,음료\n>> ");
    fgets(input, sizeof(input), stdin);

    char* token = strtok(input, ",");
    int col = 1;

    while (token != NULL)
    {
        if (col == NAME) Client_PutStringData(&newNode->client, NAME, token);
        else if (col == GENDER) Client_PutStringData(&newNode->client, GENDER, token);
        else if (col == BIRTHDAY) Client_PutStringData(&newNode->client, BIRTHDAY, token);
        else if (col == PHONE_NUMBER) Client_PutStringData(&newNode->client, PHONE_NUMBER, token);
        else if (col == VISIT) Client_PutIntData(&newNode->client, VISIT, atoi(token));
        else if (col == MILEAGE) Client_PutIntData(&newNode->client, MILEAGE, atoi(token));
        else if (col == SERVICE_HISTORY) Client_PutStringData(&newNode->client, SERVICE_HISTORY, token);

        token = strtok(NULL, ",");
        col++;
    }

    // Assign a unique ID
    int id = 1;
    ClientNode* current = handler->head;
    while (current != NULL)
    {
        if (Client_GetIntData(&current->client, ID) >= id)
            id = Client_GetIntData(&current->client, ID) + 1;
        current = current->next;
    }
    Client_PutIntData(&newNode->client, ID, id);

    newNode->next = handler->head;
    handler->head = newNode;
}

// 클라이언트 마일리지 수정
void DataHandler_ModifyClientMileage(DataHandler* handler, int id, int cost, int type)
{
    ClientNode* current = handler->head;
    while (current)
    {
        if (current->client.id == id)
        {
            if (type == 0)  // 저장
                Client_SaveMileage(&current->client, cost);
            else if (type == 1) // 사용
                Client_PayMileage(&current->client, cost);
            return;
        }
        current = current->next;
    }
    printf("Client with ID %d not found\n", id);
}

// 클라이언트 서비스 기록 수정
void DataHandler_ModifyClientHistory(DataHandler* handler, int id, const char* data)
{
    ClientNode* current = handler->head;
    while (current)
    {
        if (current->client.id == id)
        {
            strncpy(current->client.service_history, data, sizeof(current->client.service_history) - 1);
            return;
        }
        current = current->next;
    }
    printf("Client with ID %d not found\n", id);
}

// 생일로 클라이언트 찾기
int DataHandler_FindClient(DataHandler* handler, const char* birthday)
{
    ClientNode* current = handler->head;
    while (current != NULL)
    {
        if (strcmp(current->client.birthday, birthday) == 0)
        {
            Client_PrintInfo(&current->client);
            return Client_GetIntData(&current->client, ID);
        }
        current = current->next;
    }
    printf("Client with birthday %s not found\n", birthday);
    return -1;
}

// 인덱스로 데이터 가져오기
const char* DataHandler_GetData(DataHandler* handler, int index)
{
    ClientNode* current = handler->head;
    int i = 0;
    while (current != NULL)
    {
        if (i == index)
            return Client_GetStringData(&current->client, NAME);
        current = current->next;
        i++;
    }
    return NULL;
}

// 연결 리스트를 뒤집는 함수
ClientNode* reverseList(ClientNode* head)
{
    ClientNode* prev = NULL;
    ClientNode* current = head;
    ClientNode* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}