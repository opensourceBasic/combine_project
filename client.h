#pragma once

typedef enum
{
	ID,
	NAME,
	GENDER,
	BIRTHDAY,
	PHONE_NUMBER,
	VISIT,
	MILEAGE,
	SERVICE_HISTORY
} data_type;

typedef struct client
{
	int id;
	char name[100];
	char gender[10];
	char birthday[15];
	char phone_number[20];
	int visit;
	int mileage;
	char service_history[200];
} Client;

void Client_Init(Client* client);
void Client_InitWithParams(Client* client, int id, const char* name, const char* gender, const char* birthday, const char* phone_number, int visit, int mileage, const char* service_history);
void Client_SaveMileage(Client* client, int cost);
void Client_PutIntData(Client* client, data_type type, int data);
void Client_PutStringData(Client* client, data_type type, const char* data);
void Client_PrintInfo(const Client* client);
int Client_PayMileage(Client* client, int cost);
int Client_GetIntData(const Client* client, data_type type);
const char* Client_GetStringData(const Client* client, data_type type);
char* Client_ToCSV(const Client* client);