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
	//�˿���Ϣ��������˵�
    char str[MAX_ARRAY_SIZE];
	char c = ' ';
	cout << "��ѡ����Ҫִ�еĲ�����" << endl;
	cout << "1.������г˿���Ϣ" << endl
	<< "2.����һλ�˿���Ϣ" << endl
	<< "3.ɾ��һλ�˿���Ϣ" << endl
	<< "4.�޸ĳ˿���Ϣ" << endl
	<< "5.���ҳ˿���Ϣ" << endl
	<< "6.������һ���˵�" << endl;

	while (1)
    {
        cin.get(c);
        cin.ignore(MAX_ARRAY_SIZE, '\n');
        if(c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6')
        {
            cout << "�����ѡ����������������" << endl;
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
	//��ʼ����Ϣ�������˿���Ϣ����˵�
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