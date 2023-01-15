#include <iostream>
#include <stdlib.h>
#include "Passenger.h"
#include "SearchPassenger.h"

using namespace std;

Status deletePasByPtr(PPASSENGER& pas_list, PPASSENGER& passenger){
    //将passenger指针指向的内容从链表中删除
    if(!pas_list || !passenger) return ERROR;
    PPASSENGER p = pas_list;
    while (p->next != passenger)
    {
        p = p->next;
    }
    p->next = passenger->next;
    free(passenger);
    return OK;
}

Status deletePassenger(PPASSENGER& pas_list){
    //删除乘客的主体函数
    //删除乘客只能根据唯一的证件号来进行删除
    if(!pas_list) return ERROR;
    char str[MAX_ARRAY_SIZE];
    PPASSENGER p;
    cout << "请输入需要删除的乘客证件号：" << endl;
    cin.getline(str, MAX_ARRAY_SIZE);
    if(!searchPasByIdNum(pas_list, p, str))
    {
        cout << "未找到该乘客" << endl;
        return ERROR;
    }

    if(deletePasByPtr(pas_list, p))
    {
        cout << "删除成功!" << endl;
        return OK;
    }
    else return ERROR;
}