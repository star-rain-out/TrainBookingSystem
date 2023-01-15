#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "Passenger.h"
#include "SearchPassenger.h"
#include "../Check.h"
using namespace std;

Status insertPasListByPtr(PPASSENGER& pas_list, PPASSENGER& passenger){
    //��passengerָ��ָ������ݲ���˿���Ϣ������
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
    //����Ļ��ȡ�������ݲ�����ָ��ָ���������
    if(!passenger) return ERROR;
    char str[MAX_ARRAY_SIZE];
    cout << "������˿�������" << endl;
    cin.getline(str, MAX_ARRAY_SIZE);
    if(checkCancel(str)) return ERROR;
    strcpy(passenger->name, str);
    return OK;
}

Status getPasIdType(PPASSENGER& passenger){
    //����Ļ��ȡ�������ݲ�����ָ��ָ���֤��������
    if(!passenger) return ERROR;
    char str[8];
    int type = 0;
    
    cout << "������֤��������(1Ϊ���֤,2Ϊ����):" << endl;
    while (1)
    {
        cin.getline(str, MAX_ARRAY_SIZE);
        if(checkCancel(str)) return ERROR;
        type = atoi(str);
        if(type != 1 && type != 2)
        {
            cout << "�����ʽ����" << endl;
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
        cout << "֤�����Ͳ���ȷ��" << endl;
        return ERROR;
        break;
    }
    return OK;
}

Status getPasIdNum(PPASSENGER pas_list, PPASSENGER& passenger){
    //����Ļ��ȡ�������ݲ�����ָ��ָ���֤��������
    if(!passenger) return ERROR;
    int type = checkIdType(passenger->id_type); //��ȡ֤������
    PPASSENGER q; //����֤���ź����Ĳ���
    if(!type)
    {
        cout << "δ��ȡ��֤������" << endl;
        return ERROR;
    }
    char str[MAX_ARRAY_SIZE];
    cout << "������˿�֤����(���֤ȡ18λ,����ȡ9λ):" << endl;
    
    while (1)
    {
        cin.getline(str, MAX_ARRAY_SIZE);
        if(checkCancel(str)) return ERROR;
        if(searchPasByIdNum(pas_list, q, str))
        {
            cout << "��֤�����Ѵ��ڣ�����������" << endl;
            continue;
        }
        if(type == 1)
        {
            if(!checkIdNum(str, 1))
            {
                cout << "��������֤֤���Ÿ�ʽ��������������:" << endl;
                continue;
            }
        }
        if(type == 2)
        {
            if(!checkIdNum(str, 2))
            {
                cout << "����Ļ���֤���Ÿ�ʽ��������������:" << endl;
                continue;
            }
        }
        break;
    }
    strcpy(passenger->id_num, str);
    return OK;
}

Status getPasPhoneNum(PPASSENGER& passenger){
    //����Ļ��ȡ�������ݲ�����ָ��ָ����ϵ�绰��
    if(!passenger) return ERROR;
    char str[MAX_ARRAY_SIZE];
    cout << "������˿͵绰���룺" << endl;
    while (1)
    {
        cin.getline(str, MAX_ARRAY_SIZE);
        if(checkCancel(str)) return ERROR;
        if(!checkNumber(str) || strlen(str) > 11)
        {
            cout << "�绰�����ʽ��������������:" << endl;
            continue;
        }
        break;
    }
    strcpy(passenger->phone_num, str);
    return OK;
}

Status getPasEmerName(PPASSENGER& passenger){
    //����Ļ��ȡ�������ݲ�����ָ��ָ��Ľ�����ϵ��������
    if(!passenger) return ERROR;
    char str[MAX_ARRAY_SIZE];
    cout << "�����������ϵ��������" << endl;
    cin.getline(str, MAX_ARRAY_SIZE);
    if(checkCancel(str)) return ERROR;
    strcpy(passenger->emer_name, str);
    return OK;
}

Status getPasEmerPhoneNum(PPASSENGER& passenger){
    //����Ļ��ȡ�������ݲ�����ָ��ָ��Ľ�����ϵ����ϵ�绰��
    if(!passenger) return ERROR;
    char str[MAX_ARRAY_SIZE];
    cout << "�����������ϵ�˵绰���룺" << endl;
    while (1)
    {
        cin.getline(str, MAX_ARRAY_SIZE);
        if(checkCancel(str)) return ERROR;
        if(!checkNumber(str) || strlen(str) > 11)
        {
            cout << "�绰�����ʽ��������������:" << endl;
            continue;
        }
        break;
    }
    strcpy(passenger->emer_phone_num, str);
    return OK;
}

Status insertPassenger(PPASSENGER& pas_list){
    //����˿����庯��
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
        cout << "����ʧ��" << endl;
        return ERROR;
    }
    if(!insertPasListByPtr(pas_list, p))
        return ERROR;
    return OK;
}