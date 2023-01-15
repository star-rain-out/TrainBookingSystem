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

const char ID[] = "���֤";
const char PASSPORT[] = "����";
const char NUMBER[] = "0123456789";

typedef struct date
{
   int y,m,d; //�����ꡢ�¡���
}DATE; 

static DATE getSysTime( )       //���ص�ǰϵͳʱ��
{   
    struct tm today;       //���ʱ��Ľṹ��
    time_t one;            //���ʱ�������
    DATE now;
    one=time(&one);              //���ϵͳʱ��
    today=*(gmtime(&one));       //��time_t��ʽϵͳʱ��תΪstruct tm��ʽ
    now.y=today.tm_year-100+2000;     //2011�귵��111
    now.m=today.tm_mon+1;           //9�·���8;
    now.d=today.tm_mday;
    return now;
}

static Status checkIn(char key, const char par[]){
	/*
	�ж��ַ��Ƿ�������ַ�����
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
	//�ж��ַ����Ƿ�ֻ��������
	char number[] = "0123456789";
	int len = strlen(num);
	for(int i = 0; i < len; i++)
	{
		if(!checkIn(num[i], number)) return ERROR;
	}
	return OK;
}

static Status checkFloat(char num[]){
	//�ж��ַ����Ƿ�ֻ�������ֺ�С����
	char number1[] = "0123456789.";
	int len = strlen(num);
	for(int i = 0; i < len; i++)
	{
		if(!checkIn(num[i], number1)) return ERROR;
	}
	return OK;
}

static Status checkTime(char time[MAX_ARRAY_SIZE]){    
	//���ʱ���ʽ�Ƿ�Ϸ�
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
	//���ʱ��Ϸ��ԣ������time2�Ƿ���time1ʱ��֮��
	char time_1[MAX_ARRAY_SIZE], time_2[MAX_ARRAY_SIZE]; //�洢ʱ�丱��
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
    //����Ƿ�ȡ�����Ƿ���OK���񷵻�ERROR
	char cancel[] = "ȡ��";
	if(strcmp(cancel, str)){
		return ERROR;
	}
	return OK;
}

static int checkIdType(char id_type[]){
    //���֤�����ͣ����֤����1�����շ���2
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
    //����֤�������ж�֤�����Ƿ�Ϸ�
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
	//��������Ƿ�Ϸ�
	int Mon[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	Mon[2] = 28 + (date.y%4 == 0 && date.y%100 || date.y%400 == 0);
 	if(date.y > 0 && date.m > 0 && date.d > 0 && date.m < 13 && date.d <= Mon[date.m])
		return OK;
	else return ERROR;
}

static Status checkDateByStr(const char* str){
	//�����ַ����д�ŵ�����ת��Ϊ���ڽṹ�壬����ѯ�����Ƿ�Ϸ�
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
	//���ַ���ת��Ϊ���ڽṹ�岢���أ��˺����������ַ�����ʽ��ȷ�Ļ���֮��
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
	//����ǰ���ڼ������²�����date
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
	sprintf(str, "%d��%d��%d��", date.y, date.m, date.d);
	return str;
}

static Status checkDateByOrder(DATE date1, DATE date2){
	//�������˳�����date2��date1���ڿ������ȣ�����OK�����򷵻�ERROR
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
	//�������˳�����date2��date1���ڿ��󣬷���OK�����򷵻�ERROR
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

