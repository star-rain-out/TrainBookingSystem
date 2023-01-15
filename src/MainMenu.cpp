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
    //������������������
    char filename[] = "..\\data\\title.txt";
    ifstream inFile;
	inFile.open(filename);
    if (!inFile) {
	    cout << "�޷����ļ�";
	    exit(1);
	}
    string str;
    while (getline(inFile, str))
    {
        cout << str << endl;
    }
}

Status mainMenu(){
    //���˵����������������Ӳ˵�
    char str[MAX_ARRAY_SIZE];
	char c = ' ';
	cout << "��ѡ��˵�(���밢�������ּ���):" << endl;
	cout << "1.����������Ϣ����" << endl
	<< "2.�˿���Ϣ����" << endl
	<< "3.������Ʊ��Ϣ����" << endl
	<< "4.�˳�ϵͳ" << endl;
	while (1)
    {
        cin.get(c);
        cin.ignore(MAX_ARRAY_SIZE, '\n');
        if(c != '1' && c != '2' && c != '3' && c != '4')
        {
            cout << "�����ѡ����������������" << endl;
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
    //������ڣ�������Ⲣ�������˵�
    displayTitle();
    while(1)
    {
        if(mainMenu() == CANCEL)
		break;
    }
    return 0;
}