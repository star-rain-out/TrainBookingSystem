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
    //����������ѯ��Ʊ��Ϣ
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
    //����֤���Ŷ�Ʊ��Ϣ
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
    //�������ڲ�ѯ��Ʊ��Ϣ
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
    //���ݳ��β�ѯ��Ʊ��Ϣ
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
    //���ݶ����Ų�ѯ��Ʊ��Ϣ
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
    ����ѡ���ѯ��Ʊ��Ϣ
    1.����������ѯ
    2.����֤���Ų�ѯ
    3.���ݳ˳����ڲ�ѯ
    4.���ݳ��β�ѯ
    */
   if(!book_list) return ERROR;
    char c = ' '; //�������ѡ�1,2,3,4��
    char str[MAX_ARRAY_SIZE]; //�����������
    int flag = 0; //����Ƿ��ҵ�
    PBOOKING p = book_list;
    cout << "��ѡ�����ѡ�" << endl
    << "1.����������ѯ" << endl
    << "2.����֤���Ų�ѯ" << endl
    << "3.���ݳ˳����ڲ�ѯ(�����ʽΪ������:YYYYMMDD)" << endl
    << "4.���ݳ��β�ѯ" << endl;
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
        cout << "δ��ѯ�������Ϣ" << endl;
        return ERROR;
    }
    
    return OK;
}

Status checkTrainStopCode(const char* s1, const char* s2){
	//���ͣ��վʶ�����Ƿ��г�ͻ�������ͬ�±�������ַ�ͬʱΪ1���򷵻�ERROR
	int length = strlen(s1);
	for(int i = 0; i < length; i++){
		if(s1[i] == '1' && s2[i] == '1') return ERROR;
	}
	return OK;
}

char* mergeTrainStopCode(const char* s1, const char* s2){
    //�ϲ�ͣ��վʶ���룬��s2�е���'1'���ַ����Ƶ�s1��Ӧ���±�λ���в�����
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
    //��ʼ������
    if(!(root = (TREE)malloc(sizeof(TNODE)))) return ERROR;
    root->level = 0;
    root->parent = NULL;
    root->firstchild = NULL;
    root->nextsibling = NULL;
    return OK;
}

void freeTree(TREE& pnode){
    //�ͷ������������нڵ�
    if(!pnode)
    {
        freeTree(pnode->firstchild);
        freeTree(pnode->nextsibling);
        free(pnode);
    }
}

Status insertFirstChild(TREE& pnode, char* str){
    //���ڵ�pnode�����һ������
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
    //���ڵ�pnode����һ�����ֵ�
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
    //Ѱ�ҽڵ����һ�����ֵܣ�����ҵ�����OK������pnodeָ���ҵ��Ľڵ�
    //δ�ҵ�����ERROR������pnodeָ�����һ�����ֵ�
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
    //���ݶ�Ʊʶ��������������ڵ�
    //����Ʊʶ������'-'�𿪣����㼶���β���ڵ�
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
    //Ѱ��pnode��˫�׽ڵ����һ���ֵܽڵ㣬���û�����������ң�ֱ���ҵ�����
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
    //�������ڵ�㼶����ӡ���ڵ�
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
    //����Ļ��ӡ������
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
    //�������ںͳ��β����������нڵ㣬���ҳɹ�ʱpnodeָ�򳵴νڵ㲢����OK�����򷵻�ERROR
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
    //��ȡͣ��վʶ���룬���վ���յ�վ��ǰһվ��Ӧ�±���ַ�����Ϊ1����ʾ�Ѿ���ռ�ã���������Ϊ0
    int length = (train_list.elem + getTrainIndex(train_list, train_name))->stop_num;
    char* code = (char*)malloc((length + 1) * sizeof(char));
    code[length] = '\0';
    int i = getStopIndex(train_list, train_name, origin);      //���ͣ��վ�±�
    int j = getStopIndex(train_list, train_name, destination); //�յ�ͣ��վ�±�
    for(int k = 0; k < length; k++){
        code[k] = '0';     //�����ַ�����ʼ��Ϊȫ0
    }
    for(; i < j; i++){
        code[i] = '1';      //��i��j-1֮����ַ�����Ϊ1
    }
    return code;
}


char* getBookCode(PBOOKING booking, TRAINLIST train_list){
    //��ȡ��Ʊʶ���룬������ʼ��������
    //��Ʊʶ������ɲ��֣�����-����-��λ���-��λ��-ͣ��վʶ����
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
    //���ݳ��γ�ʼ��ʣ�೵Ʊ�ṹ��
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
    //����һ��ʣ�೵Ʊ�ṹ��ָ�룬���ݳ��γ�ʼ��ʣ�೵Ʊ�ṹ��
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
    //�������ڡ����Ρ�ͣ��վʶ����������һ��ʣ�೵Ʊ�ṹ�壬��ͣ��վʶ�����ͻ����λ�Ŵӽṹ����ɾȥ����0��
    LEFTTICKETS left_tickets = createLeftTickets(train_list, train_name);
    TREE p;
    //ͨ�����ںͳ��β��Ҷ�Ӧ�Ľڵ㣬�Ҳ���ֱ�ӷ���
    if(!searchTrainNameNode(root, p, date, train_name)) return left_tickets;
    char special[] = "������";
    char first[] = "һ����";
    char second[] = "������";
    p = p->firstchild;
    while (p->level != 2)
    {
        while(p->level != 5)
        {
            if(p) p = p->firstchild;
        }
        if(!checkTrainStopCode(p->data, stop_code))
        {
            //ͣ��վʶ�����Ӧ��������
            if(!strcmp(p->parent->parent->data, special))
            {
                int seat = atoi(p->parent->data);
                left_tickets.special_num--;
                left_tickets.special[seat - 1] = 0;
            }
            //ͣ��վʶ�����Ӧ��һ����
            if(!strcmp(p->parent->parent->data, first))
            {
                int seat = atoi(p->parent->data);
                left_tickets.first_num--;
                left_tickets.first[seat - 1] = 0;
            }
            //ͣ��վʶ�����Ӧ�Ķ�����
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
    //�������ڡ����Ρ�ͣ��վʶ����ı�ָ��ʣ�೵Ʊ�ṹ��ָ���е����ݣ���ͣ��վʶ�����ͻ����λ�Ŵӽṹ����ɾȥ����0��
    createLeftTickets1(left_tickets, train_list, train_name);
    TREE p;
    //ͨ�����ںͳ��β��Ҷ�Ӧ�Ľڵ㣬�Ҳ���ֱ�ӷ���
    if(!searchTrainNameNode(root, p, date, train_name)) return;
    char special[] = "������";
    char first[] = "һ����";
    char second[] = "������";
    p = p->firstchild;
    while (p->level != 2)
    {
        while(p->level != 5)
        {
            if(p) p = p->firstchild;
        }
        if(!checkTrainStopCode(p->data, stop_code))
        {
            //ͣ��վʶ�����Ӧ��������
            if(!strcmp(p->parent->parent->data, special))
            {
                int seat = atoi(p->parent->data);
                left_tickets->special_num--;
                left_tickets->special[seat - 1] = 0;
            }
            //ͣ��վʶ�����Ӧ��һ����
            if(!strcmp(p->parent->parent->data, first))
            {
                int seat = atoi(p->parent->data);
                left_tickets->first_num--;
                left_tickets->first[seat - 1] = 0;
            }
            //ͣ��վʶ�����Ӧ�Ķ�����
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
    //����һ��ʣ�೵Ʊ�ṹ�壬�����ض���ʽ���
    int i;
    cout << "����" << left_tickets.train_name << "ʣ��Ʊ����Ϣ:" << endl;
    cout << "������ʣ��" << left_tickets.special_num << "������λ��Ϊ:" << endl;
    for(i = 0; i < left_tickets.length[0]; i++)
    {
        if(left_tickets.special[i] != 0)
            cout << left_tickets.special[i] << " ";
    }
    cout << endl;
    cout << "һ����ʣ��" << left_tickets.first_num << "������λ��Ϊ:" << endl;
    for(i = 0; i < left_tickets.length[1]; i++)
    {
        if(left_tickets.first[i] != 0)
            cout << left_tickets.first[i] << " ";
    }
    cout << endl;
    cout << "������ʣ��" << left_tickets.second_num << "������λ��Ϊ:" << endl;
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
    PBOOKING book_list;   //���嶩Ʊ����ͷ
    TRAINLIST train_list;  //�������˳���
    initBookList(book_list); //��ʼ����Ʊ����
    inputBookList(book_list, filename);  //���ļ����붩Ʊ��Ϣ
    inputTrainList(train_list, filename2); //���ļ����������Ϣ
    TREE root;     //��������
    initTree(root);  //��ʼ��������
    PBOOKING booking = book_list->next;
    while(booking)  //�����ж�Ʊ��Ϣ����������
    {
        insertTree(root, getBookCode(booking, train_list));
        booking = booking->next;
    }
    //���ϴ���Ϊ��ʼ������
    //displayTree(root);
    char date[MAX_ARRAY_SIZE], origin[MAX_ARRAY_SIZE], destination[MAX_ARRAY_SIZE]; //�������ڣ����վ���յ�վ�ַ���
    cout << "��������Ҫ��ѯ������,���ڴӽ���" << getDateStr(getSysTime()) << "��" << getDateStr(getDateTwoMonLater()) << endl;
    cin.getline(date, MAX_ARRAY_SIZE);
    if(checkDateByStr(date) && checkDateByOrder(getSysTime(), getDateByStr(date))
        && checkDateByOrder(getDateByStr(date), getDateTwoMonLater()))
    {
        cout << "���������վ:" << endl;
        cin.getline(origin, MAX_ARRAY_SIZE);
        cout << "�������յ�վ:" << endl;
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
            cout << "û�з��������ĳ���" << endl;
        }
    }
    else
    {
        cout << "�����ڲ�����!" << endl;
    }
    
    freeTree(root);   //��ѯ�����������ͷ�������
    freeBookList(book_list);  //�ͷŶ�Ʊ�б�
    deleteTrainList(train_list);  //�ͷŸ���˳���
    return OK;
}