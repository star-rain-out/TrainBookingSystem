#include <iostream>
#include "Passenger.h"
#include "SearchPassenger.h"
#include "../Check.h"
using namespace std;

Status changePasByPhoneNum(PPASSENGER& passenger){
    //������ϵ�绰���ĳ˿���Ϣ
    if(!passenger) return ERROR;
    char str[MAX_ARRAY_SIZE];
    cout << "�������µĳ˿͵绰���룺" << endl;
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

Status changePasByEmerName(PPASSENGER& passenger){
    //���ݽ�����ϵ�˸��ĳ˿���Ϣ
    if(!passenger) return ERROR;
    char str[MAX_ARRAY_SIZE];
    cout << "�������µĽ�����ϵ��������" << endl;
    cin.getline(str, MAX_ARRAY_SIZE);
    if(checkCancel(str)) return ERROR;
    strcpy(passenger->emer_name, str);
    return OK;
}

Status changePasByEmerPhoneNum(PPASSENGER& passenger){
    ////���ݽ�����ϵ�˵绰���ĳ˿���Ϣ
    if(!passenger) return ERROR;
    char str[MAX_ARRAY_SIZE];
    cout << "�������µĽ�����ϵ�˵绰���룺" << endl;
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

Status changePassenger(PPASSENGER& pas_list){
    //�޸ĳ˿���Ϣ���庯��
    if(!pas_list) return ERROR;
    char str[MAX_ARRAY_SIZE];
    char c; //����޸ĵ�����
    PPASSENGER p;    //ָ����Ҫ�޸ĵĳ˿͵�ָ��
    cout << "��������Ҫ�޸ĵĳ˿�֤����" << endl;
    cin.getline(str, MAX_ARRAY_SIZE);
    if(!searchPasByIdNum(pas_list, p, str))
    {
        cout << "δ�ҵ��ó˿�" << endl;
        return ERROR;
    }
    cout << "��������Ҫ�޸ĵ�����(ֻ���������):" << endl;
    cout << "1.�޸���ϵ�绰" << endl
    << "2.�޸Ľ�����ϵ������" << endl
    << "3.�޸Ľ�����ϵ�˵绰" << endl;
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
    switch (c)
    {
    case '1':
        if(changePasByPhoneNum(p))
        {
            cout << "�޸ĳɹ�!" << endl;
            return OK;
        }
        break;
    case '2':
        if(changePasByEmerName(p))
        {
            cout << "�޸ĳɹ�!" << endl;
            return OK;
        }
        break;    
    case '3':
        if(changePasByEmerPhoneNum(p))
        {
            cout << "�޸ĳɹ�!" << endl;
            return OK;
        }
        break;
    default:
        break;
    }
    return ERROR;
}