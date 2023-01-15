#pragma once
#include "Train.h"
#define MAX_ARRAY_SIZE 50



Status searchTrainByName(TRAINLIST train_list, char name[MAX_ARRAY_SIZE], int* index);
Status searchTrainByOrigin(TRAINLIST train_list, char origin[MAX_ARRAY_SIZE], int* index);
Status searchTrainByDestination(TRAINLIST train_list, char destination[MAX_ARRAY_SIZE], int* index);
Status searchTrainByStatus(TRAINLIST train_list, char status[MAX_ARRAY_SIZE], int* index);
Status searchTrainByDepTime(TRAINLIST train_list, char departure_time[MAX_ARRAY_SIZE], int* index);
Status searchTrainByArrTime(TRAINLIST train_list, char arrival_time[MAX_ARRAY_SIZE], int* index);
Status searchTrainByStopName(TRAINLIST train_list, char stop_name[MAX_ARRAY_SIZE], int* index);
Status searchTrainInfo(TRAINLIST train_list, int type, char value[MAX_ARRAY_SIZE], int index[MAX_ARRAY_SIZE]);
Status searchTrainExist(TRAINLIST train_list, int type, char value[MAX_ARRAY_SIZE]);
Status searchTrain(TRAINLIST train_list);

int getTrainIndex(TRAINLIST train_list, char *train_name);
int getStopIndex(TRAINLIST train_list, char *train_name, char *stop_name);
Status searchTrainByOtoD(TRAINLIST train_list, char *origin, char* destination, int*& index);
char* getOriginDepTime(TRAINLIST train_list, char* train_name, char* origin);
char* getDestinationArrTime(TRAINLIST train_list, char* train_name, char* destination);
float getStopDistance(TRAINLIST train_list, char* train_name, char* stop_name);