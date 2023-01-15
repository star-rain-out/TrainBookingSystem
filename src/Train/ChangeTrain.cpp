#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "Train.h"
#include "../Check.h"
#define MAX_ARRAY_SIZE 50

#define CANCEL 2

using namespace std;


int num = 0; //全局变量，保存需要修改的停靠站序号

Status getStopNum(PTRAIN train, int& num){
	//获取用户输入，并将停靠站数量赋值给引用参数num
    if(!train) return ERROR;
    int num1;
	char str[MAX_ARRAY_SIZE];
	cout << "请输入要修改的停靠站序号（第一站和最后一站无法修改）：" << endl;
	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		num1 = atoi(str);
		if(num < 2 || num > (train->stop_num - 1) || !checkNumber(str))
		{
			cout << "停靠站序号应在" << train->stop_num -1 << "之间,请重新输入" << endl;
			continue;
		}
		num = num1;
		return OK;
	}
}

Status changeTrainOrigin(PTRAIN train){
	//获取用户输入的始发站名称并存到指针指向的内容中
    if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	cout << "请输入新始发站：" << endl;
	cin.getline(str, MAX_ARRAY_SIZE);
	if(checkCancel(str)) return ERROR;
	strcpy(train->origin, str);
	return OK;
}

Status changeTrainDestination(PTRAIN train){
	//获取用户输入的终点站名称并存到指针指向的内容中
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	cout << "请输入新终到站：" << endl;
	cin.getline(str, MAX_ARRAY_SIZE);
	if(checkCancel(str)) return ERROR;
	strcpy(train->destination, str);
	return OK;
}

Status changeTrainDistance(PTRAIN train){
	//获取用户输入的运行距离并存到指针指向的内容中
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	int num;
	cout << "请输入新的运行距离：" << endl;
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

Status changeTrainStatus(PTRAIN train){
	//改变高铁的运行状态
	if(!train) return ERROR;
	char normal[] = "正常";
	char stop[] = "停运";
	if(strcmp(train->status, normal) && strcmp(train->status, stop)) return ERROR;
    if(strcmp(train->status, normal))
    {
        strcpy(train->status, normal);
        cout << "运行状态已更改为" << normal << endl;
    }
    else
    {
        strcpy(train->status, stop);
        cout << "运行状态已更改为" << stop << endl;
    }
	
	return OK;
}

Status changeTrainDepTime(PTRAIN train){
	//获取用户输入的发车时间并存到指针指向的内容中
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	char zero[] = "0:0";
	cout << "请输入新的发车时间：" << endl;
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

Status changeTrainArrTime(PTRAIN train){
	//获取用户输入的到达时间并存到指针指向的内容中
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	cout << "请输入新的到达时间：" << endl;
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

Status changeTrainSpecialClass(PTRAIN train){
	//获取用户输入的特等座数量并存到指针指向的内容中
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	int num;
	cout << "请新的输入特等座（商务座）数量：" << endl;
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

Status changeTrainFirstClass(PTRAIN train){
	//获取用户输入的一等座数量并存到指针指向的内容中
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	int num;
	cout << "请输入新的一等座数量：" << endl;
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

Status changeTrainSecondClass(PTRAIN train){
	//获取用户输入的二等座数量并存到指针指向的内容中
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	int num;
	cout << "请输入新的二等座数量：" << endl;
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

Status changeTrainStopNum(PTRAIN train){
	//获取用户输入的停靠站数量并存到指针指向的内容中
	if(!train) return ERROR;
	char str[MAX_ARRAY_SIZE];
	
	int num;
	cout << "请输入新的停靠站数量（若修改停靠站数量，则要重新输入所有停靠站信息）：" << endl;
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

Status changeTrainStopName(PTRAIN train, int stop_num){
	//获取第stop_num个停靠站名称
	char str[MAX_ARRAY_SIZE];
	cout << "请输入新的停靠站" << stop_num << "名称:" << endl;
	cin.getline(str, MAX_ARRAY_SIZE);
	if(checkCancel(str)) return ERROR;
	if(stop_num > 0)
	{
		strcpy(train->stop_names[stop_num - 1], str);
		return OK;
	}
	else return ERROR;
}

Status changeTrainStopArrTime(PTRAIN train, int stop_num){
	//获取第stop_num个停靠站到站时间
	char str[MAX_ARRAY_SIZE];
	cout << "请输入新的停靠站" << stop_num << "到站时间:" << endl;
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
			strcpy(train->stop_arrival_time[stop_num], str);
			break;
		}
		if(!checkTimeByOrder(train->stop_departure_time[stop_num - 1], str) || !checkTimeByOrder(str, train->arrival_time))
		{
			cout << "到站时间应比前一停靠站发车时间晚，比到达终点站时间早，请重新输入" << endl;
			continue;
		}
		strcpy(train->stop_arrival_time[stop_num], str);
		break;
	}
	return OK;
}

Status changeTrainStopDepTime(PTRAIN train, int stop_num){
	//修改第stop_num个停靠站出站时间
	char str[MAX_ARRAY_SIZE];
	cout << "请输入新的停靠站" << stop_num << "出站时间:" << endl;
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
		strcpy(train->stop_arrival_time[stop_num], str);
		break;
	}
	return OK;
}

Status changeTrainStopDistance(PTRAIN train, int stop_num){
	//修改第stop_num个停靠站里程
	float distance;
	char str[MAX_ARRAY_SIZE];
	cout << "请输入新的停靠站" << stop_num << "里程:" << endl;
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

Status changeTrainStopInfo(PTRAIN train){
	/*
	修改停靠站名称，到站时间，出发时间和里程。
	修改时检查数据合法性，停靠站到站时间应比前一站出站时间靠后
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
			!changeTrainStopName(train, i) ||
			!changeTrainStopArrTime(train, i) ||
			!changeTrainStopDepTime(train, i) ||
			!changeTrainStopDistance(train ,i)
		) return ERROR;
	}
	return OK;
}

Status changeTrainInfo(TRAINLIST& train_list){
	/*
    根据type的值修改高铁信息
    type=0：全部修改
	1：修改始发地
	2：修改终到地
	3：修改运行距离
	4：修改运行状态
	5：修改发车时间
	6：修改到达时间
	7：修改特等座数量
    8：修改一等座数量
    9：修改二等座数量
    10：修改停靠站数量（如果修改，则必须修改所有停靠站信息）
    11：修改停靠站名称
    12：修改停靠站到站时间
    13：修改停靠站出站时间
    14：修改停靠站里程
    */
   	PTRAIN train = train_list.elem;
	int flag = 0; //标记是否找到车次
	int i = 0; //存放车次数组下标
	char str[MAX_ARRAY_SIZE];
	int type = 0;
	cout << "请输入要修改的高铁车次：" << endl;
	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		for(i = 0; i < train_list.train_num; i++){
			if(!strcmp(train_list.train_value.name[i], str))
			{
				flag = 1;
				break;
			}
		}
		if(!flag)
		{
			cout << "未找到该车次，请重新输入；" << endl;
			continue;
		} 
		break;
	}
	train += i; //指针指向需要修改的车次

	cout << "请选择需要修改的类型（输入对应的阿拉伯数字）：" << endl;
	cout << "0:全部修改" << endl;
	cout << "1:修改始发地" << endl;
	cout << "2:修改终到地" << endl;
	cout << "3:修改运行距离" << endl;
	cout << "4:修改运行状态" << endl;
	cout << "5:修改发车时间" << endl;
	cout << "6:修改到达时间" << endl;
	cout << "7:修改特等座数量" << endl;
    cout << "8:修改一等座数量" << endl;
    cout << "9:修改二等座数量" << endl;
    cout << "10:修改停靠站数量（如果修改，则必须修改所有停靠站信息）" << endl;
    cout << "11:修改停靠站名称" << endl;
    cout << "12:修改停靠站到站时间" << endl;
    cout << "13:修改停靠站出站时间" << endl;
    cout << "14:修改停靠站里程" << endl;
	cout << "15:返回上一级" << endl;
	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		
		if(!checkNumber(str))
		{
			cout << "输入数字不合法，请重新输入" << endl;
			continue;
		}
		type = atoi(str);
		if(type < 0 || type > 15)
		{
			cout << "输入的序号不正确，请重新输入" << endl;
			continue;
		}
		break;
	}

    switch (type)
    {
    case 0:
        if(
		    !changeTrainOrigin(train) ||
		    !changeTrainDestination(train) ||
		    !changeTrainDistance(train) ||
		    !changeTrainStatus(train) ||
		    !changeTrainDepTime(train) ||
		    !changeTrainArrTime(train) ||
		    !changeTrainSpecialClass(train) ||
		    !changeTrainFirstClass(train) ||
		    !changeTrainSecondClass(train) ||
		    !changeTrainStopNum(train) ||
		    !changeTrainStopInfo(train)
	    )	return ERROR;
        break;
    case 1:
        if(!changeTrainOrigin(train)) return ERROR;
        strcpy(train->stop_names[0], train->origin);
        break;
    case 2:
        if(!changeTrainDestination(train)) return ERROR;
        strcpy(train->stop_names[train->stop_num - 1], train->destination);
        break;
    case 3:
        if(!changeTrainDistance(train)) return ERROR;
        train->stop_distance[train->stop_num - 1] = train->distance;
        break;
    case 4:
        if(!changeTrainStatus(train)) return ERROR;
        break;
    case 5:
        if(!changeTrainDepTime(train)) return ERROR;
        strcpy(train->stop_arrival_time[0], train->departure_time);
	    strcpy(train->stop_departure_time[0], train->departure_time);
        break;
    case 6:
        if(!changeTrainArrTime(train)) return ERROR;
        strcpy(train->stop_arrival_time[train->stop_num - 1], train->arrival_time);
	    strcpy(train->stop_departure_time[train->stop_num - 1], train->arrival_time);
        break;
    case 7:
        if(!changeTrainSpecialClass(train)) return ERROR;
        break;
    case 8:
        if(!changeTrainFirstClass(train)) return ERROR;
        break;
    case 9:
        if(!changeTrainSecondClass(train)) return ERROR;
        break;
    case 10:
        if(!changeTrainStopNum(train) || !changeTrainStopInfo(train)) return ERROR;
        break;
    case 11:
        if(!getStopNum(train, num)) return ERROR;
        if(!changeTrainStopName(train, num)) return ERROR;
        break;
    case 12:
        if(!getStopNum(train, num)) return ERROR;
        if(!changeTrainStopArrTime(train, num)) return ERROR;
        break;
    case 13:
        if(!getStopNum(train, num)) return ERROR;
        if(!changeTrainStopDepTime(train, num)) return ERROR;
        break;
    case 14:
        if(!getStopNum(train, num)) return ERROR;
        if(!changeTrainStopDistance(train, num)) return ERROR;
        break;
	case 15:
		return CANCEL;
		break;
    default:
		return ERROR;
        break;
    }
	
	return OK;
}

Status changeTrain(TRAINLIST& train_list){
	/*
    根据type的值修改高铁信息
    type=0：全部修改
	1：修改始发地
	2：修改终到地
	3：修改运行距离
	4：修改运行状态
	5：修改发车时间
	6：修改到达时间
	7：修改特等座数量
    8：修改一等座数量
    9：修改二等座数量
    10：修改停靠站数量（如果修改，则必须修改所有停靠站信息）
    11：修改停靠站名称
    12：修改停靠站到站时间
    13：修改停靠站出站时间
    14：修改停靠站里程
    */
   	int status = changeTrainInfo(train_list);
   	if(!status)
   	{
		cout << "修改失败" << endl;
   	}
	if(status == OK)
	{
		cout << "修改成功" << endl;
		setTrainValue(train_list);
	}
	return OK;
}

Status turnTrainStatus(TRAINLIST& train_list){
	//改变高铁的运行状态，正常就变成停运，反之相反
	PTRAIN train = train_list.elem;
	int flag = 0; //标记是否找到车次
	int i = 0; //存放车次数组下标
	char str[MAX_ARRAY_SIZE];
	int type = 0;
	cout << "请输入要修改的高铁车次：" << endl;
	while(1)
	{
		cin.getline(str, MAX_ARRAY_SIZE);
		if(checkCancel(str)) return ERROR;
		for(i = 0; i < train_list.train_num; i++){
			if(!strcmp(train_list.train_value.name[i], str))
			{
				flag = 1;
				break;
			}
		}
		if(!flag)
		{
			cout << "未找到该车次，请重新输入；" << endl;
			continue;
		} 
		break;
	}
	train += i; //指针指向需要修改的车次


	char normal[] = "正常";
	char stop[] = "停运";
	if(strcmp(train->status, normal) && strcmp(train->status, stop)) return ERROR;
    if(strcmp(train->status, normal))
    {
        strcpy(train->status, normal);
        cout << "运行状态已更改为" << normal << endl;
    }
    else
    {
        strcpy(train->status, stop);
        cout << "运行状态已更改为" << stop << endl;
    }
	setTrainValue(train_list);
	return OK;
}