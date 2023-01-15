#include <iostream>
#include <string.h>
#include <iomanip>
#include "Booking.h"
#include "SearchBooking.h"
#include "../Train/Train.h"
#include "../Train/SearchTrain.h"
#include "../Check.h"
using namespace std;

const char linker[] = "-";

Status searchBookByName(PBOOKING book_list, PBOOKING& booking, char *name){
    //根据姓名查询订票信息
    if(!book_list) return ERROR;
    PBOOKING p = booking->next;
    while(p)
    {
        if(!strcmp(name, p->passenger_name))
        {
            break;
        }
        p = p->next;
    }
    if(!p)  return ERROR;
    booking = p;
    return OK;
}

Status searchBookByIdNum(PBOOKING book_list, PBOOKING& booking, char *id_num){
    //根据证件号订票信息
    if(!book_list) return ERROR;
    PBOOKING p = booking->next;
    while(p)
    {
        if(!strcmp(id_num, p->id_num))
        {
            break;
        }
        p = p->next;
    }
    if(!p)  return ERROR;
    booking = p;
    return OK;
}

Status searchBookByDate(PBOOKING book_list, PBOOKING& booking, char *date){
    //根据日期查询订票信息
    if(!book_list) return ERROR;
    PBOOKING p = booking->next;
    while(p)
    {
        if(!strcmp(date, p->date))
        {
            break;
        }
        p = p->next;
    }
    if(!p)  return ERROR;
    booking = p;
    return OK;
}

Status searchBookByTrainName(PBOOKING book_list, PBOOKING& booking, char *train_name){
    //根据车次查询订票信息
    if(!book_list) return ERROR;
    PBOOKING p = booking->next;
    while(p)
    {
        if(!strcmp(train_name, p->train_name))
        {
            break;
        }
        p = p->next;
    }
    if(!p)  return ERROR;
    booking = p;
    return OK;
}

Status searchBookByBookingNum(PBOOKING book_list, PBOOKING& booking, char *booking_num){
    //根据订单号查询订票信息
    if(!book_list) return ERROR;
    PBOOKING p = booking->next;
    while(p)
    {
        if(!strcmp(booking_num, p->booking_num))
        {
            break;
        }
        p = p->next;
    }
    if(!p)  return ERROR;
    booking = p;
    return OK;
}

Status searchBooking(PBOOKING book_list){
    /*
    根据选项查询订票信息
    1.根据姓名查询
    2.根据证件号查询
    3.根据乘车日期查询
    4.根据车次查询
    */
   if(!book_list) return ERROR;
    char c = ' '; //保存查找选项“1,2,3,4”
    char str[MAX_ARRAY_SIZE]; //保存查找内容
    int flag = 0; //标记是否找到
    PBOOKING p = book_list;
    cout << "请选择查找选项：" << endl
    << "1.根据姓名查询" << endl
    << "2.根据证件号查询" << endl
    << "3.根据乘车日期查询(输入格式为年月日:YYYYMMDD)" << endl
    << "4.根据车次查询" << endl;
    while (1)
    {
        cin.get(c);
        cin.ignore(MAX_ARRAY_SIZE, '\n');
        if(c != '1' && c != '2' && c != '3' && c != '4')
        {
            cout << "输入的选项有误，请重新输入" << endl;
            continue;
        }
        break;
    }
    cout << "请输入查找内容" << endl;
    cin.getline(str, MAX_ARRAY_SIZE);
    switch (c)
    {
    case '1':
        flag = searchBookByName(book_list, p, str);
        if(flag == OK)
        {
            displayBookHeader();
            displayBookByPtr(p);
            while (searchBookByName(book_list, p, str))
            {
                displayBookByPtr(p);
            }
        }
        break;
    case '2':
        flag = searchBookByIdNum(book_list, p, str);
        if(flag == OK)
        {
            displayBookHeader();
            displayBookByPtr(p);
            while (searchBookByIdNum(book_list, p, str))
            {
                displayBookByPtr(p);
            }
        }
        break;
    case '3':
        flag = searchBookByDate(book_list, p, str);
        if(flag == OK)
        {
            displayBookHeader();
            displayBookByPtr(p);
            while (searchBookByDate(book_list, p, str))
            {
                displayBookByPtr(p);
            }
        }
        break;
    case '4':
        flag = searchBookByTrainName(book_list, p, str);
        if(flag == OK)
        {
            displayBookHeader();
            displayBookByPtr(p);
            while (searchBookByTrainName(book_list, p, str))
            {
                displayBookByPtr(p);
            }
        }
        break;
    default:
        break;
    }
    if(flag == 0)
    {
        cout << "未查询到相关信息" << endl;
        return ERROR;
    }
    
    return OK;
}

Status checkTrainStopCode(const char* s1, const char* s2){
	//检查停靠站识别码是否有冲突，如果相同下标的两个字符同时为1，则返回ERROR
	int length = strlen(s1);
	for(int i = 0; i < length; i++){
		if(s1[i] == '1' && s2[i] == '1') return ERROR;
	}
	return OK;
}

char* mergeTrainStopCode(const char* s1, const char* s2){
    //合并停靠站识别码，将s2中等于'1'的字符复制到s1对应的下标位置中并返回
    int length = strlen(s1);
    char* str = (char*)malloc((length + 1) * sizeof(char));
    str[length] = '\0';
    strcpy(str, s1);
    for(int i = 0; i < length; i++){
		if(s2[i] == '1')
        {
            str[i] = '1';
        }
	}
    return str;
}

Status initTree(TREE& root){
    //初始化树根
    if(!(root = (TREE)malloc(sizeof(TNODE)))) return ERROR;
    root->level = 0;
    root->parent = NULL;
    root->firstchild = NULL;
    root->nextsibling = NULL;
    return OK;
}

void freeTree(TREE& pnode){
    //释放搜索树中所有节点
    if(!pnode)
    {
        freeTree(pnode->firstchild);
        freeTree(pnode->nextsibling);
        free(pnode);
    }
}

Status insertFirstChild(TREE& pnode, char* str){
    //将节点pnode插入第一个左孩子
    if(!pnode || pnode->firstchild) return ERROR;
    TREE p;
    if(!(p = (TREE)malloc(sizeof(TNode)))) return ERROR;
    strcpy(p->data, str);
    p->parent = pnode;
    p->level = pnode->level + 1;
    p->firstchild = NULL;
    p->nextsibling = NULL;
    pnode->firstchild = p;
    return OK;
}

Status insertNextSibling(TREE& pnode, char* str){
    //将节点pnode插入一个右兄弟
    if(!pnode || pnode->nextsibling) return ERROR;
    TREE p;
    if(!(p = (TREE)malloc(sizeof(TNode)))) return ERROR;
    strcpy(p->data, str);
    p->parent = pnode->parent;
    p->level = pnode->level;
    p->firstchild = NULL;
    p->nextsibling = NULL;
    pnode->nextsibling = p;
    return OK;
}

Status searchSibling(TREE& pnode, char* str){
    //寻找节点的下一个右兄弟，如果找到返回OK，并将pnode指向找到的节点
    //未找到返回ERROR，并将pnode指向最后一个右兄弟
    if(!pnode) return ERROR;
    TREE q = pnode;
    while(pnode)
    {
        if(!strcmp(pnode->data, str))
            break;
        q = pnode;
        pnode = pnode->nextsibling;
    }
    if(!pnode)
    {
        pnode = q;
        return ERROR;
    } 
    return OK;
}


Status insertTree(TREE& root, char* book_code){
    //根据订票识别码插入搜索树节点
    //将车票识别码用'-'拆开，按层级依次插入节点
    TREE p = root;
    char key[5][30];
    int i;
    strcpy(key[0], strtok(book_code, linker));
    for(i = 1; i < 5; i++)
    {
        strcpy(key[i], strtok(NULL, linker));
    }
    for(i = 0; i < 5; i++)
    {
        if(!p->firstchild)
        {
            insertFirstChild(p, key[i]);
            p = p->firstchild;
        }else{
            p = p->firstchild;
            if(p->level == 5)
            {
                strcpy(p->data, mergeTrainStopCode(p->data, key[i]));
                break;
            }
            if(!searchSibling(p, key[i]))
            {
                insertNextSibling(p, key[i]);
                p = p->nextsibling;
            }
        }
    }
    return OK;
}

void searchParentSibling(TREE& pnode){
    //寻找pnode的双亲节点的下一个兄弟节点，如果没有则再向上找，直到找到树根
    if(pnode->level == 0) return;
    if(!pnode->parent->nextsibling)
    {
        pnode = pnode->parent;
        searchParentSibling(pnode);
    }
    else
    {
        pnode = pnode->parent->nextsibling;
    }
}

void displayTNode(TREE pnode){
    //根据树节点层级来打印树节点
    if(!pnode->level)
    {
        cout << "root" << endl;
    }
    if(pnode->level == 1)
    {
        cout << setiosflags(ios::right) << setw(5) << "|---" << pnode->data << endl;
    }
    if(pnode->level == 2)
    {
        cout << setiosflags(ios::right) << setw(15) << "|---" << pnode->data << endl;
    }
    if(pnode->level == 3)
    {
        cout << setiosflags(ios::right) << setw(22) << "|---" << pnode->data << endl;
    }
    if(pnode->level == 4)
    {
        cout << setiosflags(ios::right) << setw(26) << "|---" << pnode->data << endl;
    }
    if(pnode->level == 5)
    {
        cout << setiosflags(ios::right) << setw(30) << "|---" << pnode->data << endl;
    }
}

void displayTree(TREE pnode){
    //向屏幕打印搜索树
    while(pnode){
        displayTNode(pnode);
        if(!pnode->firstchild)
            break;
        else pnode = pnode->firstchild;
    }
    if(pnode->nextsibling)
    {
        pnode = pnode->nextsibling;
        while (pnode)
        {
            displayTNode(pnode);
            if(!pnode->nextsibling)
                break;
            else pnode = pnode->nextsibling;
        }
    }
    
    searchParentSibling(pnode);
    if(pnode->level == 0)
        return;
    else displayTree(pnode);
}

Status searchTrainNameNode(TREE root, TREE& pnode, char* date, char* train_name){
    //根据日期和车次查找搜索树中节点，查找成功时pnode指向车次节点并返回OK，否则返回ERROR
    if(!root) return ERROR;
    TREE p;
    if(root->firstchild) p = root->firstchild;
    while(p)
    { 
        if(!strcmp(p->data, date))
            break;
        p = p->nextsibling;
    }
    if(!p) return ERROR;
    if(p->firstchild) p = p->firstchild;
    while(p)
    {
        if(!strcmp(p->data, train_name))
            break;
        p = p->nextsibling;
    }
    if(!p) return ERROR;
    pnode = p;
    return OK;
} 


char* getTrainStopCode(TrainList train_list, char* train_name, char* origin, char* destination){
    //获取停靠站识别码，起点站与终点站的前一站对应下标的字符设置为1，表示已经被占用，其他设置为0
    int length = (train_list.elem + getTrainIndex(train_list, train_name))->stop_num;
    char* code = (char*)malloc((length + 1) * sizeof(char));
    code[length] = '\0';
    int i = getStopIndex(train_list, train_name, origin);      //起点停靠站下标
    int j = getStopIndex(train_list, train_name, destination); //终点停靠站下标
    for(int k = 0; k < length; k++){
        code[k] = '0';     //整个字符串初始化为全0
    }
    for(; i < j; i++){
        code[i] = '1';      //将i与j-1之间的字符设置为1
    }
    return code;
}


char* getBookCode(PBOOKING booking, TRAINLIST train_list){
    //获取车票识别码，用来初始化搜索树
    //车票识别码组成部分：日期-车次-座位类别-座位号-停靠站识别码
    char linker[] = "-";
    char seat_num[3];
    char *code = (char*)malloc(MAX_ARRAY_SIZE * sizeof(char));
    code[0] = '\0';
    strcat(code, booking->date);
    strcat(code, linker);
    strcat(code, booking->train_name);
    strcat(code, linker);
    strcat(code, booking->seat_level);
    strcat(code, linker);
    strcat(code, itoa(booking->seat_num, seat_num, 10));
    strcat(code, linker);
    strcat(code, getTrainStopCode(train_list, booking->train_name, booking->origin, booking->destination));
    return code;
}

LEFTTICKETS createLeftTickets(TRAINLIST train_list, char* train_name){
    //根据车次初始化剩余车票结构体
    LEFTTICKETS left_tikets;
    strcpy(left_tikets.train_name, train_name);
    int index = getTrainIndex(train_list, train_name);
    left_tikets.length[0] = left_tikets.special_num = train_list.elem[index].special_class;
    left_tikets.length[1] = left_tikets.first_num = train_list.elem[index].first_class;
    left_tikets.length[2] = left_tikets.second_num = train_list.elem[index].second_class;
    left_tikets.special = (int*)malloc(left_tikets.special_num * sizeof(int));
    left_tikets.first = (int*)malloc(left_tikets.first_num * sizeof(int));
    left_tikets.second = (int*)malloc(left_tikets.second_num * sizeof(int));
    int i;
    for(i = 0; i < left_tikets.special_num; i++){
        left_tikets.special[i] = i + 1;
    }
    for(i = 0; i < left_tikets.first_num; i++){
        left_tikets.first[i] = i + 1;
    }
    for(i = 0; i < left_tikets.second_num; i++){
        left_tikets.second[i] = i + 1;
    }
    return left_tikets;
}

void createLeftTickets1(LEFTTICKETS*& left_tickets, TRAINLIST train_list, char* train_name){
    //接收一个剩余车票结构体指针，根据车次初始化剩余车票结构体
    strcpy(left_tickets->train_name, train_name);
    int index = getTrainIndex(train_list, train_name);
    left_tickets->length[0] = left_tickets->special_num = train_list.elem[index].special_class;
    left_tickets->length[1] = left_tickets->first_num = train_list.elem[index].first_class;
    left_tickets->length[2] = left_tickets->second_num = train_list.elem[index].second_class;
    left_tickets->special = (int*)malloc(left_tickets->special_num * sizeof(int));
    left_tickets->first = (int*)malloc(left_tickets->first_num * sizeof(int));
    left_tickets->second = (int*)malloc(left_tickets->second_num * sizeof(int));
    int i;
    for(i = 0; i < left_tickets->special_num; i++){
        left_tickets->special[i] = i + 1;
    }
    for(i = 0; i < left_tickets->first_num; i++){
        left_tickets->first[i] = i + 1;
    }
    for(i = 0; i < left_tickets->second_num; i++){
        left_tickets->second[i] = i + 1;
    }
    
}

LEFTTICKETS setLeftTickets(TREE root, TRAINLIST train_list, char* date, char* train_name, char* stop_code){
    //根据日期、车次、停靠站识别码来构造一个剩余车票结构体，将停靠站识别码冲突的座位号从结构体中删去（置0）
    LEFTTICKETS left_tickets = createLeftTickets(train_list, train_name);
    TREE p;
    //通过日期和车次查找对应的节点，找不到直接返回
    if(!searchTrainNameNode(root, p, date, train_name)) return left_tickets;
    char special[] = "商务座";
    char first[] = "一等座";
    char second[] = "二等座";
    p = p->firstchild;
    while (p->level != 2)
    {
        while(p->level != 5)
        {
            if(p) p = p->firstchild;
        }
        if(!checkTrainStopCode(p->data, stop_code))
        {
            //停靠站识别码对应的商务座
            if(!strcmp(p->parent->parent->data, special))
            {
                int seat = atoi(p->parent->data);
                left_tickets.special_num--;
                left_tickets.special[seat - 1] = 0;
            }
            //停靠站识别码对应的一等座
            if(!strcmp(p->parent->parent->data, first))
            {
                int seat = atoi(p->parent->data);
                left_tickets.first_num--;
                left_tickets.first[seat - 1] = 0;
            }
            //停靠站识别码对应的二等座
            if(!strcmp(p->parent->parent->data, second))
            {
                int seat = atoi(p->parent->data);
                left_tickets.second_num--;
                left_tickets.second[seat - 1] = 0;
            }
        }
        p = p->parent;
        if(!p->nextsibling)
        {
            p = p->parent;
            if(!p->nextsibling)
            {
                break;
            } else {
                p = p->nextsibling;
            }
        } else {
            p = p->nextsibling;
        }
    }
    return left_tickets;
}

void setLeftTickets1(LEFTTICKETS*& left_tickets, TREE root, TRAINLIST train_list, char* date, char* train_name, char* stop_code){
    //根据日期、车次、停靠站识别码改变指向剩余车票结构体指针中的内容，将停靠站识别码冲突的座位号从结构体中删去（置0）
    createLeftTickets1(left_tickets, train_list, train_name);
    TREE p;
    //通过日期和车次查找对应的节点，找不到直接返回
    if(!searchTrainNameNode(root, p, date, train_name)) return;
    char special[] = "商务座";
    char first[] = "一等座";
    char second[] = "二等座";
    p = p->firstchild;
    while (p->level != 2)
    {
        while(p->level != 5)
        {
            if(p) p = p->firstchild;
        }
        if(!checkTrainStopCode(p->data, stop_code))
        {
            //停靠站识别码对应的商务座
            if(!strcmp(p->parent->parent->data, special))
            {
                int seat = atoi(p->parent->data);
                left_tickets->special_num--;
                left_tickets->special[seat - 1] = 0;
            }
            //停靠站识别码对应的一等座
            if(!strcmp(p->parent->parent->data, first))
            {
                int seat = atoi(p->parent->data);
                left_tickets->first_num--;
                left_tickets->first[seat - 1] = 0;
            }
            //停靠站识别码对应的二等座
            if(!strcmp(p->parent->parent->data, second))
            {
                int seat = atoi(p->parent->data);
                left_tickets->second_num--;
                left_tickets->second[seat - 1] = 0;
            }
        }
        p = p->parent;
        if(!p->nextsibling)
        {
            p = p->parent;
            if(!p->nextsibling)
            {
                break;
            } else {
                p = p->nextsibling;
            }
        } else {
            p = p->nextsibling;
        }
    }
    return;
}

void displayLeftTickets(LEFTTICKETS left_tickets){
    //接收一个剩余车票结构体，并以特定格式输出
    int i;
    cout << "高铁" << left_tickets.train_name << "剩余票数信息:" << endl;
    cout << "商务座剩余" << left_tickets.special_num << "个，座位号为:" << endl;
    for(i = 0; i < left_tickets.length[0]; i++)
    {
        if(left_tickets.special[i] != 0)
            cout << left_tickets.special[i] << " ";
    }
    cout << endl;
    cout << "一等座剩余" << left_tickets.first_num << "个，座位号为:" << endl;
    for(i = 0; i < left_tickets.length[1]; i++)
    {
        if(left_tickets.first[i] != 0)
            cout << left_tickets.first[i] << " ";
    }
    cout << endl;
    cout << "二等座剩余" << left_tickets.second_num << "个，座位号为:" << endl;
    for(i = 0; i < left_tickets.length[2]; i++)
    {
        if(left_tickets.second[i] != 0)
            cout << left_tickets.second[i] << " ";
    }
    cout << endl;
}

Status searchLeftTickets(){
    char filename[] = "..\\data\\booking.txt";
    char filename2[] = "..\\data\\train.txt";
    PBOOKING book_list;   //定义订票链表头
    TRAINLIST train_list;  //定义高铁顺序表
    initBookList(book_list); //初始化订票链表
    inputBookList(book_list, filename);  //从文件读入订票信息
    inputTrainList(train_list, filename2); //从文件读入高铁信息
    TREE root;     //定义树根
    initTree(root);  //初始化搜索树
    PBOOKING booking = book_list->next;
    while(booking)  //将所有订票信息插入搜索树
    {
        insertTree(root, getBookCode(booking, train_list));
        booking = booking->next;
    }
    //以上代码为初始化代码
    //displayTree(root);
    char date[MAX_ARRAY_SIZE], origin[MAX_ARRAY_SIZE], destination[MAX_ARRAY_SIZE]; //定义日期，起点站，终点站字符串
    cout << "请输入需要查询的日期,日期从今日" << getDateStr(getSysTime()) << "至" << getDateStr(getDateTwoMonLater()) << endl;
    cin.getline(date, MAX_ARRAY_SIZE);
    if(checkDateByStr(date) && checkDateByOrder(getSysTime(), getDateByStr(date))
        && checkDateByOrder(getDateByStr(date), getDateTwoMonLater()))
    {
        cout << "请输入起点站:" << endl;
        cin.getline(origin, MAX_ARRAY_SIZE);
        cout << "请输入终点站:" << endl;
        cin.getline(destination, MAX_ARRAY_SIZE);
        int* train_index;
        if(searchTrainByOtoD(train_list, origin, destination, train_index))
        {
            for(int i = 0; train_index[i] != -1; i++){
                LEFTTICKETS left_tickets = setLeftTickets(root, train_list, date, 
                train_list.train_value.name[train_index[i]], 
                getTrainStopCode(train_list, train_list.train_value.name[train_index[i]], origin, destination));
                displayLeftTickets(left_tickets);
                //cout << train_index[i] << endl;
            }
        }
        else
        {
            cout << "没有符合条件的车次" << endl;
        }
    }
    else
    {
        cout << "该日期不存在!" << endl;
    }
    
    freeTree(root);   //查询函数结束后释放搜索树
    freeBookList(book_list);  //释放订票列表
    deleteTrainList(train_list);  //释放高铁顺序表
    return OK;
}