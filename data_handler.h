#pragma once

#include "client.h"

typedef struct ClientNode {
    Client client;
    struct ClientNode* next;
} ClientNode;

typedef struct {
    ClientNode* head;
    int size;
} DataHandler;

DataHandler* DataHandler_Create();
void DataHandler_Destroy(DataHandler* handler);
void DataHandler_ReadCSV(DataHandler* handler, const char* filename);
void DataHandler_WriteCSV(DataHandler* handler, const char* filename);
void DataHandler_AddClient(DataHandler* handler);
void DataHandler_ModifyClientMileage(DataHandler* handler, int id, int cost, int type);
void DataHandler_ModifyClientHistory(DataHandler* handler, int id, const char* data);
int DataHandler_FindClient(DataHandler* handler, const char* birthday);
const char* DataHandler_GetData(DataHandler* handler, int index);
ClientNode* reverseList(ClientNode* head);