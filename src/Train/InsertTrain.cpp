#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#include "Train.h"
#include "SearchTrain.h"
#include "../Check.h"
#define MAX_ARRAY_SIZE 50

using namespace std;

Status getTrainName(TRAINLIST train_list, PTRAIN train){
	//获取用户输入的车次名称并存入指针指向的内容中
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	char str1[MAX_ARRAY_SIZE];
	int num;   //用于检查车次数字是否合法
	int flag = 0;
	int index[MAX_ARRAY_SIZE];
	cout << "请输入新增的高铁车次（取消请输入“取消”并回车）：" << endl;
	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		strcpy(str1, str);
		if(str1[0] != 'G')
		{
			cout << "车次必须以G开头! 请重新输入" << endl;
			continue;
		}
		for(int i = 0; str1[i]!= '\0'; i++){
			str1[i] = str1[i + 1];
		}
		num = atoi(str1);
		if(num <= 0 || num > 1000 || !checkNumber(str1))
		{
			cout << "车次数字不合法,应取1~1000之间,请重新输入" << endl;
			continue;
		}
		for(int i = 0; i < train_list.train_num; i++){
			if(!strcmp(train_list.train_value.name[i], str))
			{
				cout << "该车次已存在，请重新输入" << endl;
				flag = 1;
				break;
			}
		}
		if(flag)
		{
			flag = 0;
			continue;
		} 
		strcpy(train->name, str);
		return OK;
	}
}

Status getTrainOrigin(PTRAIN train){
	//获取用户输入的始发站名称并存入指针指向的内容中
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	cout << "请输入始发站：" << endl;
	cin.getline(str, MAX_ARRAY_SIZE);
	if(checkCancel(str)) return ERROR;
	strcpy(train->origin, str);
	return OK;
}

Status getTrainDestination(PTRAIN train){
	//获取用户输入的终点站名称并存入指针指向的内容中
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	cout << "请输入终到站：" << endl;
	cin.getline(str, MAX_ARRAY_SIZE);
	if(checkCancel(str)) return ERROR;
	strcpy(train->destination, str);
	return OK;
}

Status getTrainDistance(PTRAIN train){
	//获取用户输入的运行距离并存入指针指向的内容中
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	int num;
	cout << "请输入运行距离：" << endl;
	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		num = atoi(str);
		if(num < 0 || num > 10000)
		{
			cout << "运行距离应在1-10000之间,请重新输入" << endl;
			continue;
		}
		train->distance = num;
		return OK;
	}
}

Status getTrainStatus(PTRAIN train){
	//获取用户输入的运行状态并存入指针指向的内容中
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	char normal[] = "正常";
	char stop[] = "停运";
	
	cout << "请输入运行状态（正常或停运）：" << endl;
	while (1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		if(strcmp(str, normal) && strcmp(str, stop))
		{
			cout << "运行状态应为正常或者停运，请重新输入" << endl;
			continue;
		}
		strcpy(train->status, str);
		break;
	}
	return OK;
}

Status getTrainDepTime(PTRAIN train){
	//获取用户输入的发车时间并存入指针指向的内容中
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	char zero[] = "0:0";
	cout << "请输入发车时间：" << endl;
	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		if(!checkTime(str) || !checkTimeByOrder(zero, str))
		{
			cout << "输入的时间格式有误（注意:为英文冒号），请重新输入" << endl;
			continue;
		}
		strcpy(train->departure_time, str);
		return OK;
	}
}

Status getTrainArrTime(PTRAIN train){
	//获取用户输入的到达时间并存入指针指向的内容中
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	cout << "请输入到达时间：" << endl;
	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		if(!checkTime(str))
		{
			cout << "输入的时间格式有误（注意:为英文冒号），请重新输入" << endl;
			continue;
		}
		if(!checkTimeByOrder(train->departure_time, str))
		{
			cout << "到达时间必须在发车时间之后，请重新输入" << endl;
			continue;
		}
		strcpy(train->arrival_time, str);
		return OK;
	}
}

Status getTrainSpecialClass(PTRAIN train){
	////获取用户输入的商务座数量并存入指针指向的内容中
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	int num;
	cout << "请输入特等座（商务座）数量：" << endl;
	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		num = atoi(str);
		if(num < 0 || num > 100 || !checkNumber(str))
		{
			cout << "特等座数量应在1-100之间,请重新输入" << endl;
			continue;
		}
		train->special_class = num;
		return OK;
	}
}

Status getTrainFirstClass(PTRAIN train){
	//获取用户输入的一等座并存入指针指向的内容中
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	int num;
	cout << "请输入一等座数量：" << endl;
	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		num = atoi(str);
		if(num < 0 || num > 100 || !checkNumber(str))
		{
			cout << "一等座数量应在1-100之间,请重新输入" << endl;
			continue;
		}
		train->first_class = num;
		return OK;
	}
}

Status getTrainSecondClass(PTRAIN train){
	//获取用户输入的二等座数量并存入指针指向的内容中
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	int num;
	cout << "请输入二等座数量：" << endl;
	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		num = atoi(str);
		if(num < 0 || num > 100 || !checkNumber(str))
		{
			cout << "二等座数量应在1-100之间,请重新输入" << endl;
			continue;
		}
		train->second_class = num;
		return OK;
	}
}

Status getTrainStopNum(PTRAIN train){
	//获取用户输入的停靠站数量并存入指针指向的内容中
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	int num;
	cout << "请输入停靠站数量：" << endl;
	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		num = atoi(str);
		if(num < 0 || num > 100 || !checkNumber(str))
		{
			cout << "停靠站数量应在1-100之间,请重新输入" << endl;
			continue;
		}
		train->stop_num = num;
		return OK;
	}
}

Status getTrainStopName(PTRAIN train, int stop_num){
	//获取第stop_num个停靠站名称
	char str[MAX_ARRAY_SIZE];
	cout << "请输入停靠站" << stop_num << "名称:" << endl;
	cin.getline(str, MAX_ARRAY_SIZE);
	if(checkCancel(str)) return ERROR;
	if(stop_num > 0)
	{
		strcpy(train->stop_names[stop_num - 1], str);
		return OK;
	}
	else return ERROR;
}

Status getTrainStopArrTime(PTRAIN train, int stop_num){
	//获取第stop_num个停靠站到站时间
	char str[MAX_ARRAY_SIZE];
	cout << "请输入停靠站" << stop_num << "到站时间:" << endl;
	while(1)
	{
		
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		if(!checkTime(str))
		{
			cout << "输入的时间格式有误，请重新输入" << endl;
			continue;
		}
		if(stop_num == 2)
		{
			//第一次比较时间与发车时间进行比较
			if(!checkTimeByOrder(train->departure_time, str) || !checkTimeByOrder(str, train->arrival_time))
			{
				cout << "到站时间应比发车时间晚，比到达终点站时间早，请重新输入" << endl;
				continue;
			}
			strcpy(train->stop_arrival_time[stop_num - 1], str);
			break;
		}
		if(!checkTimeByOrder(train->stop_departure_time[stop_num - 2], str) || !checkTimeByOrder(str, train->arrival_time))
		{
			cout << "到站时间应比前一停靠站发车时间晚，比到达终点站时间早，请重新输入" << endl;
			continue;
		}
		strcpy(train->stop_arrival_time[stop_num - 1], str);
		break;
	}
	return OK;
}

Status getTrainStopDepTime(PTRAIN train, int stop_num){
	//获取第stop_num个停靠站出站时间
	char str[MAX_ARRAY_SIZE];
	cout << "请输入停靠站" << stop_num << "出站时间:" << endl;
	while(1)
	{
		
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		if(!checkTime(str))
		{
			cout << "输入的时间格式有误，请重新输入" << endl;
			continue;
		}
		if(!checkTimeByOrder(train->stop_arrival_time[stop_num - 1], str) || !checkTimeByOrder(str, train->arrival_time))
		{
			cout << "发车时间应比到站时间晚，比到达终点站时间早，请重新输入" << endl;
			continue;
		}
		strcpy(train->stop_departure_time[stop_num - 1], str);
		break;
	}
	return OK;
}

Status getTrainStopDistance(PTRAIN train, int stop_num){
	//获取第stop_num个停靠站里程
	float distance;
	char str[MAX_ARRAY_SIZE];
	cout << "请输入停靠站" << stop_num << "里程:" << endl;
	while (1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		distance = atof(str);
		if(distance < 0 || distance >= train->distance || !checkFloat(str))
		{
			cout << "里程应在【0-运行距离】之间，请重新输入" << endl;
			continue;
		}
		if(distance <= train->stop_distance[stop_num - 2])
		{
			cout << "里程应在前一站里程之后，请重新输入" << endl;
			continue;
		}
		train->stop_distance[stop_num - 1] = distance;
		break;
	}
	return OK;
}

Status getTrainStopInfo(PTRAIN train){
	/*
	获取停靠站名称，到站时间，出发时间和里程。
	获取时检查数据合法性，停靠站到站时间应比前一站出站时间靠后
	将第一个停靠站和最后一个停靠站的信息更改为始发站和终到站的信息
	*/
	if(!train) return ERROR;

	strcpy(train->stop_names[0], train->origin);
	strcpy(train->stop_arrival_time[0], train->departure_time);
	strcpy(train->stop_departure_time[0], train->departure_time);
	train->stop_distance[0] = 0;
	strcpy(train->stop_names[train->stop_num - 1], train->destination);
	strcpy(train->stop_arrival_time[train->stop_num - 1], train->arrival_time);
	strcpy(train->stop_departure_time[train->stop_num - 1], train->arrival_time);
	train->stop_distance[train->stop_num - 1] = train->distance;
	char str[MAX_ARRAY_SIZE];
	char time_before[MAX_ARRAY_SIZE]; //存储上一个输入的时间，用于比较时间次序
	float distance;
	float distance_before = 0;
	
	for(int i = 2; i < train->stop_num; i++)
	{
		if(
			!getTrainStopName(train, i) ||
			!getTrainStopArrTime(train, i) ||
			!getTrainStopDepTime(train, i) ||
			!getTrainStopDistance(train ,i)
		) return ERROR;
	}
	return OK;
}

Status getTrainInfo(TRAINLIST train_list, PTRAIN train){
	//获取用户输入的主体函数
	if(!train){
		cout << 1;
		return ERROR;
	}
	if(
		!getTrainName(train_list, train) ||
		!getTrainOrigin(train) ||
		!getTrainDestination(train) ||
		!getTrainDistance(train) ||
		!getTrainStatus(train) ||
		!getTrainDepTime(train) ||
		!getTrainArrTime(train) ||
		!getTrainSpecialClass(train) ||
		!getTrainFirstClass(train) ||
		!getTrainSecondClass(train) ||
		!getTrainStopNum(train) ||
		!getTrainStopInfo(train)
	)	return ERROR;
	return OK;
}

Status insertTrain(TRAINLIST& train_list){
	//插入高铁信息的主体函数，先获取信息，然后进行插入
	PTRAIN p = (PTRAIN)realloc(train_list.elem, (train_list.train_num + 1) * sizeof(TRAIN));
	if(!p) return ERROR;
	train_list.elem = p;
	p += train_list.train_num;
	
	if(!getTrainInfo(train_list, p))
	{
		cout << "插入失败" << endl;
		return ERROR;
	}
	train_list.train_num++;
	setTrainValue(train_list);
	cout << "插入成功！" << endl;
	return OK;
}
