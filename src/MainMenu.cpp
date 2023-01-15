#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include "Check.h"
#include "./Train/TrainMenu.h"
#include "./Passenger/PassengerMenu.h"
#include "./Booking/BookingMenu.h"
#define CANCEL 2
using namespace std;

void displayTitle(){
    //输出主程序标题艺术字
    char filename[] = "..\\data\\title.txt";
    ifstream inFile;
	inFile.open(filename);
    if (!inFile) {
	    cout << "无法打开文件";
	    exit(1);
	}
    string str;
    while (getline(inFile, str))
    {
        cout << str << endl;
    }
}

Status mainMenu(){
    //主菜单函数，包括三个子菜单
    char str[MAX_ARRAY_SIZE];
	char c = ' ';
	cout << "请选择菜单(输入阿拉伯数字即可):" << endl;
	cout << "1.高铁车次信息管理" << endl
	<< "2.乘客信息管理" << endl
	<< "3.高铁订票信息管理" << endl
	<< "4.退出系统" << endl;
	while (1)
    {
        cin.get(c);
        cin.ignore(MAX_ARRAY_SIZE, '\n');
        if(c != '1' && c != '2' && c != '3' && c != '4')
        {
            cout << "输入的选项有误，请重新输入" << endl;
            continue;
        }
        break;
    }
	
	switch (c)
	{
	case '1':
		createTrainMenu();
		break;
	case '2':
		createPassengerMenu();
		break;
	case '3':
		creatBookingMenu();
		break;
	case '4':
		return CANCEL;
		break;
	default:
		return ERROR;
		break;
	}
    
    return OK;
}

int main(){
    //程序入口，输出标题并创建主菜单
    displayTitle();
    while(1)
    {
        if(mainMenu() == CANCEL)
		break;
    }
    return 0;
}