#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "Train.h"
#include "../Check.h"
#define MAX_ARRAY_SIZE 50

#define CANCEL 2

using namespace std;


int num = 0; //ȫ�ֱ�����������Ҫ�޸ĵ�ͣ��վ���

Status getStopNum(PTRAIN train, int& num){
	//��ȡ�û����룬����ͣ��վ������ֵ�����ò���num
    if(!train) return ERROR;
    int num1;
	char str[MAX_ARRAY_SIZE];
	cout << "������Ҫ�޸ĵ�ͣ��վ��ţ���һվ�����һվ�޷��޸ģ���" << endl;
	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		num1 = atoi(str);
		if(num < 2 || num > (train->stop_num - 1) || !checkNumber(str))
		{
			cout << "ͣ��վ���Ӧ��" << train->stop_num -1 << "֮��,����������" << endl;
			continue;
		}
		num = num1;
		return OK;
	}
}

Status changeTrainOrigin(PTRAIN train){
	//��ȡ�û������ʼ��վ���Ʋ��浽ָ��ָ���������
    if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	cout << "��������ʼ��վ��" << endl;
	cin.getline(str, MAX_ARRAY_SIZE);
	if(checkCancel(str)) return ERROR;
	strcpy(train->origin, str);
	return OK;
}

Status changeTrainDestination(PTRAIN train){
	//��ȡ�û�������յ�վ���Ʋ��浽ָ��ָ���������
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	cout << "���������յ�վ��" << endl;
	cin.getline(str, MAX_ARRAY_SIZE);
	if(checkCancel(str)) return ERROR;
	strcpy(train->destination, str);
	return OK;
}

Status changeTrainDistance(PTRAIN train){
	//��ȡ�û���������о��벢�浽ָ��ָ���������
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	int num;
	cout << "�������µ����о��룺" << endl;
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

Status changeTrainStatus(PTRAIN train){
	//�ı����������״̬
	if(!train) return ERROR;
	char normal[] = "����";
	char stop[] = "ͣ��";
	if(strcmp(train->status, normal) && strcmp(train->status, stop)) return ERROR;
    if(strcmp(train->status, normal))
    {
        strcpy(train->status, normal);
        cout << "����״̬�Ѹ���Ϊ" << normal << endl;
    }
    else
    {
        strcpy(train->status, stop);
        cout << "����״̬�Ѹ���Ϊ" << stop << endl;
    }
	
	return OK;
}

Status changeTrainDepTime(PTRAIN train){
	//��ȡ�û�����ķ���ʱ�䲢�浽ָ��ָ���������
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	char zero[] = "0:0";
	cout << "�������µķ���ʱ�䣺" << endl;
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

Status changeTrainArrTime(PTRAIN train){
	//��ȡ�û�����ĵ���ʱ�䲢�浽ָ��ָ���������
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	cout << "�������µĵ���ʱ�䣺" << endl;
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

Status changeTrainSpecialClass(PTRAIN train){
	//��ȡ�û�������ص����������浽ָ��ָ���������
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	int num;
	cout << "���µ������ص�������������������" << endl;
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

Status changeTrainFirstClass(PTRAIN train){
	//��ȡ�û������һ�����������浽ָ��ָ���������
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	int num;
	cout << "�������µ�һ����������" << endl;
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

Status changeTrainSecondClass(PTRAIN train){
	//��ȡ�û�����Ķ������������浽ָ��ָ���������
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	int num;
	cout << "�������µĶ�����������" << endl;
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

Status changeTrainStopNum(PTRAIN train){
	//��ȡ�û������ͣ��վ�������浽ָ��ָ���������
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	int num;
	cout << "�������µ�ͣ��վ���������޸�ͣ��վ��������Ҫ������������ͣ��վ��Ϣ����" << endl;
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

Status changeTrainStopName(PTRAIN train, int stop_num){
	//��ȡ��stop_num��ͣ��վ����
	char str[MAX_ARRAY_SIZE];
	cout << "�������µ�ͣ��վ" << stop_num << "����:" << endl;
	cin.getline(str, MAX_ARRAY_SIZE);
	if(checkCancel(str)) return ERROR;
	if(stop_num > 0)
	{
		strcpy(train->stop_names[stop_num - 1], str);
		return OK;
	}
	else return ERROR;
}

Status changeTrainStopArrTime(PTRAIN train, int stop_num){
	//��ȡ��stop_num��ͣ��վ��վʱ��
	char str[MAX_ARRAY_SIZE];
	cout << "�������µ�ͣ��վ" << stop_num << "��վʱ��:" << endl;
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
			strcpy(train->stop_arrival_time[stop_num], str);
			break;
		}
		if(!checkTimeByOrder(train->stop_departure_time[stop_num - 1], str) || !checkTimeByOrder(str, train->arrival_time))
		{
			cout << "��վʱ��Ӧ��ǰһͣ��վ����ʱ�����ȵ����յ�վʱ���磬����������" << endl;
			continue;
		}
		strcpy(train->stop_arrival_time[stop_num], str);
		break;
	}
	return OK;
}

Status changeTrainStopDepTime(PTRAIN train, int stop_num){
	//�޸ĵ�stop_num��ͣ��վ��վʱ��
	char str[MAX_ARRAY_SIZE];
	cout << "�������µ�ͣ��վ" << stop_num << "��վʱ��:" << endl;
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
		strcpy(train->stop_arrival_time[stop_num], str);
		break;
	}
	return OK;
}

Status changeTrainStopDistance(PTRAIN train, int stop_num){
	//�޸ĵ�stop_num��ͣ��վ���
	float distance;
	char str[MAX_ARRAY_SIZE];
	cout << "�������µ�ͣ��վ" << stop_num << "���:" << endl;
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

Status changeTrainStopInfo(PTRAIN train){
	/*
	�޸�ͣ��վ���ƣ���վʱ�䣬����ʱ�����̡�
	�޸�ʱ������ݺϷ��ԣ�ͣ��վ��վʱ��Ӧ��ǰһվ��վʱ�俿��
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
			!changeTrainStopName(train, i) ||
			!changeTrainStopArrTime(train, i) ||
			!changeTrainStopDepTime(train, i) ||
			!changeTrainStopDistance(train ,i)
		) return ERROR;
	}
	return OK;
}

Status changeTrainInfo(TRAINLIST& train_list){
	/*
    ����type��ֵ�޸ĸ�����Ϣ
    type=0��ȫ���޸�
	1���޸�ʼ����
	2���޸��յ���
	3���޸����о���
	4���޸�����״̬
	5���޸ķ���ʱ��
	6���޸ĵ���ʱ��
	7���޸��ص�������
    8���޸�һ��������
    9���޸Ķ���������
    10���޸�ͣ��վ����������޸ģ�������޸�����ͣ��վ��Ϣ��
    11���޸�ͣ��վ����
    12���޸�ͣ��վ��վʱ��
    13���޸�ͣ��վ��վʱ��
    14���޸�ͣ��վ���
    */
   	PTRAIN train = train_list.elem;
	int flag = 0; //����Ƿ��ҵ�����
	int i = 0; //��ų��������±�
	char str[MAX_ARRAY_SIZE];
	int type = 0;
	cout << "������Ҫ�޸ĵĸ������Σ�" << endl;
	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		for(i = 0; i < train_list.train_num; i++){
			if(!strcmp(train_list.train_value.name[i], str))
			{
				flag = 1;
				break;
			}
		}
		if(!flag)
		{
			cout << "δ�ҵ��ó��Σ����������룻" << endl;
			continue;
		} 
		break;
	}
	train += i; //ָ��ָ����Ҫ�޸ĵĳ���

	cout << "��ѡ����Ҫ�޸ĵ����ͣ������Ӧ�İ��������֣���" << endl;
	cout << "0:ȫ���޸�" << endl;
	cout << "1:�޸�ʼ����" << endl;
	cout << "2:�޸��յ���" << endl;
	cout << "3:�޸����о���" << endl;
	cout << "4:�޸�����״̬" << endl;
	cout << "5:�޸ķ���ʱ��" << endl;
	cout << "6:�޸ĵ���ʱ��" << endl;
	cout << "7:�޸��ص�������" << endl;
    cout << "8:�޸�һ��������" << endl;
    cout << "9:�޸Ķ���������" << endl;
    cout << "10:�޸�ͣ��վ����������޸ģ�������޸�����ͣ��վ��Ϣ��" << endl;
    cout << "11:�޸�ͣ��վ����" << endl;
    cout << "12:�޸�ͣ��վ��վʱ��" << endl;
    cout << "13:�޸�ͣ��վ��վʱ��" << endl;
    cout << "14:�޸�ͣ��վ���" << endl;
	cout << "15:������һ��" << endl;
	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		
		if(!checkNumber(str))
		{
			cout << "�������ֲ��Ϸ�������������" << endl;
			continue;
		}
		type = atoi(str);
		if(type < 0 || type > 15)
		{
			cout << "�������Ų���ȷ������������" << endl;
			continue;
		}
		break;
	}

    switch (type)
    {
    case 0:
        if(
		    !changeTrainOrigin(train) ||
		    !changeTrainDestination(train) ||
		    !changeTrainDistance(train) ||
		    !changeTrainStatus(train) ||
		    !changeTrainDepTime(train) ||
		    !changeTrainArrTime(train) ||
		    !changeTrainSpecialClass(train) ||
		    !changeTrainFirstClass(train) ||
		    !changeTrainSecondClass(train) ||
		    !changeTrainStopNum(train) ||
		    !changeTrainStopInfo(train)
	    )	return ERROR;
        break;
    case 1:
        if(!changeTrainOrigin(train)) return ERROR;
        strcpy(train->stop_names[0], train->origin);
        break;
    case 2:
        if(!changeTrainDestination(train)) return ERROR;
        strcpy(train->stop_names[train->stop_num - 1], train->destination);
        break;
    case 3:
        if(!changeTrainDistance(train)) return ERROR;
        train->stop_distance[train->stop_num - 1] = train->distance;
        break;
    case 4:
        if(!changeTrainStatus(train)) return ERROR;
        break;
    case 5:
        if(!changeTrainDepTime(train)) return ERROR;
        strcpy(train->stop_arrival_time[0], train->departure_time);
	    strcpy(train->stop_departure_time[0], train->departure_time);
        break;
    case 6:
        if(!changeTrainArrTime(train)) return ERROR;
        strcpy(train->stop_arrival_time[train->stop_num - 1], train->arrival_time);
	    strcpy(train->stop_departure_time[train->stop_num - 1], train->arrival_time);
        break;
    case 7:
        if(!changeTrainSpecialClass(train)) return ERROR;
        break;
    case 8:
        if(!changeTrainFirstClass(train)) return ERROR;
        break;
    case 9:
        if(!changeTrainSecondClass(train)) return ERROR;
        break;
    case 10:
        if(!changeTrainStopNum(train) || !changeTrainStopInfo(train)) return ERROR;
        break;
    case 11:
        if(!getStopNum(train, num)) return ERROR;
        if(!changeTrainStopName(train, num)) return ERROR;
        break;
    case 12:
        if(!getStopNum(train, num)) return ERROR;
        if(!changeTrainStopArrTime(train, num)) return ERROR;
        break;
    case 13:
        if(!getStopNum(train, num)) return ERROR;
        if(!changeTrainStopDepTime(train, num)) return ERROR;
        break;
    case 14:
        if(!getStopNum(train, num)) return ERROR;
        if(!changeTrainStopDistance(train, num)) return ERROR;
        break;
	case 15:
		return CANCEL;
		break;
    default:
		return ERROR;
        break;
    }
	
	return OK;
}

Status changeTrain(TRAINLIST& train_list){
	/*
    ����type��ֵ�޸ĸ�����Ϣ
    type=0��ȫ���޸�
	1���޸�ʼ����
	2���޸��յ���
	3���޸����о���
	4���޸�����״̬
	5���޸ķ���ʱ��
	6���޸ĵ���ʱ��
	7���޸��ص�������
    8���޸�һ��������
    9���޸Ķ���������
    10���޸�ͣ��վ����������޸ģ�������޸�����ͣ��վ��Ϣ��
    11���޸�ͣ��վ����
    12���޸�ͣ��վ��վʱ��
    13���޸�ͣ��վ��վʱ��
    14���޸�ͣ��վ���
    */
   	int status = changeTrainInfo(train_list);
   	if(!status)
   	{
		cout << "�޸�ʧ��" << endl;
   	}
	if(status == OK)
	{
		cout << "�޸ĳɹ�" << endl;
		setTrainValue(train_list);
	}
	return OK;
}

Status turnTrainStatus(TRAINLIST& train_list){
	//�ı����������״̬�������ͱ��ͣ�ˣ���֮�෴
	PTRAIN train = train_list.elem;
	int flag = 0; //����Ƿ��ҵ�����
	int i = 0; //��ų��������±�
	char str[MAX_ARRAY_SIZE];
	int type = 0;
	cout << "������Ҫ�޸ĵĸ������Σ�" << endl;
	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		for(i = 0; i < train_list.train_num; i++){
			if(!strcmp(train_list.train_value.name[i], str))
			{
				flag = 1;
				break;
			}
		}
		if(!flag)
		{
			cout << "δ�ҵ��ó��Σ����������룻" << endl;
			continue;
		} 
		break;
	}
	train += i; //ָ��ָ����Ҫ�޸ĵĳ���


	char normal[] = "����";
	char stop[] = "ͣ��";
	if(strcmp(train->status, normal) && strcmp(train->status, stop)) return ERROR;
    if(strcmp(train->status, normal))
    {
        strcpy(train->status, normal);
        cout << "����״̬�Ѹ���Ϊ" << normal << endl;
    }
    else
    {
        strcpy(train->status, stop);
        cout << "����״̬�Ѹ���Ϊ" << stop << endl;
    }
	setTrainValue(train_list);
	return OK;
}