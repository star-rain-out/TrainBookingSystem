#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include "../Check.h"
#include "Booking.h"
#include "InsertBooking.h"
#include "SearchBooking.h"
#include "DeleteBooking.h"
#include "../Train/Train.h"
#include "../Train/SearchTrain.h"
using namespace std;

Status initBookList(PBOOKING& book_list){
    //初始化订票链表头
    book_list = (PBOOKING)malloc(sizeof(BOOKING));
    if(!book_list) return ERROR;
    char booking_num[] = "00000000-0000-000";
    strcpy(book_list->booking_num, booking_num);
    book_list->next = NULL;
    return OK;
}

Status inputBookList(PBOOKING& book_list, char* filename){
    //从文件读入订票信息
    if(!book_list) return ERROR;
    ifstream inFile;
	inFile.open(filename);
    if (!inFile) {
	    cout << "无法打开文件";
	    exit(1); // 结束进程
	}
    PBOOKING q = book_list;
    PBOOKING p = (PBOOKING)malloc(sizeof(BOOKING));
    while (inFile >> p->booking_num >> p->date >> p->train_name >> p->origin >> p->destination 
            >> p->id_type >> p->id_num >> p->passenger_name >> p->departure_time >> p->arrival_time
            >> p->seat_level >> p->seat_num >> p->price)
    {
        insertBookListTail(book_list, p);
    }
    
    inFile.close();
    return OK;
}

Status outputBookList(PBOOKING book_list, char* filename){
    //输出订票信息至文件
    if(!book_list) return ERROR;
    ofstream outFile;
	outFile.open(filename, ios::out);
    if (!outFile) {
	    cout << "无法打开文件";
	    exit(1); 
	}
    PBOOKING p = book_list->next;
    while (p)
    {
        outFile << p->booking_num << " "
        << p->date << " "
        << p->train_name << " "
        << p->origin << " "
        << p->destination << " "
        << p->id_type << " "
        << p->id_num << " "
        << p->passenger_name << " "
        << p->departure_time << " "
        << p->arrival_time<< " "
        << p->seat_level << " "
        << p->seat_num << " "
        << p->price << endl;
        p = p->next;
    }
    
    outFile.close();
    return OK;
}

void displayBookList(PBOOKING book_list){
    //向屏幕输出订票信息
    PBOOKING p = book_list->next;
    cout << setiosflags(ios::left) << setw(20) << "订单号" << "|" << setw(10) << "乘车日期" 
    << "|" << setw(6) << "车次" << "|" << setw(10) << "始发站" << "|" << setw(10) 
    << "终到站" << "|" << setw(10) << "证件类别" << "|" << setw(20) << "证件号"
    << "|" << setw(10) << "乘客姓名" << "|" << setw(10) << "发车时间"  << "|" 
    << setw(10) << "到达时间" << "|" << setw(10) << "座位等级" << "|" << setw(8) 
    << "座位号" << "|" << setw(6) << "票价"<< endl;
    //以上为表头
    cout << "---------------------------------------------------------------------------"
    << "----------------------------------------------------------------------------" << endl;
    while (p)
    {
        cout << setiosflags(ios::left)
        << setw(20) << p->booking_num << "|"
        << setw(10) << p->date << "|"
        << setw(6) << p->train_name << "|"
        << setw(10) << p->origin << "|"
        << setw(10) << p->destination << "|"
        << setw(10) << p->id_type << "|"
        << setw(20) << p->id_num << "|"
        << setw(10) << p->passenger_name << "|"
        << setw(10) << p->departure_time << "|"
        << setw(10) << p->arrival_time << "|"
        << setw(10) << p->seat_level << "|"
        << setw(8) << p->seat_num << "|"
        << setw(6) << p->price << endl;
        p = p->next;
    }
}

void displayBookHeader(){
    //向屏幕输出表头
    cout << setiosflags(ios::left) << setw(20) << "订单号" << "|" << setw(10) << "乘车日期" 
    << "|" << setw(6) << "车次" << "|" << setw(10) << "始发站" << "|" << setw(10) 
    << "终到站" << "|" << setw(10) << "证件类别" << "|" << setw(20) << "证件号"
    << "|" << setw(10) << "乘客姓名" << "|" << setw(10) << "发车时间"  << "|" 
    << setw(10) << "到达时间" << "|" << setw(10) << "座位等级" << "|" << setw(8) 
    << "座位号" << "|" << setw(6) << "票价"<< endl;
    cout << "---------------------------------------------------------------------------"
    << "----------------------------------------------------------------------------" << endl;
}

void displayBookByPtr(PBOOKING booking){
    //根据指针指向的内容输出订票信息
    PBOOKING p = booking;
    cout << setiosflags(ios::left)
    << setw(20) << p->booking_num << "|"
    << setw(10) << p->date << "|"
    << setw(6) << p->train_name << "|"
    << setw(10) << p->origin << "|"
    << setw(10) << p->destination << "|"
    << setw(10) << p->id_type << "|"
    << setw(20) << p->id_num << "|"
    << setw(10) << p->passenger_name << "|"
    << setw(10) << p->departure_time << "|"
    << setw(10) << p->arrival_time << "|"
    << setw(10) << p->seat_level << "|"
    << setw(8) << p->seat_num << "|"
    << setw(6) << p->price << endl;
}

void printBookingByPtr(PBOOKING booking){
    //根据指针指向的内容打印车票
    if(!booking) return;
    cout << "======================================" << endl;
    cout << "    " << booking->origin << "站" << " " << booking->train_name << "-->"
    << " " << booking->destination << "站" << endl;
    cout << getDateStr(getDateByStr(booking->date)) << booking->departure_time << "开"
    << "   " << booking->seat_level << " " << "座位号" << booking->seat_num << endl;
    cout << "票价:" << booking->price << "元" << endl;
    cout << "限乘当日当次车" << endl;
    cout << "订单号：" << booking->booking_num << endl;
    cout << "======================================" << endl;
}

Status printBooking(PBOOKING book_list){
    //打印车票函数
    if(!book_list) return ERROR;
    char booking_num[MAX_ARRAY_SIZE];
    cout << "请输入需要打印车票的订单号:" << endl;
    cin.getline(booking_num, MAX_ARRAY_SIZE);
    PBOOKING p = book_list->next;
    int flag = 0;
    while(p)
    {
        if(!strcmp(p->booking_num, booking_num))
        {
            flag = 1;
            break;
        }
        p = p->next;
    }
    if(!flag)
    {
        cout << "您输入的订单号不存在!" << endl;
        return ERROR;
    }
    printBookingByPtr(p);
    return OK;
}


void freeBookList(PBOOKING& book_list){
    //释放订票链表节点
    PBOOKING p = book_list;
    PBOOKING q = book_list;
    while (q)
    {
        p = q;
        q = q->next;
        free(p);
    }
}



