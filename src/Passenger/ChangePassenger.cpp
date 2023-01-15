#include <iostream>
#include "Passenger.h"
#include "SearchPassenger.h"
#include "../Check.h"
using namespace std;

Status changePasByPhoneNum(PPASSENGER& passenger){
    //根据联系电话更改乘客信息
    if(!passenger) return ERROR;
    char str[MAX_ARRAY_SIZE];
    cout << "请输入新的乘客电话号码：" << endl;
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

Status changePasByEmerName(PPASSENGER& passenger){
    //根据紧急联系人更改乘客信息
    if(!passenger) return ERROR;
    char str[MAX_ARRAY_SIZE];
    cout << "请输入新的紧急联系人姓名：" << endl;
    cin.getline(str, MAX_ARRAY_SIZE);
    if(checkCancel(str)) return ERROR;
    strcpy(passenger->emer_name, str);
    return OK;
}

Status changePasByEmerPhoneNum(PPASSENGER& passenger){
    ////根据紧急联系人电话更改乘客信息
    if(!passenger) return ERROR;
    char str[MAX_ARRAY_SIZE];
    cout << "请输入新的紧急联系人电话号码：" << endl;
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

Status changePassenger(PPASSENGER& pas_list){
    //修改乘客信息主体函数
    if(!pas_list) return ERROR;
    char str[MAX_ARRAY_SIZE];
    char c; //存放修改的类型
    PPASSENGER p;    //指向需要修改的乘客的指针
    cout << "请输入需要修改的乘客证件号" << endl;
    cin.getline(str, MAX_ARRAY_SIZE);
    if(!searchPasByIdNum(pas_list, p, str))
    {
        cout << "未找到该乘客" << endl;
        return ERROR;
    }
    cout << "请输入需要修改的类型(只需输入序号):" << endl;
    cout << "1.修改联系电话" << endl
    << "2.修改紧急联系人姓名" << endl
    << "3.修改紧急联系人电话" << endl;
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
    switch (c)
    {
    case '1':
        if(changePasByPhoneNum(p))
        {
            cout << "修改成功!" << endl;
            return OK;
        }
        break;
    case '2':
        if(changePasByEmerName(p))
        {
            cout << "修改成功!" << endl;
            return OK;
        }
        break;    
    case '3':
        if(changePasByEmerPhoneNum(p))
        {
            cout << "修改成功!" << endl;
            return OK;
        }
        break;
    default:
        break;
    }
    return ERROR;
}