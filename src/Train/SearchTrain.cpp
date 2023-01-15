#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "Train.h"
#include "../Check.h"
#define MAX_ARRAY_SIZE 50


using namespace std;

Status searchTrainByName(TRAINLIST train_list, char name[MAX_ARRAY_SIZE], int* index){
	//���ݳ��β�ѯ����������index��ֵ
	int flag = 0;  //����Ƿ��ҵ�
	int j = 0;
	for(j = 0; j < MAX_ARRAY_SIZE; j++)
	{
		if(index[j] == -1) break;
	}
	for(int i = 0; i < train_list.train_num; i++){
		if(!strcmp(train_list.train_value.name[i], name))
		{
			index[j] = i;
			flag = 1;  //����ҵ��ͱ��
		}
	}
	if(flag) return OK;
	else return ERROR;
}

Status searchTrainByOrigin(TRAINLIST train_list, char origin[MAX_ARRAY_SIZE], int* index){
	//����ʼ��վ��ѯ����������index��ֵ
	int flag = 0;  //����Ƿ��ҵ�
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
	//�����յ�վ��ѯ����������index��ֵ
	int flag = 0;  //����Ƿ��ҵ�
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
	//��������״̬��ѯ����������index��ֵ
	int flag = 0;  //����Ƿ��ҵ�
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
	//���ݷ���ʱ���ѯ����������index��ֵ
	int flag = 0;  //����Ƿ��ҵ�
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
	//���ݵ���ʱ���ѯ����������index��ֵ
	int flag = 0;  //����Ƿ��ҵ�
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
	//���ݵ���ʱ���ѯ����������index��ֵ
	int flag = 0;  //����Ƿ��ҵ�
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
	����Ҫ����Ҹ�����Ϣ�����޸�����
	type=0��ģ������
	1�������β���
	2����ʼ���ز���
	3�����յ��ز���
	4��������״̬����
	5��������ʱ�����
	6��������ʱ�����
	7����ͣ��վ���Ʋ�ѯ
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
	cout << "��ѡ����ҷ�ʽ��" << endl;
	cout << "0:ģ������" << endl
	<< "1:�����β���" << endl
	<< "2:��ʼ���ز���" << endl
	<< "3:���յ��ز���" << endl
	<< "4:������״̬����" << endl
	<< "5:������ʱ�����" << endl
	<< "6:������ʱ�����" << endl
	<< "7:��ͣ��վ���Ʋ���" << endl;

	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		
		if(!checkNumber(str))
		{
			cout << "�������ֲ��Ϸ�������������" << endl;
			continue;
		}
		type = atoi(str);
		if(type < 0 || type > 7)
		{
			cout << "�������Ų���ȷ������������" << endl;
			continue;
		}
		break;
	}
	cout << "������ؼ��֣�" << endl;
	cin.getline(str, MAX_ARRAY_SIZE);
	if(!searchTrainInfo(train_list, type, str, index) || index[0] == -1)
	{
		cout << "δ��ѯ���ùؼ���" << endl;
		return ERROR;
	}
	displayTrainByIndex(train_list, index);
	return OK;
}

Status searchTrainExist(TRAINLIST train_list, int type, char value[MAX_ARRAY_SIZE]){
	/*
	����Ҫ����Ҹ�����Ϣ���������Ƿ��ҵ�
	type=0��ģ������
	1�������β���
	2����ʼ���ز���
	3�����յ��ز���
	4��������״̬����
	5��������ʱ�����
	6��������ʱ�����
	7����ͣ��վ���Ʋ�ѯ
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
		cout << "�����ָ����ڣ�" << endl;
		return ERROR;
		break;
	}

	if(index[0] == -1)	return ERROR;
	return OK;
}

int getTrainIndex(TRAINLIST train_list, char *train_name){
	//���ݳ��λ�ȡ�����±�
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
	//���ݳ��κ�ͣ��վ���ƻ�ȡͣ��վ�±�
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
	//ͨ�������յ�վ�������Ƿ��ж�Ӧ�ĸ������Σ�������ӵ�index�����У������flag
	int flag = 0;  //����Ƿ��ҵ�
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
	//ͨ�����β�ѯ���վ�ķ���ʱ�䲢�����ַ���
	char* time = (char*)malloc(6 * sizeof(char)); //�ڶ�������ռ�
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
	//ͨ�����β�ѯ�յ�վ�ĵ�վʱ�䲢�����ַ���
	char* time = (char*)malloc(6 * sizeof(char)); //�ڶ�������ռ�
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
	//ͨ�����β�ѯͣ��վ����̲�����
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