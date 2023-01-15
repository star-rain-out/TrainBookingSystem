#include <iostream>
#include <stdlib.h>
#include "Passenger.h"
#include "SearchPassenger.h"

using namespace std;

Status deletePasByPtr(PPASSENGER& pas_list, PPASSENGER& passenger){
    //��passengerָ��ָ������ݴ�������ɾ��
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
    //ɾ���˿͵����庯��
    //ɾ���˿�ֻ�ܸ���Ψһ��֤����������ɾ��
    if(!pas_list) return ERROR;
    char str[MAX_ARRAY_SIZE];
    PPASSENGER p;
    cout << "��������Ҫɾ���ĳ˿�֤���ţ�" << endl;
    cin.getline(str, MAX_ARRAY_SIZE);
    if(!searchPasByIdNum(pas_list, p, str))
    {
        cout << "δ�ҵ��ó˿�" << endl;
        return ERROR;
    }

    if(deletePasByPtr(pas_list, p))
    {
        cout << "ɾ���ɹ�!" << endl;
        return OK;
    }
    else return ERROR;
}