#include"main.h"
/*推荐系统导论第一次作业
  使用协同过滤方法推荐评分问题
  Lyy 2018-03-06
  */

// 使用协同过滤一般方法
// 使用动态链表

int main(){
	//begianing
	buff Buff[20];	//	存储20个最相关的用户节点
	FILE * fp;		//	文件指针
	users main_user;//要预测的用户评分行为
	users TempUser;	//对每个用户进行相关性计算的缓存变量
	int i;
	users last_user;movies temp;//针对文件定位困难问题设置每个用户的一个元素
	float x=0;
	//*************初始化***************************
	last_user.UserId=0;
	last_user.M=&temp;
	last_user.M->next=NULL;
	fp=NULL;
	fp = fopen("u1.base","r");
	if(fp==NULL)
		return 1;
	for(i=0;i<20;i++)
	{
		Buff[i].average=-1;
		Buff[i].user.M=NULL;
	}
	main_user.M=NULL;
	main_user.UserId=405;//必须非 1
	findsource(fp,main_user.UserId,&last_user);//指针定位
	ReadData(fp,&main_user,&last_user);//读取数据
	//fseek(fp,0,0);//指针归位
	fclose(fp);
	fp = fopen("u1.base","r");
	//**********************************************
	//**************计算相关度**********************
	last_user.UserId=1;
	printf("计算相关度:\n");
	for(i=0;!feof(fp);)
	{
		i++;	//放这里防止continue;使i不在加一
		TempUser.UserId=i;
		TempUser.M=NULL;
		ReadData(fp,&TempUser,&last_user);
		if(i==main_user.UserId)
			continue;
		x = compute_related(main_user,TempUser);
		if(x==1)
			printf("has problem");
		save_max(x,Buff,TempUser);
		show_rate(943,TempUser.UserId);
		//show_related(Buff);
		//存储
	}
	putchar('\n');
	show_related(Buff);
	fclose(fp);

	//推荐计算
	//2018-03-08
	x=compute_recommend(main_user,Buff,288);
	if(x==-1)
		printf("\n最相关的没有288这一项");
	else
		printf("\n预测结果是405 用户对 288 评分为： %f",x);
	for(i=0;i<20;i++)
	{
		destroy(Buff[i].user.M);
		Buff[i].user.M=NULL;
	}
	putchar('\n');
	system("pause");
}