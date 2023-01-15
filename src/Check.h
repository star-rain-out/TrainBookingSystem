#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define OK 1
#define ERROR 0
#define MAX_ARRAY_SIZE 50
typedef int Status;
using namespace std;

const char ID[] = "身份证";
const char PASSPORT[] = "护照";
const char NUMBER[] = "0123456789";

typedef struct date
{
   int y,m,d; //定义年、月、日
}DATE; 

static DATE getSysTime( )       //返回当前系统时间
{   
    struct tm today;       //存放时间的结构体
    time_t one;            //存放时间的类型
    DATE now;
    one=time(&one);              //获得系统时间
    today=*(gmtime(&one));       //将time_t格式系统时间转为struct tm格式
    now.y=today.tm_year-100+2000;     //2011年返回111
    now.m=today.tm_mon+1;           //9月返回8;
    now.d=today.tm_mday;
    return now;
}

static Status checkIn(char key, const char par[]){
	/*
	判断字符是否包含在字符串中
	*/
    int len =strlen(par);
    int i=0;
    for(i=0; i < len; i++){
        if(par[i] == key)
            return OK;
    }
    return ERROR;
}

static Status checkNumber(char* num){
	//判断字符串是否只包含数字
	char number[] = "0123456789";
	int len = strlen(num);
	for(int i = 0; i < len; i++)
	{
		if(!checkIn(num[i], number)) return ERROR;
	}
	return OK;
}

static Status checkFloat(char num[]){
	//判断字符串是否只包含数字和小数点
	char number1[] = "0123456789.";
	int len = strlen(num);
	for(int i = 0; i < len; i++)
	{
		if(!checkIn(num[i], number1)) return ERROR;
	}
	return OK;
}

static Status checkTime(char time[MAX_ARRAY_SIZE]){    
	//检查时间格式是否合法
	char number[] = "0123456789:";
	int len = strlen(time);
	for(int i = 0; i < len; i++)
	{
		if(!checkIn(time[i], number)) return ERROR;
	}
	int hour, minute;
	char time1[MAX_ARRAY_SIZE];
	char c = ':';
	int flag = 0;
	for(int i = 0; time[i] != '\0'; i++)
	{
		if(time[i] == c) flag += 1;
	}
	if(flag = 0 || flag > 1) return ERROR;
	strcpy(time1, time);
	char* str = strtok(time1, ":");
	hour = atoi(str);
	str = strtok(NULL, ":");
	minute = atoi(str);
	if(hour < 0 || hour > 24) return ERROR;
	if(minute < 0 || minute > 60) return ERROR;
	return OK;
}

static Status checkTimeByOrder(char* time1, char* time2){    
	//检查时间合法性，并检查time2是否在time1时间之后
	char time_1[MAX_ARRAY_SIZE], time_2[MAX_ARRAY_SIZE]; //存储时间副本
	int hour1, hour2, minute1, minute2;
	strcpy(time_1, time1);
	strcpy(time_2, time2);
	char* str = strtok(time_1, ":");
	hour1 = atoi(str);
	str = strtok(NULL, ":");
	minute1 = atoi(str);
	str = strtok(time_2, ":");
	hour2 = atoi(str);
	str = strtok(NULL, ":");
	minute2 = atoi(str);
	if(hour1 == hour2)
	{
		if(minute2 <= minute1) return ERROR;
	}
	else
	{
		if(hour2 < hour1) return ERROR;
	}
	return OK;
}

static Status checkCancel(char* str){
    //检查是否取消，是返回OK，否返回ERROR
	char cancel[] = "取消";
	if(strcmp(cancel, str)){
		return ERROR;
	}
	return OK;
}

static int checkIdType(char id_type[]){
    //检查证件类型，身份证返回1，护照返回2
    if(!strcmp(id_type, ID))
    {
        return 1;
    }
    else if(!strcmp(id_type, PASSPORT))
    {
        return 2;
    }
    else return ERROR;
}

static Status checkIdNum(char id_num[], int type){
    //根据证件类型判断证件号是否合法
    const char ID[] = "0123456789X ";
    const char WORD[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    switch (type)
    {
    case 1:
        if(strlen(id_num) > 18) return ERROR;
        for(int i = 0; i < 17; i++)
        {
            if(!checkIn(id_num[i], NUMBER)) return ERROR;
        }
        if(!checkIn(id_num[17], ID)) return ERROR;
        break;
    case 2:
        if(strlen(id_num) > 9 || strlen(id_num) <8) return ERROR;
        if(!checkIn(id_num[0], WORD)) return ERROR;
        break;
    default:
        return ERROR;
        break;
    }
    return OK;
}


static Status checkDate(DATE date)
{
	//检查日期是否合法
	int Mon[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	Mon[2] = 28 + (date.y%4 == 0 && date.y%100 || date.y%400 == 0);
 	if(date.y > 0 && date.m > 0 && date.d > 0 && date.m < 13 && date.d <= Mon[date.m])
		return OK;
	else return ERROR;
}

static Status checkDateByStr(const char* str){
	//根据字符串中存放的日期转换为日期结构体，并查询日期是否合法
	if(strlen(str) !=  8) return ERROR;
	char* s = (char*)malloc(9 * sizeof(char));
	strcpy(s, str);
	if(!checkNumber(s)) return ERROR;
	char y[5], m[3], d[3];
	DATE date;
	y[4] = '\0';
	m[2] = '\0';
	d[2] = '\0';
	for(int i = 0; i < 4; i++){
		y[i] = s[i];
	}
	m[0] = s[4];
	m[1] = s[5];
	d[0] = s[6];
	d[1] = s[7];
	date.y = atoi(y);
	date.m = atoi(m);
	date.d = atoi(d);
	if(!checkDate(date)) return ERROR;
	return OK;
}

static DATE getDateByStr(const char* str){
	//将字符串转换为日期结构体并返回，此函数建立在字符串格式正确的基础之上
	char* s = (char*)malloc(9 * sizeof(char));
	strcpy(s, str);
	char y[5], m[3], d[3];
	DATE date;
	y[4] = '\0';
	m[2] = '\0';
	d[2] = '\0';
	for(int i = 0; i < 4; i++){
		y[i] = s[i];
	}
	m[0] = s[4];
	m[1] = s[5];
	d[0] = s[6];
	d[1] = s[7];
	date.y = atoi(y);
	date.m = atoi(m);
	date.d = atoi(d);
	return date;
}

static DATE getDateTwoMonLater(){
	//将当前日期加两个月并返回date
	DATE date = getSysTime();
	int Mon[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	int day = date.d + 60 - Mon[date.m];
	int month = date.m + 1;
	if(day > Mon[date.m + 1])
	{
		day -= Mon[date.m + 1];
		month++;
		if(day > Mon[date.m + 2])
		{
			day -= Mon[date.m + 2];
			month++;
		}
	}
	date.d = day;
	date.m = month;
	return date;
}

static char* getDateStr(DATE date){
	char* str = (char*)malloc(20 * sizeof(char));
	sprintf(str, "%d年%d月%d日", date.y, date.m, date.d);
	return str;
}

static Status checkDateByOrder(DATE date1, DATE date2){
	//检查日期顺序，如果date2比date1日期靠后或相等，返回OK，否则返回ERROR
	if(date1.y > date2.y) return ERROR;
	if(date1.y == date2.y)
	{
		if(date1.m > date2.m) return ERROR;
		if(date1.m == date2.m)
		{
			if(date1.d > date2.d) return ERROR;
			else return OK;
		} else return OK;
	} else return OK;
}

static Status checkDateByOrder1(DATE date1, DATE date2){
	//检查日期顺序，如果date2比date1日期靠后，返回OK，否则返回ERROR
	if(date1.y > date2.y) return ERROR;
	if(date1.y == date2.y)
	{
		if(date1.m > date2.m) return ERROR;
		if(date1.m == date2.m)
		{
			if(date1.d >= date2.d) return ERROR;
			else return OK;
		} else return OK;
	} else return OK;
}

