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
    //订票菜单函数
    char str[MAX_ARRAY_SIZE];
	char c = ' ';
	cout << "请选择需要执行的操作：" << endl;
	cout << "1.输出所有车票信息" << endl
	<< "2.订票" << endl
	<< "3.退票" << endl
	<< "4.查询余票" << endl
	<< "5.打印一张车票" << endl
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
    //初始化订票链表并运行
    char filename[] = "..\\data\\booking.txt";
    char filename2[] = "..\\data\\train.txt";
    PBOOKING book_list;   //定义订票链表头
    TRAINLIST train_list;  //定义高铁顺序表
    initBookList(book_list); //初始化订票链表
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