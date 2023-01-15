#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#include "Train.h"
#include "SearchTrain.h"
#include "../Check.h"
#define MAX_ARRAY_SIZE 50

using namespace std;

Status getTrainName(TRAINLIST train_list, PTRAIN train){
	//��ȡ�û�����ĳ������Ʋ�����ָ��ָ���������
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	char str1[MAX_ARRAY_SIZE];
	int num;   //���ڼ�鳵�������Ƿ�Ϸ�
	int flag = 0;
	int index[MAX_ARRAY_SIZE];
	cout << "�����������ĸ������Σ�ȡ�������롰ȡ�������س�����" << endl;
	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		strcpy(str1, str);
		if(str1[0] != 'G')
		{
			cout << "���α�����G��ͷ! ����������" << endl;
			continue;
		}
		for(int i = 0; str1[i]!= '\0'; i++){
			str1[i] = str1[i + 1];
		}
		num = atoi(str1);
		if(num <= 0 || num > 1000 || !checkNumber(str1))
		{
			cout << "�������ֲ��Ϸ�,Ӧȡ1~1000֮��,����������" << endl;
			continue;
		}
		for(int i = 0; i < train_list.train_num; i++){
			if(!strcmp(train_list.train_value.name[i], str))
			{
				cout << "�ó����Ѵ��ڣ�����������" << endl;
				flag = 1;
				break;
			}
		}
		if(flag)
		{
			flag = 0;
			continue;
		} 
		strcpy(train->name, str);
		return OK;
	}
}

Status getTrainOrigin(PTRAIN train){
	//��ȡ�û������ʼ��վ���Ʋ�����ָ��ָ���������
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	cout << "������ʼ��վ��" << endl;
	cin.getline(str, MAX_ARRAY_SIZE);
	if(checkCancel(str)) return ERROR;
	strcpy(train->origin, str);
	return OK;
}

Status getTrainDestination(PTRAIN train){
	//��ȡ�û�������յ�վ���Ʋ�����ָ��ָ���������
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	cout << "�������յ�վ��" << endl;
	cin.getline(str, MAX_ARRAY_SIZE);
	if(checkCancel(str)) return ERROR;
	strcpy(train->destination, str);
	return OK;
}

Status getTrainDistance(PTRAIN train){
	//��ȡ�û���������о��벢����ָ��ָ���������
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	int num;
	cout << "���������о��룺" << endl;
	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		num = atoi(str);
		if(num < 0 || num > 10000)
		{
			cout << "���о���Ӧ��1-10000֮��,����������" << endl;
			continue;
		}
		train->distance = num;
		return OK;
	}
}

Status getTrainStatus(PTRAIN train){
	//��ȡ�û����������״̬������ָ��ָ���������
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	char normal[] = "����";
	char stop[] = "ͣ��";
	
	cout << "����������״̬��������ͣ�ˣ���" << endl;
	while (1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		if(strcmp(str, normal) && strcmp(str, stop))
		{
			cout << "����״̬ӦΪ��������ͣ�ˣ�����������" << endl;
			continue;
		}
		strcpy(train->status, str);
		break;
	}
	return OK;
}

Status getTrainDepTime(PTRAIN train){
	//��ȡ�û�����ķ���ʱ�䲢����ָ��ָ���������
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	char zero[] = "0:0";
	cout << "�����뷢��ʱ�䣺" << endl;
	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		if(!checkTime(str) || !checkTimeByOrder(zero, str))
		{
			cout << "�����ʱ���ʽ����ע��:ΪӢ��ð�ţ�������������" << endl;
			continue;
		}
		strcpy(train->departure_time, str);
		return OK;
	}
}

Status getTrainArrTime(PTRAIN train){
	//��ȡ�û�����ĵ���ʱ�䲢����ָ��ָ���������
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	cout << "�����뵽��ʱ�䣺" << endl;
	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		if(!checkTime(str))
		{
			cout << "�����ʱ���ʽ����ע��:ΪӢ��ð�ţ�������������" << endl;
			continue;
		}
		if(!checkTimeByOrder(train->departure_time, str))
		{
			cout << "����ʱ������ڷ���ʱ��֮������������" << endl;
			continue;
		}
		strcpy(train->arrival_time, str);
		return OK;
	}
}

Status getTrainSpecialClass(PTRAIN train){
	////��ȡ�û����������������������ָ��ָ���������
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	int num;
	cout << "�������ص�������������������" << endl;
	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		num = atoi(str);
		if(num < 0 || num > 100 || !checkNumber(str))
		{
			cout << "�ص�������Ӧ��1-100֮��,����������" << endl;
			continue;
		}
		train->special_class = num;
		return OK;
	}
}

Status getTrainFirstClass(PTRAIN train){
	//��ȡ�û������һ����������ָ��ָ���������
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	int num;
	cout << "������һ����������" << endl;
	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		num = atoi(str);
		if(num < 0 || num > 100 || !checkNumber(str))
		{
			cout << "һ��������Ӧ��1-100֮��,����������" << endl;
			continue;
		}
		train->first_class = num;
		return OK;
	}
}

Status getTrainSecondClass(PTRAIN train){
	//��ȡ�û�����Ķ���������������ָ��ָ���������
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	int num;
	cout << "�����������������" << endl;
	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		num = atoi(str);
		if(num < 0 || num > 100 || !checkNumber(str))
		{
			cout << "����������Ӧ��1-100֮��,����������" << endl;
			continue;
		}
		train->second_class = num;
		return OK;
	}
}

Status getTrainStopNum(PTRAIN train){
	//��ȡ�û������ͣ��վ����������ָ��ָ���������
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	int num;
	cout << "������ͣ��վ������" << endl;
	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		num = atoi(str);
		if(num < 0 || num > 100 || !checkNumber(str))
		{
			cout << "ͣ��վ����Ӧ��1-100֮��,����������" << endl;
			continue;
		}
		train->stop_num = num;
		return OK;
	}
}

Status getTrainStopName(PTRAIN train, int stop_num){
	//��ȡ��stop_num��ͣ��վ����
	char str[MAX_ARRAY_SIZE];
	cout << "������ͣ��վ" << stop_num << "����:" << endl;
	cin.getline(str, MAX_ARRAY_SIZE);
	if(checkCancel(str)) return ERROR;
	if(stop_num > 0)
	{
		strcpy(train->stop_names[stop_num - 1], str);
		return OK;
	}
	else return ERROR;
}

Status getTrainStopArrTime(PTRAIN train, int stop_num){
	//��ȡ��stop_num��ͣ��վ��վʱ��
	char str[MAX_ARRAY_SIZE];
	cout << "������ͣ��վ" << stop_num << "��վʱ��:" << endl;
	while(1)
	{
		
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		if(!checkTime(str))
		{
			cout << "�����ʱ���ʽ��������������" << endl;
			continue;
		}
		if(stop_num == 2)
		{
			//��һ�αȽ�ʱ���뷢��ʱ����бȽ�
			if(!checkTimeByOrder(train->departure_time, str) || !checkTimeByOrder(str, train->arrival_time))
			{
				cout << "��վʱ��Ӧ�ȷ���ʱ�����ȵ����յ�վʱ���磬����������" << endl;
				continue;
			}
			strcpy(train->stop_arrival_time[stop_num - 1], str);
			break;
		}
		if(!checkTimeByOrder(train->stop_departure_time[stop_num - 2], str) || !checkTimeByOrder(str, train->arrival_time))
		{
			cout << "��վʱ��Ӧ��ǰһͣ��վ����ʱ�����ȵ����յ�վʱ���磬����������" << endl;
			continue;
		}
		strcpy(train->stop_arrival_time[stop_num - 1], str);
		break;
	}
	return OK;
}

Status getTrainStopDepTime(PTRAIN train, int stop_num){
	//��ȡ��stop_num��ͣ��վ��վʱ��
	char str[MAX_ARRAY_SIZE];
	cout << "������ͣ��վ" << stop_num << "��վʱ��:" << endl;
	while(1)
	{
		
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		if(!checkTime(str))
		{
			cout << "�����ʱ���ʽ��������������" << endl;
			continue;
		}
		if(!checkTimeByOrder(train->stop_arrival_time[stop_num - 1], str) || !checkTimeByOrder(str, train->arrival_time))
		{
			cout << "����ʱ��Ӧ�ȵ�վʱ�����ȵ����յ�վʱ���磬����������" << endl;
			continue;
		}
		strcpy(train->stop_departure_time[stop_num - 1], str);
		break;
	}
	return OK;
}

Status getTrainStopDistance(PTRAIN train, int stop_num){
	//��ȡ��stop_num��ͣ��վ���
	float distance;
	char str[MAX_ARRAY_SIZE];
	cout << "������ͣ��վ" << stop_num << "���:" << endl;
	while (1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		distance = atof(str);
		if(distance < 0 || distance >= train->distance || !checkFloat(str))
		{
			cout << "���Ӧ�ڡ�0-���о��롿֮�䣬����������" << endl;
			continue;
		}
		if(distance <= train->stop_distance[stop_num - 2])
		{
			cout << "���Ӧ��ǰһվ���֮������������" << endl;
			continue;
		}
		train->stop_distance[stop_num - 1] = distance;
		break;
	}
	return OK;
}

Status getTrainStopInfo(PTRAIN train){
	/*
	��ȡͣ��վ���ƣ���վʱ�䣬����ʱ�����̡�
	��ȡʱ������ݺϷ��ԣ�ͣ��վ��վʱ��Ӧ��ǰһվ��վʱ�俿��
	����һ��ͣ��վ�����һ��ͣ��վ����Ϣ����Ϊʼ��վ���յ�վ����Ϣ
	*/
	if(!train) return ERROR;

	strcpy(train->stop_names[0], train->origin);
	strcpy(train->stop_arrival_time[0], train->departure_time);
	strcpy(train->stop_departure_time[0], train->departure_time);
	train->stop_distance[0] = 0;
	strcpy(train->stop_names[train->stop_num - 1], train->destination);
	strcpy(train->stop_arrival_time[train->stop_num - 1], train->arrival_time);
	strcpy(train->stop_departure_time[train->stop_num - 1], train->arrival_time);
	train->stop_distance[train->stop_num - 1] = train->distance;
	char str[MAX_ARRAY_SIZE];
	char time_before[MAX_ARRAY_SIZE]; //�洢��һ�������ʱ�䣬���ڱȽ�ʱ�����
	float distance;
	float distance_before = 0;
	
	for(int i = 2; i < train->stop_num; i++)
	{
		if(
			!getTrainStopName(train, i) ||
			!getTrainStopArrTime(train, i) ||
			!getTrainStopDepTime(train, i) ||
			!getTrainStopDistance(train ,i)
		) return ERROR;
	}
	return OK;
}

Status getTrainInfo(TRAINLIST train_list, PTRAIN train){
	//��ȡ�û���������庯��
	if(!train){
		cout << 1;
		return ERROR;
	}
	if(
		!getTrainName(train_list, train) ||
		!getTrainOrigin(train) ||
		!getTrainDestination(train) ||
		!getTrainDistance(train) ||
		!getTrainStatus(train) ||
		!getTrainDepTime(train) ||
		!getTrainArrTime(train) ||
		!getTrainSpecialClass(train) ||
		!getTrainFirstClass(train) ||
		!getTrainSecondClass(train) ||
		!getTrainStopNum(train) ||
		!getTrainStopInfo(train)
	)	return ERROR;
	return OK;
}

Status insertTrain(TRAINLIST& train_list){
	//���������Ϣ�����庯�����Ȼ�ȡ��Ϣ��Ȼ����в���
	PTRAIN p = (PTRAIN)realloc(train_list.elem, (train_list.train_num + 1) * sizeof(TRAIN));
	if(!p) return ERROR;
	train_list.elem = p;
	p += train_list.train_num;
	
	if(!getTrainInfo(train_list, p))
	{
		cout << "����ʧ��" << endl;
		return ERROR;
	}
	train_list.train_num++;
	setTrainValue(train_list);
	cout << "����ɹ���" << endl;
	return OK;
}
