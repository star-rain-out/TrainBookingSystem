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
    //根据订单号删除订单
    if(!book_list) return ERROR;
    if(!book_list->next) return ERROR;
    PBOOKING p = book_list->next;
    PBOOKING q = book_list; //q指向p的前一个指针
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
    //获取当前系统时间，然后与dep_time-2小时进行比较，如果靠前返回OK，否则返回ERROR
    time_t timep;
    time(&timep);
    struct tm *p;
    p = gmtime(&timep);
    int hour = 8 + p->tm_hour;
    int minute = p->tm_min;
    //以上为获取当前系统时间
    //cout << "当前系统时间:" << hour << ':' << minute << endl;
    char* now = (char*)malloc(6 * sizeof(char));
    sprintf(now, "%d:%d", hour + 2, minute);
    if(!checkTimeByOrder(now, dep_time))
    {
        return ERROR;
    }
    else return OK;
}

Status deleteBooking(PBOOKING& book_list){
    //删除订票信息的主体函数
    if(!book_list) return ERROR;
    char booking_num[MAX_ARRAY_SIZE];
    cout << "请输入需要退票的订单号:" << endl;
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
    if(!checkDateByOrder1(getSysTime(), getDateByStr(p->date)))
    {
        if(checkDateByOrder(getSysTime(), getDateByStr(p->date)))
        {
            if(!compareTime(p->departure_time))
            {
                cout << "当前时间距离高铁出发在两小时之内,需要收取5%的退票费" << endl;
                cout << "退票成功,退回金额为:" << p->price << '*' << "%95 = " << p->price * 0.95
                << "元" << endl; 
            }
            else
            {
                deleteBookByBookNum(book_list, booking_num);
                cout << "退票成功,退回金额为:" << p->price << "元" << endl;
            }
        }
        else
        {
            cout << "当前时间距离高铁出发在两小时之内,需要收取5%的退票费" << endl;
            cout << "退票成功,退回金额为:" << p->price << '*' << "%95 = " << p->price * 0.95
            << "元" << endl;
        }
    }
    else
    {
        
        cout << "退票成功,退回金额为:" << p->price << "元" << endl;
    }
    deleteBookByBookNum(book_list, booking_num);
    return OK;
}