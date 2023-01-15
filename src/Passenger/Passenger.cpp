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
    //初始化存放乘客信息的链表头
    pas_list = (PPASSENGER)malloc(sizeof(PASSENGER));
    if(!pas_list) return ERROR;
    pas_list->next = NULL;
    return OK;
}

Status inputPasList(PPASSENGER& pas_list, char* filename){
    //从filename路径文件中读取乘客信息并插入乘客信息链表中
    if(!pas_list) return ERROR;
    ifstream inFile;
	inFile.open(filename);
    if (!inFile) {
	    cout << "无法打开文件";
	    exit(1); // 结束进程
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
    //将乘客信息链表中的数据输出至文件
    if(!pas_list) return ERROR;
    ofstream outFile;
	outFile.open(filename, ios::out);
    if (!outFile) {
	    cout << "无法打开文件";
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
    //格式化输出乘客信息
    PPASSENGER p = pas_list;
    p = p->next;
    cout << setiosflags(ios::left) << setw(20) << "证件号码" << "|" << setw(8) << "姓名" 
    << "|" << setw(8) << "证件类型" << "|" << setw(16) << "联系电话" << "|" << setw(16) 
    << "紧急联系人姓名" << "|" << setw(16) << "紧急联系人电话" << endl;
    //以上为表头
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
    //输出乘客信息表头
    cout << setiosflags(ios::left) << setw(20) << "证件号码" << "|" << setw(8) << "姓名" 
    << "|" << setw(8) << "证件类型" << "|" << setw(16) << "联系电话" << "|" << setw(16) 
    << "紧急联系人姓名" << "|" << setw(16) << "紧急联系人电话" << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
}

void displayPasByPtr(PPASSENGER passenger){
    //输出指针指向的乘客信息
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
    //释放乘客信息链表
    PPASSENGER p = pas_list;
    PPASSENGER q = pas_list;
    while (q)
    {
        p = q;
        q = q->next;
        free(p);
    }
     
}

