#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Booking.h"
#include "SearchBooking.h"
#include "../Train/Train.h"
#include "../Train/SearchTrain.h"
#include "../Check.h"
#include "../Passenger/Passenger.h"
#include "../Passenger/SearchPassenger.h"
using namespace std;

Status compareBookingNum(PBOOKING booking1, PBOOKING booking2){
    //比较booking1与booking2指针指向的订单编号顺序，booking2大于booking1则返回OK
    //比较规则：先比日期，再比车次大小，最后比序号大小
    if(!booking2) return ERROR;
    if(!booking1) return OK;
    const char* linker = "-";
    char booking_num1[18], booking_num2[18];
    strcpy(booking_num1, booking1->booking_num);
    strcpy(booking_num2, booking2->booking_num);
    char key1[3][9], key2[3][9];
    int i;
    strcpy(key1[0], strtok(booking_num1, linker));
    for(i = 1; i < 3; i++)
    {
        strcpy(key1[i], strtok(NULL, linker));
    }
    strcpy(key2[0], strtok(booking_num2, linker));
    for(i = 1; i < 3; i++)
    {
        strcpy(key2[i], strtok(NULL, linker));
    }
    if(!strcmp(key1[0], key2[0]))
    {
        //如果日期相等，则比较车次
        if(!strcmp(key1[1], key2[1]))
        {
            //如果车次相等，则比较序号
            int num1 = atoi(key1[2]);
            int num2 = atoi(key2[2]);
            if(num2 > num1) return OK;
            else return ERROR;
        }
        else
        {
            int num1 = atoi(key1[1]);
            int num2 = atoi(key2[1]);
            if(num2 > num1) return OK;
            else return ERROR;
        }
    }
    else
    {
        if(checkDateByOrder(getDateByStr(key1[0]), getDateByStr(key2[0])))
        {            
            return OK;
        }
            
        else return ERROR;
    }
}

Status insertBookListTail(PBOOKING& book_list, PBOOKING& booking){
    //将从文件读取完一行信息的指针booking插入到单链表尾部
    if(!booking) return ERROR;
    PBOOKING p = book_list;
    if(p->next) p = p->next;
    PBOOKING pre_p = book_list;
    PBOOKING q = (PBOOKING)malloc(sizeof(BOOKING));
    q->next = NULL;
   
    strcpy(q->booking_num, booking->booking_num);
    strcpy(q->date, booking->date);
    strcpy(q->train_name, booking->train_name);
    strcpy(q->origin, booking->origin);
    strcpy(q->destination, booking->destination);
    strcpy(q->id_type, booking->id_type);
    strcpy(q->id_num, booking->id_num);
    strcpy(q->passenger_name, booking->passenger_name);
    strcpy(q->departure_time, booking->departure_time);
    strcpy(q->arrival_time, booking->arrival_time);
    strcpy(q->seat_level, booking->seat_level);
    q->seat_num = booking->seat_num;
    q->price = booking->price;

    if(p == book_list)
    {
        p->next = q;
        return OK;
    }
    while(1)
    {
        if(compareBookingNum(pre_p, q) && compareBookingNum(q, p))
        {
            pre_p->next = q;
            q->next = p;
            break;
        }
        else
        {
            if(p->next)
            {
                pre_p = p;
                p = p->next;
            }
            else
            {
                p->next = q;
                break;
            }
            
        }
    }
    
    return OK;
}

char* getBookingNum(PBOOKING book_list, const char* date, const char* train_name){
    //根据日期和车次在book_list中按顺序查找，生成一个新订单号并返回
    //如果找不到日期，或者找到日期找不到车次，直接返回日期-车次-001
    //如果找到了对应的日期和车次，则寻找对应序号的最大值
    if(!book_list) exit(1);
    const char* linker = "-";
    char* result = (char*)malloc(20 * sizeof(char)); //返回结果的字符串，在堆上申请
    PBOOKING booking = book_list->next;
    char zero[5] = "0000";
    //在堆上申请一个存放车次的数组，初始化为0000
    char* train_name_str = (char*)malloc(5 * sizeof(char));
    strcpy(train_name_str, zero);
    char str[5];
    strcpy(str, train_name);
    //将车次赋值给train_name_str,并去掉G
    for(int i = strlen(str) - 1, j = 3; str[i] != 'G'; i--){
        train_name_str[j] = str[i];
        j--;
    }
    char key[3][9], booking_num[18];
    int i, max = 0, flag = 0;
    while(booking)
    {
        strcpy(booking_num, booking->booking_num);
        strcpy(key[0], strtok(booking_num, linker));
        for(i = 1; i < 3; i++)
        {
            strcpy(key[i], strtok(NULL, linker));
        }
        if(!strcmp(key[0], date))
        {
            if(!strcmp(key[1], train_name_str))
            {
                i = atoi(key[2]);
                if(i > max)
                {
                    max = i;
                }
                flag = 1;
            }
        }
        booking = booking->next;
    }
    //如果找到，则序号比最大值加1
    if(flag)
    {
        sprintf(result, "%s-%s-%03d", date, train_name_str, max + 1);
    }
    else
    {
        //没找到则直接拼接，序号为001
        sprintf(result, "%s-%s-001", date, train_name_str);
    }
    return result;
}

float getTicketsPrice(char* seat_level, float origin_distance, float destination_distance){
    //根据座位等级，起点站和终点站里程计算票价并返回
    char special[] = "商务座";
    char first[] = "一等座";
    char second[] = "二等座";
    float price = 0;
    if(!strcmp(seat_level, special))
    {
        price = 1.2 * (destination_distance - origin_distance);
    }
    if(!strcmp(seat_level, first))
    {
        price = 0.6 * (destination_distance - origin_distance);
    }
    if(!strcmp(seat_level, second))
    {
        price = 0.46 * (destination_distance - origin_distance);
    }
    return price;
}

PBOOKING getBooking(TRAINLIST train_list, PPASSENGER pas_list, PBOOKING book_list, char* id_num,
                    char* date, char* train_name, char* origin, char* destination, char* seat_level,
                    int seat_num)
    {
        PPASSENGER passenger = pas_list;  //定义指向链表的指针，用于搜索乘客信息
        PBOOKING booking;
        booking = (PBOOKING)malloc(sizeof(BOOKING));
        //char booking_num[18], id_type[13], passenger_name[20], dep_time[6], arr_time[6];
        float price;
        strcpy(booking->booking_num, getBookingNum(book_list, date, train_name));
        strcpy(booking->date, date);
        strcpy(booking->train_name, train_name);
        strcpy(booking->origin, origin);
        strcpy(booking->destination, destination);
        searchPasByIdNum(pas_list, passenger, id_num);
        strcpy(booking->id_type, passenger->id_type);
        strcpy(booking->id_num, id_num);
        strcpy(booking->passenger_name, passenger->name);
        strcpy(booking->departure_time, getOriginDepTime(train_list, train_name, origin));
        strcpy(booking->arrival_time, getDestinationArrTime(train_list, train_name, destination));
        strcpy(booking->seat_level, seat_level);
        booking->seat_num = seat_num;
        booking->price = (double)getTicketsPrice(seat_level, getStopDistance(train_list, train_name, origin),
                                                    getStopDistance(train_list, train_name, destination));
        return booking;
}

Status checkLeftTickets(LEFTTICKETS*& left_tickets, int length, char*& train_name, char*& seat_level, int& seat_num){
    //获取用户输入并检查用户输入的车次、座位等级和座位号是否是存在剩余车票结构体中的，如果存在则依次赋值
    //不存在返回0
    if(!left_tickets) return ERROR;
    LEFTTICKETS* p = left_tickets;  
    char special[] = "商务座";
    char first[] = "一等座";
    char second[] = "二等座";
    char train_name_str[MAX_ARRAY_SIZE], seat_level_str[MAX_ARRAY_SIZE], seat_num_str[2];
    seat_num_str[1] = '\n';
    char c;
    int flag = 0, seat_num_int = 0;
    cout << "请输入要订的车次" << endl;
    cin.getline(train_name_str, MAX_ARRAY_SIZE);
    cout << "请输入座次等级(商务座、一等座或二等座):" << endl;
    cin.getline(seat_level_str, MAX_ARRAY_SIZE);
    cout << "请输入座位号:" << endl;
    cin.get(c);
    cin.ignore(MAX_ARRAY_SIZE, '\n');
    seat_num_str[0] = c;
    seat_num_int = atoi(seat_num_str);
    for(int i = 0; i < length; i++){
        if(!strcmp(p->train_name, train_name_str))
        {
            if(!strcmp(seat_level_str, special))
            {
                for(int j = 0; j < p->length[0]; j++){
                    if(seat_num_int != 0 && seat_num_int != -1 && seat_num_int == p->special[j])
                    {
                        flag = 1;
                        p->special[j] = 0;
                        break;
                    }
                }
                if(flag) break;
            }
            if(!strcmp(seat_level_str, first))
            {
                for(int j = 0; j < p->length[1]; j++){
                    if(seat_num_int != 0 && seat_num_int != -1 && seat_num_int == p->first[j])
                    {
                        flag = 1;
                        p->first[j] = 0;
                        break;
                    }
                }
                if(flag) break;
            }
            if(!strcmp(seat_level_str, second))
            {
                for(int j = 0; j < p->length[2]; j++){
                    if(seat_num_int != 0 && seat_num_int != -1 && seat_num_int == p->second[j])
                    {
                        flag = 1;
                        p->second[j] = 0;
                        break;
                    }
                }
                if(flag) break;
            }
        }
        p++;
    }
    if(flag)
    {
        train_name = (char*)malloc(20 * sizeof(char));
        seat_level = (char*)malloc(20 * sizeof(char));
        strcpy(train_name, train_name_str);
        strcpy(seat_level, seat_level_str);
        seat_num = seat_num_int;
    }
    return flag;
}

Status checkLeftTicketsNext(LEFTTICKETS*& left_tickets, int length, char* train_name, char*& seat_level, int& seat_num){
    //为同行乘客订票使用，获取用户输入并检查用户输入的座位等级和座位号是否是存在剩余车票结构体中的，如果存在则依次赋值
    //不存在返回0
    if(!left_tickets) return ERROR;
    LEFTTICKETS* p = left_tickets;  
    char special[] = "商务座";
    char first[] = "一等座";
    char second[] = "二等座";
    char train_name_str[MAX_ARRAY_SIZE], seat_level_str[MAX_ARRAY_SIZE], seat_num_str[2];
    seat_num_str[1] = '\n';
    char c;
    int flag = 0, seat_num_int = 0;
    strcpy(train_name_str, train_name);
    cout << "请输入座次等级(商务座、一等座或二等座):" << endl;
    cin.getline(seat_level_str, MAX_ARRAY_SIZE);
    cout << "请输入座位号:" << endl;
    cin.get(c);
    cin.ignore(MAX_ARRAY_SIZE, '\n');
    seat_num_str[0] = c;
    seat_num_int = atoi(seat_num_str);
    for(int i = 0; i < length; i++){
        if(!strcmp(p->train_name, train_name_str))
        {
            if(!strcmp(seat_level_str, special))
            {
                for(int j = 0; j < p->length[0]; j++){
                    if(seat_num_int != 0 && seat_num_int != -1 && seat_num_int == p->special[j])
                    {
                        flag = 1;
                        p->special[j] = 0;
                        break;
                    }
                }
                if(flag) break;
            }
            if(!strcmp(seat_level_str, first))
            {
                for(int j = 0; j < p->length[1]; j++){
                    if(seat_num_int != 0 && seat_num_int != -1 && seat_num_int == p->first[j])
                    {
                        flag = 1;
                        p->first[j] = 0;
                        break;
                    }
                }
                if(flag) break;
            }
            if(!strcmp(seat_level_str, second))
            {
                for(int j = 0; j < p->length[2]; j++){
                    if(seat_num_int != 0 && seat_num_int != -1 && seat_num_int == p->second[j])
                    {
                        flag = 1;
                        p->second[j] = 0;
                        break;
                    }
                }
                if(flag) break;
            }
        }
        p++;
    }
    if(flag)
    {
        train_name = (char*)malloc(20 * sizeof(char));
        seat_level = (char*)malloc(20 * sizeof(char));
        strcpy(train_name, train_name_str);
        strcpy(seat_level, seat_level_str);
        seat_num = seat_num_int;
    }
    return flag;
}

Status insertBookList(PBOOKING& book_list){
    if(!book_list) return ERROR;
    char filename[] = "..\\data\\passenger.txt";
    char filename1[] = "..\\data\\booking.txt";
    char filename2[] = "..\\data\\train.txt";
    TRAINLIST train_list;  //定义高铁顺序表
    inputTrainList(train_list, filename2); //从文件读入高铁信息
    TREE root;     //定义树根
    initTree(root);  //初始化搜索树
    PBOOKING booking = book_list->next;
    while(booking)  //将所有订票信息插入搜索树
    {
        insertTree(root, getBookCode(booking, train_list));
        booking = booking->next;
    }
    PPASSENGER pas_list;  //定义乘客信息链表头
    PPASSENGER passenger = pas_list;  //定义指向链表的指针，用于搜索乘客信息
    initPasList(pas_list);
    inputPasList(pas_list, filename);

    
    //以上为初始化代码

    char id_num[MAX_ARRAY_SIZE];
    cout << "请输入需要订票的乘客证件号:" << endl;
    cin.getline(id_num, MAX_ARRAY_SIZE);
    if(searchPasByIdNum(pas_list, passenger, id_num))
    {
        char date[MAX_ARRAY_SIZE], train_name[MAX_ARRAY_SIZE], origin[MAX_ARRAY_SIZE], destination[MAX_ARRAY_SIZE]; //定义日期，起点站，终点站字符串
        cout << "请输入需要订票的日期,日期从今日" << getDateStr(getSysTime()) << "至" << getDateStr(getDateTwoMonLater()) << endl;
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
                int length = 0; //定义顺序表长度
                for(int i = 0; train_index[i] != -1; i++)
                    length++;

                //根据长度创建一个剩余车票结构体顺序表，用来圈定订票的座次范围
                LEFTTICKETS* left_tickets = (LEFTTICKETS*)malloc(length * sizeof(LEFTTICKETS));
                LEFTTICKETS* p = left_tickets;
                for(int i = 0; train_index[i] != -1; i++){
                    setLeftTickets1(p, root, train_list, date, 
                    train_list.train_value.name[train_index[i]], 
                    getTrainStopCode(train_list, train_list.train_value.name[train_index[i]], origin, destination));
                    displayLeftTickets(*(p));
                    p++;
                }
                char* train_name, *seat_level;
                int seat_num;
                if(checkLeftTickets(left_tickets, length, train_name, seat_level, seat_num))
                {
                    PBOOKING p = (PBOOKING)malloc(sizeof(BOOKING));
                    p = getBooking(train_list, pas_list, book_list, id_num, date, train_name,
                                                origin, destination, seat_level, seat_num);
                    insertBookListTail(book_list, p);
                    printBookingByPtr(p);

                    cout << "是否要为同行乘客订票?" << endl;
                    char yes[] = "是", answer[10];
                    cin.getline(answer, 10);
                    if(!strcmp(answer, yes))
                    {
                        cout << "请输入需要订票的乘客证件号:" << endl;
                        cin.getline(id_num, MAX_ARRAY_SIZE);
                        if(searchPasByIdNum(pas_list, passenger, id_num))
                        {
                            if(checkLeftTicketsNext(left_tickets, length, train_name, seat_level, seat_num))
                            {
                                p = getBooking(train_list, pas_list, book_list, id_num, date, train_name,
                                                    origin, destination, seat_level, seat_num);
                                insertBookListTail(book_list, p);
                                printBookingByPtr(p);
                                cout << "是否要为同行乘客订票?" << endl;
                                cin.getline(answer, 10);
                                if(!strcmp(answer, yes))
                                {
                                    cout << "请输入需要订票的乘客证件号:" << endl;
                                    cin.getline(id_num, MAX_ARRAY_SIZE);
                                    if(searchPasByIdNum(pas_list, passenger, id_num))
                                    {
                                        if(checkLeftTicketsNext(left_tickets, length, train_name, seat_level, seat_num))
                                        {
                                            p = getBooking(train_list, pas_list, book_list, id_num, date, train_name,
                                                        origin, destination, seat_level, seat_num);
                                            insertBookListTail(book_list, p);
                                            printBookingByPtr(p);
                                        }
                                        else
                                        {
                                            cout << "输入的信息有误!" << endl;
                                        }
                                    }
                                    else
                                    {
                                        cout << "该乘客不存在" << endl;
                                    }
                                }
                                
                            }
                            else
                            {
                                cout << "输入的信息有误!" << endl;
                            }
                        }
                        else
                        {
                            cout << "该乘客不存在" << endl;
                        }
                    }
                    
                }
                else
                {
                    cout << "输入的信息有误!" << endl;
                }
            }
            else
            {
                cout << "没有符合条件的车次!" << endl;
            }
            
        }
        else
        {
            cout << "该日期不符合要求!" << endl;
        }
    }
    else
    {
        cout << "未找到乘客信息!" << endl;
    }

    freePasList(pas_list);
    freeTree(root);
    deleteTrainList(train_list);
    return OK;
}
