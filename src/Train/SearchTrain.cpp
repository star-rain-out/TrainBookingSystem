#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "Train.h"
#include "../Check.h"
#define MAX_ARRAY_SIZE 50


using namespace std;

Status searchTrainByName(TRAINLIST train_list, char name[MAX_ARRAY_SIZE], int* index){
	//根据车次查询高铁，并对index赋值
	int flag = 0;  //标记是否找到
	int j = 0;
	for(j = 0; j < MAX_ARRAY_SIZE; j++)
	{
		if(index[j] == -1) break;
	}
	for(int i = 0; i < train_list.train_num; i++){
		if(!strcmp(train_list.train_value.name[i], name))
		{
			index[j] = i;
			flag = 1;  //如果找到就标记
		}
	}
	if(flag) return OK;
	else return ERROR;
}

Status searchTrainByOrigin(TRAINLIST train_list, char origin[MAX_ARRAY_SIZE], int* index){
	//根据始发站查询高铁，并对index赋值
	int flag = 0;  //标记是否找到
	int j = 0;
	for(j = 0; j < MAX_ARRAY_SIZE; j++)
	{
		if(index[j] == -1) break;
	}

	for(int i = 0; i < train_list.train_num; i++){
		if(!strcmp(train_list.train_value.origin[i], origin))
		{
			index[j] = i;
			j++;
			flag = 1;
		}
	}
	if(flag) return OK;
	else return ERROR;
}

Status searchTrainByDestination(TRAINLIST train_list, char destination[MAX_ARRAY_SIZE], int* index){
	//根据终点站查询高铁，并对index赋值
	int flag = 0;  //标记是否找到
	int j = 0;
	for(j = 0; j < MAX_ARRAY_SIZE; j++)
	{
		if(index[j] == -1) break;
	}
	for(int i = 0; i < train_list.train_num; i++){
		if(!strcmp(train_list.train_value.destination[i], destination))
		{
			index[j] = i;
			j++;
			flag = 1;
		}
	}
	if(flag) return OK;
	else return ERROR;
}

Status searchTrainByStatus(TRAINLIST train_list, char status[MAX_ARRAY_SIZE], int* index){
	//根据运行状态查询高铁，并对index赋值
	int flag = 0;  //标记是否找到
	int j = 0;
	for(j = 0; j < MAX_ARRAY_SIZE; j++)
	{
		if(index[j] == -1) break;
	}
	for(int i = 0; i < train_list.train_num; i++){
		if(!strcmp(train_list.train_value.status[i], status))
		{
			index[j] = i;
			j++;
			flag = 1;
		}
	}
	if(flag) return OK;
	else return ERROR;
}

Status searchTrainByDepTime(TRAINLIST train_list, char departure_time[MAX_ARRAY_SIZE], int* index){
	//根据发车时间查询高铁，并对index赋值
	int flag = 0;  //标记是否找到
	int j = 0;
	for(j = 0; j < MAX_ARRAY_SIZE; j++)
	{
		if(index[j] == -1) break;
	}
	for(int i = 0; i < train_list.train_num; i++){
		if(!strcmp(train_list.train_value.departure_time[i], departure_time))
		{
			index[j] = i;
			j++;
			flag = 1;
		}
	}
	if(flag) return OK;
	else return ERROR;
}

Status searchTrainByArrTime(TRAINLIST train_list, char arrival_time[MAX_ARRAY_SIZE], int* index){
	//根据到达时间查询高铁，并对index赋值
	int flag = 0;  //标记是否找到
	int j = 0;
	for(j = 0; j < MAX_ARRAY_SIZE; j++)
	{
		if(index[j] == -1) break;
	}
	for(int i = 0; i < train_list.train_num; i++){
		if(!strcmp(train_list.train_value.arrival_time[i], arrival_time))
		{
			index[j] = i;
			j++;
			flag = 1;
		}
	}
	if(flag) return OK;
	else return ERROR;
}

Status searchTrainByStopName(TRAINLIST train_list, char stop_name[MAX_ARRAY_SIZE], int* index){
	//根据到达时间查询高铁，并对index赋值
	int flag = 0;  //标记是否找到
	int j = 0;
	for(j = 0; j < MAX_ARRAY_SIZE; j++)
	{
		if(index[j] == -1) break;
	}
	for(int i = 0; i < train_list.train_num; i++){
		for(int k = 0; k < train_list.elem[i].stop_num; k++){
			if(!strcmp(train_list.train_value.stop_names[i].stop_names[k], stop_name))
			{
				index[j] = i;
				j++;
				flag = 1;
			}
		}
	}
	if(flag) return OK;
	else return ERROR;
}

Status searchTrainInfo(TRAINLIST train_list, int type, char value[MAX_ARRAY_SIZE], int index[MAX_ARRAY_SIZE]){
	/*
	根据要求查找高铁信息，并修改索引
	type=0：模糊查找
	1：按车次查找
	2：按始发地查找
	3：按终到地查找
	4：按运行状态查找
	5：按发车时间查找
	6：按到达时间查找
	7：按停靠站名称查询
	*/
	//int index[MAX_ARRAY_SIZE];
	//index = (int*)malloc(MAX_ARRAY_SIZE * sizeof(int));
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		index[i] = -1;
	}
	switch (type)
	{
	case 0:
		searchTrainByName(train_list, value, index);
		searchTrainByOrigin(train_list, value, index);
		searchTrainByDestination(train_list, value, index);
		searchTrainByStatus(train_list, value, index);
		searchTrainByDepTime(train_list, value, index);
		searchTrainByArrTime(train_list, value, index);
		searchTrainByStopName(train_list, value, index);
		break;
	case 1:
		searchTrainByName(train_list, value, index);
		break;
	case 2:
		searchTrainByOrigin(train_list, value, index);
		break;
	case 3:
		searchTrainByDestination(train_list, value, index);
		break;
	case 4:
		searchTrainByStatus(train_list, value, index);
		break;
	case 5:
		searchTrainByDepTime(train_list, value, index);
		break;
	case 6:
		searchTrainByArrTime(train_list, value, index);
		break;
	case 7:
		searchTrainByStopName(train_list, value, index);
		break;
	default:
		return ERROR;
		break;
	}
	if(index[0] == -1)	return ERROR;
	return OK;
}

Status searchTrain(TRAINLIST train_list){
	char str[MAX_ARRAY_SIZE];
	int index[MAX_ARRAY_SIZE];
	int type = 0;
	cout << "请选择查找方式：" << endl;
	cout << "0:模糊查找" << endl
	<< "1:按车次查找" << endl
	<< "2:按始发地查找" << endl
	<< "3:按终到地查找" << endl
	<< "4:按运行状态查找" << endl
	<< "5:按发车时间查找" << endl
	<< "6:按到达时间查找" << endl
	<< "7:按停靠站名称查找" << endl;

	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		
		if(!checkNumber(str))
		{
			cout << "输入数字不合法，请重新输入" << endl;
			continue;
		}
		type = atoi(str);
		if(type < 0 || type > 7)
		{
			cout << "输入的序号不正确，请重新输入" << endl;
			continue;
		}
		break;
	}
	cout << "请输入关键字：" << endl;
	cin.getline(str, MAX_ARRAY_SIZE);
	if(!searchTrainInfo(train_list, type, str, index) || index[0] == -1)
	{
		cout << "未查询到该关键字" << endl;
		return ERROR;
	}
	displayTrainByIndex(train_list, index);
	return OK;
}

Status searchTrainExist(TRAINLIST train_list, int type, char value[MAX_ARRAY_SIZE]){
	/*
	根据要求查找高铁信息，并返回是否找到
	type=0：模糊查找
	1：按车次查找
	2：按始发地查找
	3：按终到地查找
	4：按运行状态查找
	5：按发车时间查找
	6：按到达时间查找
	7：按停靠站名称查询
	*/
	int index[MAX_ARRAY_SIZE];
	//index = (int*)malloc(MAX_ARRAY_SIZE * sizeof(int));
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		index[i] = -1;
	}
	//memset(index,-1,sizeof(index));
	switch (type)
	{
	case 0:
		searchTrainByName(train_list, value, index);
		searchTrainByOrigin(train_list, value, index);
		searchTrainByDestination(train_list, value, index);
		searchTrainByStatus(train_list, value, index);
		searchTrainByDepTime(train_list, value, index);
		searchTrainByArrTime(train_list, value, index);
		searchTrainByStopName(train_list, value, index);
		break;
	case 1:
		searchTrainByName(train_list, value, index);
		break;
	case 2:
		searchTrainByOrigin(train_list, value, index);
		break;
	case 3:
		searchTrainByDestination(train_list, value, index);
		break;
	case 4:
		searchTrainByStatus(train_list, value, index);
		break;
	case 5:
		searchTrainByDepTime(train_list, value, index);
		break;
	case 6:
		searchTrainByArrTime(train_list, value, index);
		break;
	case 7:
		searchTrainByStopName(train_list, value, index);
		break;
	default:
		cout << "输入的指令不存在！" << endl;
		return ERROR;
		break;
	}

	if(index[0] == -1)	return ERROR;
	return OK;
}

int getTrainIndex(TRAINLIST train_list, char *train_name){
	//根据车次获取车次下标
	int i = 0;
	for(i = 0; i < train_list.train_num; i++){
		if(!strcmp(train_list.train_value.name[i], train_name))
		{
			break;
		}
	}
	return i;
}

int getStopIndex(TRAINLIST train_list, char *train_name, char *stop_name){
	//根据车次和停靠站名称获取停靠站下标
	int i = 0;
	int j = 0;
	for(i = 0; i < train_list.train_num; i++){
		if(!strcmp(train_list.train_value.name[i], train_name))
		{
			break;
		}
	}
	for(j = 0; j < (train_list.elem + i)->stop_num; j++){
		if(!strcmp((train_list.train_value.stop_names + i)->stop_names[j], stop_name))
		{
			break;
		}
	}
	return j;
}

Status searchTrainByOtoD(TRAINLIST train_list, char *origin, char* destination, int*& index){
	//通过起点和终点站来搜索是否有对应的高铁车次，有则添加到index数组中，并标记flag
	int flag = 0;  //标记是否找到
	int j = 0;
	index = (int*)malloc(MAX_ARRAY_SIZE * sizeof(int));
	for(int i = 0; i < MAX_ARRAY_SIZE; i++){
		index[i] = -1;
	}
	for(int i = 0; i < train_list.train_num; i++){
		for(int k = 0; k < train_list.elem[i].stop_num; k++){
			if(!strcmp(train_list.train_value.stop_names[i].stop_names[k], origin))
			{
				for(int m = k; m < train_list.elem[i].stop_num; m++){
					if(!strcmp(train_list.train_value.stop_names[i].stop_names[m], destination))
					{
						index[j] = i;
						j++;
						flag = 1;
					}
				}
			}
		}
	}
	if(flag) return OK;
	else return ERROR;
}

char* getOriginDepTime(TRAINLIST train_list, char* train_name, char* origin){
	//通过车次查询起点站的发车时间并返回字符串
	char* time = (char*)malloc(6 * sizeof(char)); //在堆上申请空间
	for(int i = 0; i < train_list.train_num; i++){
		if(!strcmp(train_list.train_value.name[i], train_name))
		{
			for(int k = 0; k < train_list.elem[i].stop_num; k++){
				if(!strcmp(train_list.train_value.stop_names[i].stop_names[k], origin))
				{
					strcpy(time, train_list.elem[i].stop_departure_time[k]);
				}
			}
		}
	}
	return time;
}

char* getDestinationArrTime(TRAINLIST train_list, char* train_name, char* destination){
	//通过车次查询终点站的到站时间并返回字符串
	char* time = (char*)malloc(6 * sizeof(char)); //在堆上申请空间
	for(int i = 0; i < train_list.train_num; i++){
		if(!strcmp(train_list.train_value.name[i], train_name))
		{
			for(int k = 0; k < train_list.elem[i].stop_num; k++){
				if(!strcmp(train_list.train_value.stop_names[i].stop_names[k], destination))
				{
					strcpy(time, train_list.elem[i].stop_arrival_time[k]);
				}
			}
		}
	}
	return time;
}

float getStopDistance(TRAINLIST train_list, char* train_name, char* stop_name){
	//通过车次查询停靠站的里程并返回
	float distance = 0;;
	for(int i = 0; i < train_list.train_num; i++){
		if(!strcmp(train_list.train_value.name[i], train_name))
		{
			for(int k = 0; k < train_list.elem[i].stop_num; k++){
				if(!strcmp(train_list.train_value.stop_names[i].stop_names[k], stop_name))
				{
					distance = train_list.elem[i].stop_distance[k];
				}
			}
		}
	}
	return distance;
}