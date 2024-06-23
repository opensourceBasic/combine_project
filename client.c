#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WORNINGS

// Client 초기화 함수
void Client_Init(Client* client)
{
    client->id = 0;
    strcpy(client->name, "");
    strcpy(client->gender, "");
    strcpy(client->birthday, "");
    strcpy(client->phone_number, "");
    client->visit = 0;
    client->mileage = 0;
    strcpy(client->service_history, "");
}

// Client 초기화 함수 (매개변수 있는 버전)
void Client_InitWithParams(Client* client, int id, const char* name, const char* gender, const char* birthday, const char* phone_number, int visit, int mileage, const char* service_history)
{
    client->id = id;
    strncpy(client->name, name, sizeof(client->name) - 1);
    strncpy(client->gender, gender, sizeof(client->gender) - 1);
    strncpy(client->birthday, birthday, sizeof(client->birthday) - 1);
    strncpy(client->phone_number, phone_number, sizeof(client->phone_number) - 1);
    client->visit = visit;
    client->mileage = mileage;
    strncpy(client->service_history, service_history, sizeof(client->service_history) - 1);
}

// client의 마일리지 저장
void Client_SaveMileage(Client* client, int cost)
{
    int temp = cost * 0.1;
    client->mileage += temp;
}

// int 데이터 설정
void Client_PutIntData(Client* client, data_type type, int data)
{
    switch (type)
    {
    case ID:
        client->id = data;
        break;
    case VISIT:
        client->visit = data;
        break;
    case MILEAGE:
        client->mileage = data;
        break;
    default:
        printf("Type entered does not exist\n");
        break;
    }
}

// string 데이터 설정
void Client_PutStringData(Client* client, data_type type, const char* data)
{
    switch (type)
    {
    case NAME:
        strncpy(client->name, data, sizeof(client->name) - 1);
        break;
    case GENDER:
        strncpy(client->gender, data, sizeof(client->gender) - 1);
        break;
    case BIRTHDAY:
        strncpy(client->birthday, data, sizeof(client->birthday) - 1);
        break;
    case PHONE_NUMBER:
        strncpy(client->phone_number, data, sizeof(client->phone_number) - 1);
        break;
    case SERVICE_HISTORY:
        strncpy(client->service_history, data, sizeof(client->service_history) - 1);
        break;
    default:
        printf("Type entered does not exist\n");
        break;
    }
}

// client 정보 출력
void Client_PrintInfo(const Client* client)
{
    printf("이름 : %s\n", client->name);
    printf("성별 : %s\n", client->gender);
    printf("생일 : %s\n", client->birthday);
    printf("전화번호 : %s\n", client->phone_number);
    printf("방문횟수 : %d\n", client->visit);
    printf("마일리지 : %d\n", client->mileage);
    printf("이전 서비스 : %s\n", client->service_history);
}

// client의 마일리지 사용
int Client_PayMileage(Client* client, int cost)
{
    if (client->mileage < 100)
    {
        printf("마일리지가 충분하지 않습니다\n");
        return cost;
    }
    else
    {
        int temp = client->mileage - cost;
        if (temp < 0)
        {
            client->mileage = 0;
            return cost - client->mileage;
        }
        else
        {
            client->mileage -= cost;
            return 0;
        }
    }
}

// int 데이터 가져오기
int Client_GetIntData(const Client* client, data_type type)
{
    switch (type)
    {
    case ID:
        return client->id;
    case VISIT:
        return client->visit;
    case MILEAGE:
        return client->mileage;
    default:
        printf("Type entered does not exist\n");
        return -1;
    }
}

// string 데이터 가져오기
const char* Client_GetStringData(const Client* client, data_type type)
{
    switch (type)
    {
    case NAME:
        return client->name;
    case GENDER:
        return client->gender;
    case BIRTHDAY:
        return client->birthday;
    case PHONE_NUMBER:
        return client->phone_number;
    case SERVICE_HISTORY:
        return client->service_history;
    default:
        printf("Type entered does not exist\n");
        return NULL;
    }
}

// 클라이언트를 csv 형식으로 변환
char* Client_ToCSV(Client* client) {
    // CSV 형식의 문자열을 저장할 메모리를 할당합니다.
    // 필요한 길이를 계산하여 메모리를 할당합니다.
    int bufferSize = 50 + 10 + 20 + 20 + 100 + 50; // 대략적인 길이 계산
    char* buffer = (char*)malloc(bufferSize);

    if (buffer == NULL) {
        perror("Unable to allocate memory for CSV string");
        exit(EXIT_FAILURE);
    }

    // snprintf를 사용하여 클라이언트 데이터를 CSV 형식으로 변환합니다.
    snprintf(buffer, bufferSize, "%d,%s,%s,%s,%s,%d,%d,%s",
        client->id,
        client->name,
        client->gender,
        client->birthday,
        client->phone_number,
        client->visit,
        client->mileage,
        client->service_history);

    char* newline = strchr(buffer, '\n');
    if (newline)
        *newline = '\0';

    return buffer;
}