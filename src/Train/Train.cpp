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
	    cout << "�޷����ļ�";
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
	//����������˳���д��filename�����ļ�����
	ofstream outFile(filename, ios::out); //���ı�ģʽ��filename�ı���д
	if(!outFile)
	{
		cout << "д�ļ�ʧ��" << endl;
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
	cout << "Ŀǰ����" << train_num << "������" << endl;
	//cout << "����ĸ�ʽ�����ǣ����� ʼ��վ �յ�վ ���о��� ������� ����ʱ�� ����ʱ�� ͣ����վ���� �ص������� һ�������� ���������� ��ͣ��վ���� ��վʱ�� ��վʱ�� ���" << endl;
    cout << setiosflags(ios::left) << setw(6) << "����" << "|" << setw(8) << "ʼ��վ" << "|" << setw(8) << "�յ�վ" << "|" << setw(12) << "���о���" << "|" << setw(12) << "�������" << "|"
     << setw(12) << "����ʱ��" << "|" << setw(12) << "����ʱ��" << "|" << setw(16) << "ͣ����վ����" << "|" << setw(12) << "�ص�������" << "|" << setw(12) << "һ��������" << "|" 
     << setw(12) << "����������" << "|" << setw(16) << "��ͣ��վ����" << "|" << setw(12) << "��վʱ��" << "|" << setw(12) << "��վʱ��" << "|" << setw(6) << "���" << endl;
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
	cout << setiosflags(ios::left) << setw(6) << "����" << "|" << setw(8) << "ʼ��վ" << "|" << setw(8) << "�յ�վ" << "|" << setw(12) << "���о���" << "|" << setw(12) << "�������" << "|"
     << setw(12) << "����ʱ��" << "|" << setw(12) << "����ʱ��" << "|" << setw(16) << "ͣ����վ����" << "|" << setw(12) << "�ص�������" << "|" << setw(12) << "һ��������" << "|" 
     << setw(12) << "����������" << "|" << setw(16) << "��ͣ��վ����" << "|" << setw(12) << "��վʱ��" << "|" << setw(12) << "��վʱ��" << "|" << setw(6) << "���" << endl;
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











