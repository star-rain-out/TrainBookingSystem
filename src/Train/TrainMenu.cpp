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
	//高铁车次管理菜单主体函数
    char str[MAX_ARRAY_SIZE];
	int type = 0;
	cout << "请选择需要执行的操作：" << endl;
	cout << "1.输出所有高铁信息" << endl
	<< "2.新增一辆高铁车次" << endl
	<< "3.停运（或启用）一辆高铁车次" << endl
	<< "4.修改一辆高铁车次" << endl
	<< "5.查找一辆高铁车次" << endl
	<< "6.返回上一级菜单" << endl;

	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		
		if(!checkNumber(str))
		{
			cout << "输入数字不合法，请重新输入" << endl;
			continue;
		}
		type = atoi(str);
		if(type < 1 || type > 6)
		{
			cout << "输入的序号不正确，请重新输入" << endl;
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
	//初始化信息，并创建菜单
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









