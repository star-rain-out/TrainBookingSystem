#pragma once
#include <time.h>

#define MAX_ARRAY_SIZE 50
#define ID_NUM_SIZE 19
#define NAME_SIZE 20
#define ID_TYPE_SIZE 13

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define CANCEL 2
typedef int Status;

typedef struct Booking
{
    char booking_num[18];  //订单号
    char date[9];           //乘车日期
    char train_name[5];     //车次
    char origin[MAX_ARRAY_SIZE]; //始发站
    char destination[MAX_ARRAY_SIZE]; //终到站
    char id_type[ID_TYPE_SIZE]; //证件类别
    char id_num[ID_NUM_SIZE];   //证件号
    char passenger_name[NAME_SIZE]; //乘客姓名
    char departure_time[6];     //发车时间
    char arrival_time[6];       //到达时间
    char seat_level[13];        //座位等级
    int seat_num;           //座位号
    double price;           //票价
    struct Booking * next;
}BOOKING, *PBOOKING;


Status initBookList(PBOOKING& book_list);
Status inputBookList(PBOOKING& book_list, char* filename);
Status outputBookList(PBOOKING book_list, char* filename);
void displayBookList(PBOOKING book_list);
Status printBooking(PBOOKING book_list);
void freeBookList(PBOOKING& book_list);
void displayBookHeader();
void displayBookByPtr(PBOOKING booking);
void printBookingByPtr(PBOOKING booking);