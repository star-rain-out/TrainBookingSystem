#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#include "../Check.h"
#include "Passenger.h"
#include "InsertPassenger.h"
#include "SearchPassenger.h"
#include "DeletePassenger.h"
#include "ChangePassenger.h"
using namespace std;

Status passengerMenu(PPASSENGER& pas_list){
	//乘客信息管理主体菜单
    char str[MAX_ARRAY_SIZE];
	char c = ' ';
	cout << "请选择需要执行的操作：" << endl;
	cout << "1.输出所有乘客信息" << endl
	<< "2.新增一位乘客信息" << endl
	<< "3.删除一位乘客信息" << endl
	<< "4.修改乘客信息" << endl
	<< "5.查找乘客信息" << endl
	<< "6.返回上一级菜单" << endl;

	while (1)
    {
        cin.get(c);
        cin.ignore(MAX_ARRAY_SIZE, '\n');
        if(c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6')
        {
            cout << "输入的选项有误，请重新输入" << endl;
            continue;
        }
        break;
    }
	
	switch (c)
	{
	case '1':
		displayPasList(pas_list);
		break;
	case '2':
		insertPassenger(pas_list);
		break;
	case '3':
		deletePassenger(pas_list);
		break;
	case '4':
		changePassenger(pas_list);
		break;
	case '5':
		searchPassenger(pas_list);
		break;
	case '6':
		return CANCEL;
		break;
	default:
		return ERROR;
		break;
	}
    
    return OK;
}

int createPassengerMenu(){
	//初始化信息并创建乘客信息管理菜单
    char filename[] = "..\\data\\passenger.txt";
    PPASSENGER pas_list;
    initPasList(pas_list);
    inputPasList(pas_list, filename);
    while (1)
	{
		if(passengerMenu(pas_list) == CANCEL)
		break;
	}
    outputPasList(pas_list, filename);
    freePasList(pas_list);
    return 0;
}