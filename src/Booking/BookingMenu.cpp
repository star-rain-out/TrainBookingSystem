#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "../Check.h"
#include "Booking.h"
#include "InsertBooking.h"
#include "DeleteBooking.h"
#include "SearchBooking.h"

Status bookingMenu(PBOOKING& book_list){
    //��Ʊ�˵�����
    char str[MAX_ARRAY_SIZE];
	char c = ' ';
	cout << "��ѡ����Ҫִ�еĲ�����" << endl;
	cout << "1.������г�Ʊ��Ϣ" << endl
	<< "2.��Ʊ" << endl
	<< "3.��Ʊ" << endl
	<< "4.��ѯ��Ʊ" << endl
	<< "5.��ӡһ�ų�Ʊ" << endl
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
		displayBookList(book_list);
		break;
	case '2':
		insertBookList(book_list);
		break;
	case '3':
		deleteBooking(book_list);
		break;
	case '4':
		searchBooking(book_list);
		break;
	case '5':
		printBooking(book_list);
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

int creatBookingMenu(){
    //��ʼ����Ʊ��������
    char filename[] = "..\\data\\booking.txt";
    char filename2[] = "..\\data\\train.txt";
    PBOOKING book_list;   //���嶩Ʊ����ͷ
    TRAINLIST train_list;  //�������˳���
    initBookList(book_list); //��ʼ����Ʊ����
    inputBookList(book_list, filename);
    inputTrainList(train_list, filename2);
    
    while (1)
	{
		if(bookingMenu(book_list) == CANCEL)
		break;
	}
    outputBookList(book_list, filename);
    freeBookList(book_list);
    return 0;
}