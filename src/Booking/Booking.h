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
    char booking_num[18];  //������
    char date[9];           //�˳�����
    char train_name[5];     //����
    char origin[MAX_ARRAY_SIZE]; //ʼ��վ
    char destination[MAX_ARRAY_SIZE]; //�յ�վ
    char id_type[ID_TYPE_SIZE]; //֤�����
    char id_num[ID_NUM_SIZE];   //֤����
    char passenger_name[NAME_SIZE]; //�˿�����
    char departure_time[6];     //����ʱ��
    char arrival_time[6];       //����ʱ��
    char seat_level[13];        //��λ�ȼ�
    int seat_num;           //��λ��
    double price;           //Ʊ��
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