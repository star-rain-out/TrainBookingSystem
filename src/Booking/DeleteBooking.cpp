#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Booking.h"
#include "SearchBooking.h"
#include "../Check.h"
using namespace std;

Status deleteBookByBookNum(PBOOKING& book_list, char* booking_num)
{
    //���ݶ�����ɾ������
    if(!book_list) return ERROR;
    if(!book_list->next) return ERROR;
    PBOOKING p = book_list->next;
    PBOOKING q = book_list; //qָ��p��ǰһ��ָ��
    while(p)
    {
        if(!strcmp(p->booking_num, booking_num))
        {
            q->next = p->next;
            free(p);
            break;
        }
        q = p;
        p = p->next;
    }
    return OK;
}

Status compareTime(char* dep_time){
    //��ȡ��ǰϵͳʱ�䣬Ȼ����dep_time-2Сʱ���бȽϣ������ǰ����OK�����򷵻�ERROR
    time_t timep;
    time(&timep);
    struct tm *p;
    p = gmtime(&timep);
    int hour = 8 + p->tm_hour;
    int minute = p->tm_min;
    //����Ϊ��ȡ��ǰϵͳʱ��
    //cout << "��ǰϵͳʱ��:" << hour << ':' << minute << endl;
    char* now = (char*)malloc(6 * sizeof(char));
    sprintf(now, "%d:%d", hour + 2, minute);
    if(!checkTimeByOrder(now, dep_time))
    {
        return ERROR;
    }
    else return OK;
}

Status deleteBooking(PBOOKING& book_list){
    //ɾ����Ʊ��Ϣ�����庯��
    if(!book_list) return ERROR;
    char booking_num[MAX_ARRAY_SIZE];
    cout << "��������Ҫ��Ʊ�Ķ�����:" << endl;
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
    if(!checkDateByOrder1(getSysTime(), getDateByStr(p->date)))
    {
        if(checkDateByOrder(getSysTime(), getDateByStr(p->date)))
        {
            if(!compareTime(p->departure_time))
            {
                cout << "��ǰʱ����������������Сʱ֮��,��Ҫ��ȡ5%����Ʊ��" << endl;
                cout << "��Ʊ�ɹ�,�˻ؽ��Ϊ:" << p->price << '*' << "%95 = " << p->price * 0.95
                << "Ԫ" << endl; 
            }
            else
            {
                deleteBookByBookNum(book_list, booking_num);
                cout << "��Ʊ�ɹ�,�˻ؽ��Ϊ:" << p->price << "Ԫ" << endl;
            }
        }
        else
        {
            cout << "��ǰʱ����������������Сʱ֮��,��Ҫ��ȡ5%����Ʊ��" << endl;
            cout << "��Ʊ�ɹ�,�˻ؽ��Ϊ:" << p->price << '*' << "%95 = " << p->price * 0.95
            << "Ԫ" << endl;
        }
    }
    else
    {
        
        cout << "��Ʊ�ɹ�,�˻ؽ��Ϊ:" << p->price << "Ԫ" << endl;
    }
    deleteBookByBookNum(book_list, booking_num);
    return OK;
}