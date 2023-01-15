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
	�˽ṹ��Ϊ����������Ϣ���ṹ�壬����������Ҫ��Ϣ
	*/
	char name[MAX_ARRAY_SIZE];			//����
	char origin[MAX_ARRAY_SIZE];		//ʼ����
	char destination[MAX_ARRAY_SIZE];	//�յ���
	int distance;						//���о���
	char status[MAX_ARRAY_SIZE];		//����״̬
	char departure_time[MAX_ARRAY_SIZE];//����ʱ��
	char arrival_time[MAX_ARRAY_SIZE];	//����ʱ��
 	int stop_num;              			//ͣ��վ����
  	int special_class;					//�ص�����������������
  	int first_class;					//һ��������
  	int second_class;					//����������
	char stop_names[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];			//ͣ��վ���ƣ���ά������ʽ����
	char stop_arrival_time[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];		//ͣ��վ��վʱ��
	char stop_departure_time[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];	//ͣ��վ����ʱ��
	float stop_distance[MAX_ARRAY_SIZE];						//��ͣ��վ�������
}TRAIN, *PTRAIN;

typedef struct StopName{
	/*
	�˽ṹ��Ϊ�����ṹ�壬���ڴ��ͣ��վ���ƵĶ�ά���飬���ڲ���ͣ��վ��Ϣ
	*/
	char stop_names[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
}STOPNAME, *PSTOPNAME;

typedef struct TrainValue {
	/*
	�˽ṹ��Ϊ�����ṹ�壬���ڴ�Ÿ��ֶΣ����ڸ����ֶβ�����Ϣ
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
	��ϵͳ����˳�����ʽ��Ÿ���������Ϣ���˽ṹ��Ϊ˳���ṹ��
	*/
	PTRAIN elem; //˳����ͷ
	TRAINVALUE train_value; //�������ҽṹ��
	int train_num;  //��������
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