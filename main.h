#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
typedef struct movies{	//���ݽ��
	int MoviesId;
	float score;
	char time[15];
	struct movies* next;
}movies;
typedef struct users{	//�û���㣬ָ�����ݽ��
	int UserId;
	movies * M;
	float avrage;
}users;
typedef struct buff{	//������¼ǰ20��������
	users user;
	float average;
}buff;
int ReadData(FILE *fp,users *TempUser,users* last_user);
void insertItem(users *u,movies* p);
void findsource(FILE *p,int UserId,users* last_user);
float compute_related(users main_user,users user);
void save_max(float x,buff Buff[],users TempUser);
void destroy(movies* p);
void show_related(buff Buff[]);
float compute_recommend(users main_user,buff Buff[],int n);
float findItem(movies* p,int n);
void show_rate(int max,int r);