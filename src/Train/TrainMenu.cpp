#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#include "Train.h"
#include "InsertTrain.h"
#include "SearchTrain.h"
#include "ChangeTrain.h"
#include "../Check.h"
#define MAX_ARRAY_SIZE 50

#define CANCEL 2

using namespace std;

Status trainMenu(TRAINLIST& train_list){
	//�������ι���˵����庯��
    char str[MAX_ARRAY_SIZE];
	int type = 0;
	cout << "��ѡ����Ҫִ�еĲ�����" << endl;
	cout << "1.������и�����Ϣ" << endl
	<< "2.����һ����������" << endl
	<< "3.ͣ�ˣ������ã�һ����������" << endl
	<< "4.�޸�һ����������" << endl
	<< "5.����һ����������" << endl
	<< "6.������һ���˵�" << endl;

	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		
		if(!checkNumber(str))
		{
			cout << "�������ֲ��Ϸ�������������" << endl;
			continue;
		}
		type = atoi(str);
		if(type < 1 || type > 6)
		{
			cout << "�������Ų���ȷ������������" << endl;
			continue;
		}
		break;
	}
	
	switch (type)
	{
	case 1:
		displayTrainList(train_list);
		break;
	case 2:
		insertTrain(train_list);
		break;
	case 3:
		turnTrainStatus(train_list);
		break;
	case 4:
		changeTrain(train_list);
		break;
	case 5:
		searchTrain(train_list);
		break;
	case 6:
		return CANCEL;
		break;
	default:
		return ERROR;
		break;
	}
    
    return OK;
}

int createTrainMenu() {
	//��ʼ����Ϣ���������˵�
	TRAINLIST train_list;
    TRAINVALUE train_value;
    char filename[] = "..\\data\\train.txt";
	inputTrainList(train_list, filename);
	while (1)
	{
		if(trainMenu(train_list) == CANCEL)
		break;
	}
	outputTrainList(train_list, filename);
	deleteTrainList(train_list);
    return 0;
}









