//相关的函数
#include"main.h"
#include<windows.h>
int ReadData(FILE *fp,users *TempUser,users* last_user){
	int user;
	movies* tempMovies=NULL;
	float num=0,n=0;	//	计算平均值
	if(feof(fp))//为1时，文件结束
		return 1;
	if(last_user->UserId!=1)//用户为1的不需要使用
	{
		//TempUser->UserId=last_user->UserId;
		tempMovies=(movies *)malloc(sizeof(movies));
		*tempMovies=*(last_user->M);
		tempMovies->next=NULL;
		TempUser->M=tempMovies;
		tempMovies=NULL;
		num=TempUser->M->score;
		n++;
	}
	
	for(;1;)
	{
		if(feof(fp))//为1时，文件结束
			break;
		//*fp=p;
		fscanf(fp,"%d",&user);
		if(user==TempUser->UserId)
		{
			n++;
			tempMovies=(movies *)malloc(sizeof(movies));//申请一个项目打分项
			if(tempMovies==NULL)
				return -1;
			fscanf(fp,"%d%f%s\n",&tempMovies->MoviesId,&tempMovies->score,&tempMovies->time);
			tempMovies->next=NULL;
			num+=tempMovies->score;
			insertItem(TempUser,tempMovies);	//插入并根据项目序号经行排序
			tempMovies=NULL;
		}
		else{
			last_user->UserId=user;
			fscanf(fp,"%d%f%s\n",&last_user->M->MoviesId,&last_user->M->score,&last_user->M->time);
			break;
		}
	}
	TempUser->avrage=num/n;
	return 0;
}

void insertItem(users *u,movies* p){
	//插入一个项目打分
	movies *head;
	movies *next;
	if(u->M==NULL)
	{
		u->M=p;
		return;
	}
	if(u->M->MoviesId > p->MoviesId)
		{	p->next=u->M;
			u->M=p;return;}
	head=u->M;
	next=head->next;
	while(next!=NULL)
	{
		if(next->MoviesId > p->MoviesId)
		{
			p->next=next;
			head->next=p;
			return;
		}
		head=next;
		next=next->next;
	}
	head->next=p;

}

//输出进度选项
//Lyy 2018-03-08
void show_rate(int max,int r){
	int i,j;
	float n;
	int s;
	COORD coord = {0, 1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	n=((float)r)/((float)max);
	s=(int)(n*100);
	putchar('[');
	j=s/5;
	for(i=1;i<=j;i++)
		printf("#");
	j=20-j;
	for(i=1;i<=j;i++)
		printf(" ");//putchar(' ');
	printf("]");//putchar(']');
	printf("[%d%%]",s);

}