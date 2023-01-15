#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "Passenger.h"
using namespace std;

Status searchPasByName(PPASSENGER pas_list, PPASSENGER& passenger, char* name){
    //����������ѯ�˿Ͳ���passengerָ��ָ���Ӧλ��
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
    //����֤���Ų�ѯ�˿Ͳ���passengerָ��ָ���Ӧλ��
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
    //������ϵ�绰��ѯ�˿Ͳ���passengerָ��ָ���Ӧλ��
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
    //���ݽ�����ϵ��������ѯ�˿Ͳ���passengerָ��ָ���Ӧλ��
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
    ����ѡ���ѯ�˿���Ϣ
    1.����������ѯ
    2.����֤���Ų�ѯ
    3.������ϵ�绰��ѯ
    4.���ݽ�����ϵ��������ѯ
    */
    if(!pas_list) return ERROR;
    char c = ' '; //�������ѡ�1,2,3,4��
    char str[MAX_ARRAY_SIZE]; //�����������
    int flag = 0; //����Ƿ��ҵ�
    PPASSENGER p = pas_list;
    cout << "��ѡ�����ѡ�" << endl
    << "1.����������ѯ" << endl
    << "2.����֤���Ų�ѯ" << endl
    << "3.������ϵ�绰��ѯ" << endl
    << "4.���ݽ�����ϵ��������ѯ" << endl;
    while (1)
    {
        cin.get(c);
        cin.ignore(MAX_ARRAY_SIZE, '\n');
        if(c != '1' && c != '2' && c != '3' && c != '4')
        {
            cout << "�����ѡ����������������" << endl;
            continue;
        }
        break;
    }
    cout << "�������������" << endl;
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
        cout << "δ��ѯ�������Ϣ" << endl;
        return ERROR;
    }
    
    return OK;
}