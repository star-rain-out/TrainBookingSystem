#pragma once
#include "Booking.h"
#include "../Train/Train.h"

//定义一个搜索树，采用左孩子右兄弟表示法
/*
搜索树共分为五层：
1层：日期
2层：车次
3层：座位等级
4层：座位号
5层：停靠站识别码
*/
typedef struct TNode
{
    char data[30];  //以字符串形式存放数据
    int level;      //存放节点层次
    struct TNode *parent, *firstchild, *nextsibling; //定义双亲、左孩子、右兄弟指针
}TNODE, *TREE;

typedef struct LeftTickets
{
    char train_name[5];        //存储高铁车次
    int length[3];         //记录各类座位类型顺序表长度，0为商务座，1为一等座，2为二等座
    int special_num, first_num, second_num; //记录各类座位类型剩余座位数
    int *special, *first, *second;          //采用顺序表记录各类座位剩余座位号
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