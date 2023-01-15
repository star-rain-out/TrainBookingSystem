#pragma once

#define MAX_ARRAY_SIZE 50
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define CANCEL 2
#define CANCEL 2

typedef int Status;
const char linefeed = '\n';
typedef struct Train {
	/*
	此结构体为高铁车次信息主结构体，包含各种主要信息
	*/
	char name[MAX_ARRAY_SIZE];			//车次
	char origin[MAX_ARRAY_SIZE];		//始发地
	char destination[MAX_ARRAY_SIZE];	//终到地
	int distance;						//运行距离
	char status[MAX_ARRAY_SIZE];		//运行状态
	char departure_time[MAX_ARRAY_SIZE];//发车时间
	char arrival_time[MAX_ARRAY_SIZE];	//到达时间
 	int stop_num;              			//停靠站数量
  	int special_class;					//特等座（商务座）数量
  	int first_class;					//一等座数量
  	int second_class;					//二等座数量
	char stop_names[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];			//停靠站名称，二维数组形式保存
	char stop_arrival_time[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];		//停靠站到站时间
	char stop_departure_time[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];	//停靠站出发时间
	float stop_distance[MAX_ARRAY_SIZE];						//到停靠站所需距离
}TRAIN, *PTRAIN;

typedef struct StopName{
	/*
	此结构体为辅助结构体，用于存放停靠站名称的二维数组，便于查找停靠站信息
	*/
	char stop_names[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
}STOPNAME, *PSTOPNAME;

typedef struct TrainValue {
	/*
	此结构体为辅助结构体，用于存放各字段，便于根据字段查找信息
	*/
    char name[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
	char origin[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
	char destination[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
	char status[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
	char departure_time[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
	char arrival_time[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
	PSTOPNAME stop_names;
}TRAINVALUE;

typedef struct TrainList {
	/*
	本系统采用顺序表形式存放高铁车次信息，此结构体为顺序表结构体
	*/
	PTRAIN elem; //顺序表表头
	TRAINVALUE train_value; //辅助查找结构体
	int train_num;  //高铁数量
}TRAINLIST;

Status initTrainList(TRAINLIST& train_list, int train_num);
Status inputTrainList(TRAINLIST& train_list, char filename[MAX_ARRAY_SIZE]);
Status setTrainValue(TRAINLIST& train_list);
void displayTrainValue(TRAINLIST train_list);
Status outputTrainList(TRAINLIST train_list, char filename[MAX_ARRAY_SIZE]);
Status displayTrainList(TRAINLIST train_list);
Status displayTrainByIndex(TRAINLIST train_list, int* index);
Status displayTrainByIndex(TRAINLIST train_list, int* index);
Status deleteTrainList(TRAINLIST train_list);