#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#include "Train.h"
#define MAX_ARRAY_SIZE 50


using namespace std;


Status setTrainValue(TRAINLIST& train_list){
    PTRAIN p = train_list.elem;
    TRAINVALUE* q = &train_list.train_value;
    if(!q || !p) return ERROR;
	q->stop_names = (PSTOPNAME)malloc(train_list.train_num * sizeof(STOPNAME));
    for(int i = 0; i < train_list.train_num; i++){
        strcpy(q->name[i], p->name);
        strcpy(q->origin[i], p->origin);
        strcpy(q->destination[i], p->destination);
        strcpy(q->status[i], p->status);
        strcpy(q->departure_time[i], p->departure_time);
        strcpy(q->arrival_time[i], p->arrival_time);
		for(int j = 0; j < p->stop_num; j++){
			strcpy(q->stop_names[i].stop_names[j], p->stop_names[j]);
		}
        p++;
    }
    return OK;
}

void displayTrainValue(TRAINLIST train_list){
    for(int i = 0; i < train_list.train_num; i++){
        cout << train_list.train_value.name[i] << " ";
		cout << train_list.train_value.origin[i] << " ";
		cout << train_list.train_value.destination[i] << " ";
		cout << train_list.train_value.status[i] << " ";
		cout << train_list.train_value.departure_time[i] << " ";
		cout << train_list.train_value.arrival_time[i] << " ";
		for(int j = 0; j < train_list.elem[i].stop_num; j++)
		{
			cout << train_list.train_value.stop_names[i].stop_names[j] << " ";
		}
		cout << endl;
    }
}

Status initTrainList(TRAINLIST& train_list, int train_num){
	PTRAIN p = (PTRAIN)malloc(train_num * sizeof(TRAIN));
    if(!p) return ERROR;
	train_list.elem = p;
	train_list.train_num = train_num;
	return OK;
}

Status inputTrainList(TRAINLIST& train_list, char filename[MAX_ARRAY_SIZE]){
	//char file[50];
	float num;
	int train_num;
	ifstream inFile;
	inFile.open(filename);
	if (!inFile) {
	    cout << "无法打开文件";
	    exit(1); // terminate with error
	}
	inFile >> train_num;
	initTrainList(train_list, train_num);
	PTRAIN p = train_list.elem;
	
	for(int i = 0; i < train_num; i++){
		inFile >> p->name
		>> p->origin
		>> p->destination
		>> p->distance
		>> p->status
		>> p->departure_time
		>> p->arrival_time
		>> p->stop_num
		>> p->special_class
		>> p->first_class
		>> p->second_class;
		for(int j = 0; j < p->stop_num; j++){
            inFile >> p->stop_names[j]
            >> p->stop_arrival_time[j]
            >> p->stop_departure_time[j]
            >> p->stop_distance[j];
		}
		p++;
	}
	inFile.close();
	setTrainValue(train_list);
	return OK;
}

Status outputTrainList(TRAINLIST train_list, char filename[MAX_ARRAY_SIZE]){
	//将高铁车次顺序表写入filename所在文件夹下
	ofstream outFile(filename, ios::out); //以文本模式打开filename文本备写
	if(!outFile)
	{
		cout << "写文件失败" << endl;
		return ERROR;
	}
	int train_num = train_list.train_num;
	PTRAIN p = train_list.elem;
	outFile << train_num << endl;
	for(int i = 0; i < train_num; i++){
		
		outFile << p->name << " "
		<< p->origin << " "
		<< p->destination << " "
		<< p->distance << " "
		<< p->status << " "
		<< p->departure_time << " "
		<< p->arrival_time << " "
		<< p->stop_num << " "
		<< p->special_class << " "
		<< p->first_class << " "
		<< p->second_class << " ";
		for(int j = 0; j < p->stop_num; j++){
			outFile << p->stop_names[j] << " "
			<< p->stop_arrival_time[j] << " "
			<< p->stop_departure_time[j] << " "
			<< p->stop_distance[j] << " ";
		}
		if(i != train_num - 1)
			outFile << endl;
		p++;
	}
	
	outFile.close();
	return OK;
}

Status displayTrainList(TRAINLIST train_list){
	PTRAIN p = train_list.elem;
	if(!p) return ERROR;
	int train_num = train_list.train_num;
	cout << "目前共有" << train_num << "个车次" << endl;
	//cout << "输出的格式依次是：车次 始发站 终到站 运行距离 运行情况 发车时间 到达时间 停靠车站数量 特等座数量 一等座数量 二等座数量 各停靠站名称 进站时间 出站时间 里程" << endl;
    cout << setiosflags(ios::left) << setw(6) << "车次" << "|" << setw(8) << "始发站" << "|" << setw(8) << "终到站" << "|" << setw(12) << "运行距离" << "|" << setw(12) << "运行情况" << "|"
     << setw(12) << "发车时间" << "|" << setw(12) << "到达时间" << "|" << setw(16) << "停靠车站数量" << "|" << setw(12) << "特等座数量" << "|" << setw(12) << "一等座数量" << "|" 
     << setw(12) << "二等座数量" << "|" << setw(16) << "各停靠站名称" << "|" << setw(12) << "进站时间" << "|" << setw(12) << "出站时间" << "|" << setw(6) << "里程" << endl;
	for(int i = 0; i < train_num; i++){
        cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << setiosflags(ios::left) << setw(6) << p->name << "|";
		cout << setiosflags(ios::left) << setw(8) << p->origin << "|";
		cout << setiosflags(ios::left) << setw(8) << p->destination << "|";
		cout << setiosflags(ios::left) << setw(12) << p->distance << "|";
		cout << setiosflags(ios::left) << setw(12) << p->status << "|";
		cout << setiosflags(ios::left) << setw(12) << p->departure_time << "|";
		cout << setiosflags(ios::left) << setw(12) << p->arrival_time << "|";
		cout << setiosflags(ios::left) << setw(16) << p->stop_num << "|";
		cout << setiosflags(ios::left) << setw(12) << p->special_class << "|";
		cout << setiosflags(ios::left) << setw(12) << p->first_class << "|";
		cout << setiosflags(ios::left) << setw(12) << p->second_class << "|";
		for(int j = 0; j < p->stop_num; j++){
            if(j != 0)
            {
                cout << setiosflags(ios::left) << setw(6) << " " << "|";
		        cout << setiosflags(ios::left) << setw(8) << " " << "|";
		        cout << setiosflags(ios::left) << setw(8) << " " << "|";
		        cout << setiosflags(ios::left) << setw(12) << " " << "|";
		        cout << setiosflags(ios::left) << setw(12) << " " << "|";
		        cout << setiosflags(ios::left) << setw(12) << " " << "|";
		        cout << setiosflags(ios::left) << setw(12) << " " << "|";
		        cout << setiosflags(ios::left) << setw(16) << " " << "|";
		        cout << setiosflags(ios::left) << setw(12) << " " << "|";
		        cout << setiosflags(ios::left) << setw(12) << " " << "|";
		        cout << setiosflags(ios::left) << setw(12) << " " << "|";
            }
			cout << setiosflags(ios::left) << setw(16) << p->stop_names[j] << "|";
			cout << setiosflags(ios::left) << setw(12) << p->stop_arrival_time[j] << "|";
			cout << setiosflags(ios::left) << setw(12) << p->stop_departure_time[j] << "|";
			cout << setiosflags(ios::left) << setw(6) << p->stop_distance[j];
            cout << endl;
		}
		
		p++;
	}
	cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	return OK;
}

Status displayTrainByIndex(TRAINLIST train_list, int* index){
	PTRAIN p = train_list.elem;
	if(!p || index[0] == -1) return ERROR;
	p += index[0];
	cout << setiosflags(ios::left) << setw(6) << "车次" << "|" << setw(8) << "始发站" << "|" << setw(8) << "终到站" << "|" << setw(12) << "运行距离" << "|" << setw(12) << "运行情况" << "|"
     << setw(12) << "发车时间" << "|" << setw(12) << "到达时间" << "|" << setw(16) << "停靠车站数量" << "|" << setw(12) << "特等座数量" << "|" << setw(12) << "一等座数量" << "|" 
     << setw(12) << "二等座数量" << "|" << setw(16) << "各停靠站名称" << "|" << setw(12) << "进站时间" << "|" << setw(12) << "出站时间" << "|" << setw(6) << "里程" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	for(int i = 0; index[i] != -1; i++){
		cout << setiosflags(ios::left) << setw(6) << p->name << "|";
		cout << setiosflags(ios::left) << setw(8) << p->origin << "|";
		cout << setiosflags(ios::left) << setw(8) << p->destination << "|";
		cout << setiosflags(ios::left) << setw(12) << p->distance << "|";
		cout << setiosflags(ios::left) << setw(12) << p->status << "|";
		cout << setiosflags(ios::left) << setw(12) << p->departure_time << "|";
		cout << setiosflags(ios::left) << setw(12) << p->arrival_time << "|";
		cout << setiosflags(ios::left) << setw(16) << p->stop_num << "|";
		cout << setiosflags(ios::left) << setw(12) << p->special_class << "|";
		cout << setiosflags(ios::left) << setw(12) << p->first_class << "|";
		cout << setiosflags(ios::left) << setw(12) << p->second_class << "|";
		for(int j = 0; j < p->stop_num; j++){
    	    if(j != 0)
    	    {
    	        cout << setiosflags(ios::left) << setw(6) << " " << "|";
		        cout << setiosflags(ios::left) << setw(8) << " " << "|";
		        cout << setiosflags(ios::left) << setw(8) << " " << "|";
		        cout << setiosflags(ios::left) << setw(12) << " " << "|";
		        cout << setiosflags(ios::left) << setw(12) << " " << "|";
		        cout << setiosflags(ios::left) << setw(12) << " " << "|";
		        cout << setiosflags(ios::left) << setw(12) << " " << "|";
		        cout << setiosflags(ios::left) << setw(16) << " " << "|";
		        cout << setiosflags(ios::left) << setw(12) << " " << "|";
		        cout << setiosflags(ios::left) << setw(12) << " " << "|";
		        cout << setiosflags(ios::left) << setw(12) << " " << "|";
    	    }
			cout << setiosflags(ios::left) << setw(16) << p->stop_names[j] << "|";
			cout << setiosflags(ios::left) << setw(12) << p->stop_arrival_time[j] << "|";
			cout << setiosflags(ios::left) << setw(12) << p->stop_departure_time[j] << "|";
			cout << setiosflags(ios::left) << setw(6) << p->stop_distance[j];
    	    cout << endl;
		}
		cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		p = train_list.elem;
		p += index[i+1];
		
	}
	return OK;
}

Status deleteTrainList(TRAINLIST train_list){
	free(train_list.elem);
	return OK;
}











