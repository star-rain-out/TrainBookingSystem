#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "Passenger.h"
#include "SearchPassenger.h"
#include "../Check.h"
using namespace std;

Status insertPasListByPtr(PPASSENGER& pas_list, PPASSENGER& passenger){
    //将passenger指针指向的内容插入乘客信息链表当中
    if(!passenger) return ERROR;
    PPASSENGER p = pas_list;
    PPASSENGER q = (PPASSENGER)malloc(sizeof(PASSENGER));
    q->next = NULL;
    while (p->next)
    {
        p = p->next;
    }
    strcpy(q->id_num, passenger->id_num);
    strcpy(q->name, passenger->name);
    strcpy(q->id_type, passenger->id_type);
    strcpy(q->phone_num, passenger->phone_num);
    strcpy(q->emer_name, passenger->emer_name);
    strcpy(q->emer_phone_num, passenger->emer_phone_num);
    p->next = q;
    return OK;
}

Status getPasName(PPASSENGER& passenger){
    //从屏幕获取输入内容并放入指针指向的姓名中
    if(!passenger) return ERROR;
    char str[MAX_ARRAY_SIZE];
    cout << "请输入乘客姓名：" << endl;
    cin.getline(str, MAX_ARRAY_SIZE);
    if(checkCancel(str)) return ERROR;
    strcpy(passenger->name, str);
    return OK;
}

Status getPasIdType(PPASSENGER& passenger){
    //从屏幕获取输入内容并放入指针指向的证件类型中
    if(!passenger) return ERROR;
    char str[8];
    int type = 0;
    
    cout << "请输入证件号类型(1为身份证,2为护照):" << endl;
    while (1)
    {
        cin.getline(str, MAX_ARRAY_SIZE);
        if(checkCancel(str)) return ERROR;
        type = atoi(str);
        if(type != 1 && type != 2)
        {
            cout << "输入格式错误！" << endl;
            continue;
        }
        break;
    }
    switch (type)
    {
    case 1:
        strcpy(passenger->id_type, ID);
        break;
    case 2:
        strcpy(passenger->id_type, PASSPORT);
        break;
    default:
        cout << "证件类型不正确！" << endl;
        return ERROR;
        break;
    }
    return OK;
}

Status getPasIdNum(PPASSENGER pas_list, PPASSENGER& passenger){
    //从屏幕获取输入内容并放入指针指向的证件号码中
    if(!passenger) return ERROR;
    int type = checkIdType(passenger->id_type); //获取证件类型
    PPASSENGER q; //查找证件号函数的参数
    if(!type)
    {
        cout << "未获取到证件类型" << endl;
        return ERROR;
    }
    char str[MAX_ARRAY_SIZE];
    cout << "请输入乘客证件号(身份证取18位,护照取9位):" << endl;
    
    while (1)
    {
        cin.getline(str, MAX_ARRAY_SIZE);
        if(checkCancel(str)) return ERROR;
        if(searchPasByIdNum(pas_list, q, str))
        {
            cout << "该证件号已存在，请重新输入" << endl;
            continue;
        }
        if(type == 1)
        {
            if(!checkIdNum(str, 1))
            {
                cout << "输入的身份证证件号格式有误，请重新输入:" << endl;
                continue;
            }
        }
        if(type == 2)
        {
            if(!checkIdNum(str, 2))
            {
                cout << "输入的护照证件号格式有误，请重新输入:" << endl;
                continue;
            }
        }
        break;
    }
    strcpy(passenger->id_num, str);
    return OK;
}

Status getPasPhoneNum(PPASSENGER& passenger){
    //从屏幕获取输入内容并放入指针指向联系电话中
    if(!passenger) return ERROR;
    char str[MAX_ARRAY_SIZE];
    cout << "请输入乘客电话号码：" << endl;
    while (1)
    {
        cin.getline(str, MAX_ARRAY_SIZE);
        if(checkCancel(str)) return ERROR;
        if(!checkNumber(str) || strlen(str) > 11)
        {
            cout << "电话号码格式有误，请重新输入:" << endl;
            continue;
        }
        break;
    }
    strcpy(passenger->phone_num, str);
    return OK;
}

Status getPasEmerName(PPASSENGER& passenger){
    //从屏幕获取输入内容并放入指针指向的紧急联系人姓名中
    if(!passenger) return ERROR;
    char str[MAX_ARRAY_SIZE];
    cout << "请输入紧急联系人姓名：" << endl;
    cin.getline(str, MAX_ARRAY_SIZE);
    if(checkCancel(str)) return ERROR;
    strcpy(passenger->emer_name, str);
    return OK;
}

Status getPasEmerPhoneNum(PPASSENGER& passenger){
    //从屏幕获取输入内容并放入指针指向的紧急联系人联系电话中
    if(!passenger) return ERROR;
    char str[MAX_ARRAY_SIZE];
    cout << "请输入紧急联系人电话号码：" << endl;
    while (1)
    {
        cin.getline(str, MAX_ARRAY_SIZE);
        if(checkCancel(str)) return ERROR;
        if(!checkNumber(str) || strlen(str) > 11)
        {
            cout << "电话号码格式有误，请重新输入:" << endl;
            continue;
        }
        break;
    }
    strcpy(passenger->emer_phone_num, str);
    return OK;
}

Status insertPassenger(PPASSENGER& pas_list){
    //插入乘客主体函数
    if(!pas_list) return ERROR;
    PPASSENGER p = (PPASSENGER)malloc(sizeof(PASSENGER));
    if(
        !getPasName(p) ||
        !getPasIdType(p) ||
        !getPasIdNum(pas_list, p) ||
        !getPasPhoneNum(p) ||
        !getPasEmerName(p) ||
        !getPasEmerPhoneNum(p)
    )
    {
        cout << "插入失败" << endl;
        return ERROR;
    }
    if(!insertPasListByPtr(pas_list, p))
        return ERROR;
    return OK;
}