#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "Passenger.h"
using namespace std;

Status searchPasByName(PPASSENGER pas_list, PPASSENGER& passenger, char* name){
    //根据姓名查询乘客并将passenger指针指向对应位置
    if(!pas_list) return ERROR;
    PPASSENGER p = passenger->next;
    while(p)
    {
        if(!strcmp(name, p->name))
        {
            break;
        }
        p = p->next;
    }
    if(!p)  return ERROR;
    passenger = p;
    return OK;
}

Status searchPasByIdNum(PPASSENGER pas_list, PPASSENGER& passenger, char* id_num){
    //根据证件号查询乘客并将passenger指针指向对应位置
    if(!pas_list) return ERROR;
    PPASSENGER p = pas_list->next;
    while(p)
    {
        if(!strcmp(id_num, p->id_num))
        {
            break;
        }
        p = p->next;
    }
    if(!p)  return ERROR;
    passenger = p;
    return OK;
}

Status searchPasByPhoneNum(PPASSENGER pas_list, PPASSENGER& passenger, char* phone_num){
    //根据联系电话查询乘客并将passenger指针指向对应位置
    if(!pas_list) return ERROR;
    PPASSENGER p = passenger->next;
    while(p)
    {
        if(!strcmp(phone_num, p->phone_num))
        {
            break;
        }
        p = p->next;
    }
    if(!p)  return ERROR;
    passenger = p;
    return OK;
}

Status searchPasByEmerName(PPASSENGER pas_list, PPASSENGER& passenger, char* emer_name){
    //根据紧急联系人姓名查询乘客并将passenger指针指向对应位置
    if(!pas_list) return ERROR;
    PPASSENGER p = passenger->next;
    while(p)
    {
        if(!strcmp(emer_name, p->emer_name))
        {
            break;
        }
        p = p->next;
    }
    if(!p)  return ERROR;
    passenger = p;
    return OK;
}

Status searchPassenger(PPASSENGER pas_list){
    /*
    根据选项查询乘客信息
    1.根据姓名查询
    2.根据证件号查询
    3.根据联系电话查询
    4.根据紧急联系人姓名查询
    */
    if(!pas_list) return ERROR;
    char c = ' '; //保存查找选项“1,2,3,4”
    char str[MAX_ARRAY_SIZE]; //保存查找内容
    int flag = 0; //标记是否找到
    PPASSENGER p = pas_list;
    cout << "请选择查找选项：" << endl
    << "1.根据姓名查询" << endl
    << "2.根据证件号查询" << endl
    << "3.根据联系电话查询" << endl
    << "4.根据紧急联系人姓名查询" << endl;
    while (1)
    {
        cin.get(c);
        cin.ignore(MAX_ARRAY_SIZE, '\n');
        if(c != '1' && c != '2' && c != '3' && c != '4')
        {
            cout << "输入的选项有误，请重新输入" << endl;
            continue;
        }
        break;
    }
    cout << "请输入查找内容" << endl;
    cin.getline(str, MAX_ARRAY_SIZE);
    switch (c)
    {
    case '1':
        flag = searchPasByName(pas_list, p, str);
        if(flag == OK)
        {
            displayPasHeader();
            displayPasByPtr(p);
            while (searchPasByName(pas_list, p, str))
            {
                displayPasByPtr(p);
            }
        }
        break;
    case '2':
        flag = searchPasByIdNum(pas_list, p, str);
        if(flag == OK)
        {
            displayPasHeader();
            displayPasByPtr(p);
        }
        break;
    case '3':
        flag = searchPasByPhoneNum(pas_list, p, str);
        if(flag == OK)
        {
            displayPasHeader();
            displayPasByPtr(p);
            while (searchPasByPhoneNum(pas_list, p, str))
            {
                displayPasByPtr(p);
            }
        }
        break;
    case '4':
        flag = searchPasByEmerName(pas_list, p, str);
        if(flag == OK)
        {
            displayPasHeader();
            displayPasByPtr(p);
            while (searchPasByEmerName(pas_list, p, str))
            {
                displayPasByPtr(p);
            }
        }
        break;
    default:
        break;
    }
    if(flag == 0)
    {
        cout << "未查询到相关信息" << endl;
        return ERROR;
    }
    
    return OK;
}