#pragma once
#define PHONE_NUM_SIZE 12
#define ID_NUM_SIZE 19
#define NAME_SIZE 20
#define ID_TYPE_SIZE 13

#define MAX_ARRAY_SIZE 50
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define CANCEL 2

typedef int Status;


typedef struct Passenger
{
    char id_num[ID_NUM_SIZE]; //证件号
    char name[NAME_SIZE];      //姓名
    char id_type[ID_TYPE_SIZE];        //证件类型
    char phone_num[PHONE_NUM_SIZE]; //联系电话
    char emer_name[NAME_SIZE]; //紧急联系人姓名
    char emer_phone_num[PHONE_NUM_SIZE]; //紧急联系人电话
    struct Passenger* next;
}PASSENGER, *PPASSENGER;

Status initPasList(PPASSENGER&);
Status inputPasList(PPASSENGER&, char*);
Status outputPasList(PPASSENGER, char*);
void displayPasHeader();
void displayPasByPtr(PPASSENGER);
void displayPasList(PPASSENGER);
void freePasList(PPASSENGER&);