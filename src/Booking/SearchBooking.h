#pragma once
#include "Booking.h"
#include "../Train/Train.h"

//����һ���������������������ֵܱ�ʾ��
/*
����������Ϊ��㣺
1�㣺����
2�㣺����
3�㣺��λ�ȼ�
4�㣺��λ��
5�㣺ͣ��վʶ����
*/
typedef struct TNode
{
    char data[30];  //���ַ�����ʽ�������
    int level;      //��Žڵ���
    struct TNode *parent, *firstchild, *nextsibling; //����˫�ס����ӡ����ֵ�ָ��
}TNODE, *TREE;

typedef struct LeftTickets
{
    char train_name[5];        //�洢��������
    int length[3];         //��¼������λ����˳����ȣ�0Ϊ��������1Ϊһ������2Ϊ������
    int special_num, first_num, second_num; //��¼������λ����ʣ����λ��
    int *special, *first, *second;          //����˳����¼������λʣ����λ��
}LEFTTICKETS;

Status searchBooking(PBOOKING book_list);

Status checkTrainStopCode(const char* s1, const char* s2);
char* mergeTrainStopCode(const char* s1, const char* s2);
Status initTree(TREE& root);
void freeTree(TREE& pnode);
Status insertTree(TREE& root, char* book_code);
void displayTree(TREE pnode);

char* getTrainStopCode(TrainList train_list, char* train_name, char* origin, char* destination);
char* getBookCode(PBOOKING booking, TRAINLIST train_list);
Status searchLeftTickets();
void displayLeftTickets(LEFTTICKETS left_tickets);
LEFTTICKETS setLeftTickets(TREE root, TRAINLIST train_list, char* date, char* train_name, char* stop_code);
void setLeftTickets1(LEFTTICKETS*& left_tickets,TREE root, TRAINLIST train_list, char* date, char* train_name, char* stop_code);