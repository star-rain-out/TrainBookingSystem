#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#include "Passenger.h"
#include "InsertPassenger.h"
#include "SearchPassenger.h"
#include "DeletePassenger.h"
#include "ChangePassenger.h"
#define MAX_ARRAY_SIZE 50

using namespace std;

Status initPasList(PPASSENGER& pas_list){
    //��ʼ����ų˿���Ϣ������ͷ
    pas_list = (PPASSENGER)malloc(sizeof(PASSENGER));
    if(!pas_list) return ERROR;
    pas_list->next = NULL;
    return OK;
}

Status inputPasList(PPASSENGER& pas_list, char* filename){
    //��filename·���ļ��ж�ȡ�˿���Ϣ������˿���Ϣ������
    if(!pas_list) return ERROR;
    ifstream inFile;
	inFile.open(filename);
    if (!inFile) {
	    cout << "�޷����ļ�";
	    exit(1); // ��������
	}
    PPASSENGER q = pas_list;
    
    PPASSENGER p = (PPASSENGER)malloc(sizeof(PASSENGER));
    while (inFile >> p->id_num >> p->name >> p->id_type >> p->phone_num >> p->emer_name >> p->emer_phone_num)
    {
        insertPasListByPtr(pas_list, p);
    }
    
    inFile.close();
    return OK;
}

Status outputPasList(PPASSENGER pas_list, char* filename){
    //���˿���Ϣ�����е�����������ļ�
    if(!pas_list) return ERROR;
    ofstream outFile;
	outFile.open(filename, ios::out);
    if (!outFile) {
	    cout << "�޷����ļ�";
	    exit(1); 
	}
    PPASSENGER p = pas_list;
    p = p->next;    
    while (p)
    {
        outFile << p->id_num << " "
        << p->name << " "
        << p->id_type << " "
        << p->phone_num << " "
        << p->emer_name << " "
        << p->emer_phone_num << endl;
        p = p->next;
    }
    
    outFile.close();
    return OK;
}

void displayPasList(PPASSENGER pas_list){
    //��ʽ������˿���Ϣ
    PPASSENGER p = pas_list;
    p = p->next;
    cout << setiosflags(ios::left) << setw(20) << "֤������" << "|" << setw(8) << "����" 
    << "|" << setw(8) << "֤������" << "|" << setw(16) << "��ϵ�绰" << "|" << setw(16) 
    << "������ϵ������" << "|" << setw(16) << "������ϵ�˵绰" << endl;
    //����Ϊ��ͷ
    cout << "--------------------------------------------------------------------------------------" << endl;
    while (p)
    {
        cout << setiosflags(ios::left) << setw(20) << p->id_num << "|";
        cout << setiosflags(ios::left) << setw(8) << p->name << "|";
        cout << setiosflags(ios::left) << setw(8) << p->id_type << "|";
        cout << setiosflags(ios::left) << setw(16) << p->phone_num << "|";
        cout << setiosflags(ios::left) << setw(16) << p->emer_name << "|";
        cout << setiosflags(ios::left) << setw(16) << p->emer_phone_num << endl;
        p = p->next;
    }
    cout << "--------------------------------------------------------------------------------------" << endl;
}

void displayPasHeader(){
    //����˿���Ϣ��ͷ
    cout << setiosflags(ios::left) << setw(20) << "֤������" << "|" << setw(8) << "����" 
    << "|" << setw(8) << "֤������" << "|" << setw(16) << "��ϵ�绰" << "|" << setw(16) 
    << "������ϵ������" << "|" << setw(16) << "������ϵ�˵绰" << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
}

void displayPasByPtr(PPASSENGER passenger){
    //���ָ��ָ��ĳ˿���Ϣ
    PPASSENGER p = passenger;
    cout << setiosflags(ios::left) << setw(20) << p->id_num << "|";
    cout << setiosflags(ios::left) << setw(8) << p->name << "|";
    cout << setiosflags(ios::left) << setw(8) << p->id_type << "|";
    cout << setiosflags(ios::left) << setw(16) << p->phone_num << "|";
    cout << setiosflags(ios::left) << setw(16) << p->emer_name << "|";
    cout << setiosflags(ios::left) << setw(16) << p->emer_phone_num << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
}

void freePasList(PPASSENGER& pas_list){
    //�ͷų˿���Ϣ����
    PPASSENGER p = pas_list;
    PPASSENGER q = pas_list;
    while (q)
    {
        p = q;
        q = q->next;
        free(p);
    }
     
}

