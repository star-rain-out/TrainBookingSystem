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
    //��ʼ����Ʊ����ͷ
    book_list = (PBOOKING)malloc(sizeof(BOOKING));
    if(!book_list) return ERROR;
    char booking_num[] = "00000000-0000-000";
    strcpy(book_list->booking_num, booking_num);
    book_list->next = NULL;
    return OK;
}

Status inputBookList(PBOOKING& book_list, char* filename){
    //���ļ����붩Ʊ��Ϣ
    if(!book_list) return ERROR;
    ifstream inFile;
	inFile.open(filename);
    if (!inFile) {
	    cout << "�޷����ļ�";
	    exit(1); // ��������
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
    //�����Ʊ��Ϣ���ļ�
    if(!book_list) return ERROR;
    ofstream outFile;
	outFile.open(filename, ios::out);
    if (!outFile) {
	    cout << "�޷����ļ�";
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
    //����Ļ�����Ʊ��Ϣ
    PBOOKING p = book_list->next;
    cout << setiosflags(ios::left) << setw(20) << "������" << "|" << setw(10) << "�˳�����" 
    << "|" << setw(6) << "����" << "|" << setw(10) << "ʼ��վ" << "|" << setw(10) 
    << "�յ�վ" << "|" << setw(10) << "֤�����" << "|" << setw(20) << "֤����"
    << "|" << setw(10) << "�˿�����" << "|" << setw(10) << "����ʱ��"  << "|" 
    << setw(10) << "����ʱ��" << "|" << setw(10) << "��λ�ȼ�" << "|" << setw(8) 
    << "��λ��" << "|" << setw(6) << "Ʊ��"<< endl;
    //����Ϊ��ͷ
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
    //����Ļ�����ͷ
    cout << setiosflags(ios::left) << setw(20) << "������" << "|" << setw(10) << "�˳�����" 
    << "|" << setw(6) << "����" << "|" << setw(10) << "ʼ��վ" << "|" << setw(10) 
    << "�յ�վ" << "|" << setw(10) << "֤�����" << "|" << setw(20) << "֤����"
    << "|" << setw(10) << "�˿�����" << "|" << setw(10) << "����ʱ��"  << "|" 
    << setw(10) << "����ʱ��" << "|" << setw(10) << "��λ�ȼ�" << "|" << setw(8) 
    << "��λ��" << "|" << setw(6) << "Ʊ��"<< endl;
    cout << "---------------------------------------------------------------------------"
    << "----------------------------------------------------------------------------" << endl;
}

void displayBookByPtr(PBOOKING booking){
    //����ָ��ָ������������Ʊ��Ϣ
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
    //����ָ��ָ������ݴ�ӡ��Ʊ
    if(!booking) return;
    cout << "======================================" << endl;
    cout << "    " << booking->origin << "վ" << " " << booking->train_name << "-->"
    << " " << booking->destination << "վ" << endl;
    cout << getDateStr(getDateByStr(booking->date)) << booking->departure_time << "��"
    << "   " << booking->seat_level << " " << "��λ��" << booking->seat_num << endl;
    cout << "Ʊ��:" << booking->price << "Ԫ" << endl;
    cout << "�޳˵��յ��γ�" << endl;
    cout << "�����ţ�" << booking->booking_num << endl;
    cout << "======================================" << endl;
}

Status printBooking(PBOOKING book_list){
    //��ӡ��Ʊ����
    if(!book_list) return ERROR;
    char booking_num[MAX_ARRAY_SIZE];
    cout << "��������Ҫ��ӡ��Ʊ�Ķ�����:" << endl;
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
        cout << "������Ķ����Ų�����!" << endl;
        return ERROR;
    }
    printBookingByPtr(p);
    return OK;
}


void freeBookList(PBOOKING& book_list){
    //�ͷŶ�Ʊ����ڵ�
    PBOOKING p = book_list;
    PBOOKING q = book_list;
    while (q)
    {
        p = q;
        q = q->next;
        free(p);
    }
}



