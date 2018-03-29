#include"main.h" 
#include<math.h>

//计算两个用户的相关度,只有相同项目参与运算
//*****2018-03-07  Lyy
float compute_related(users main_user,users user){
	movies *main;
	movies *u;
	float sum1=0;
	float sum2=0;
	float sum3=0;
	float sim=0;
	float Ra;
	float Rb;
	int i=0;
	//************初始化*********
	Ra=main_user.avrage;
	Rb=user.avrage;
	main=main_user.M;
	u=user.M;
	//***********找相同的计算相关度*********
	while(main!=NULL&&u!=NULL)
	{
		
		if(main->MoviesId==u->MoviesId)
		{
			sum1+=(main->score-Ra)*(u->score-Rb);
			sum2+=(main->score-Ra)*(main->score-Ra);
			sum3+=(u->score-Rb)*(u->score-Rb);
			main=main->next;	//不得让其无限循环
			u=u->next;
			i++;
		}
		else if(main->MoviesId > u->MoviesId)
			u=u->next;
		else
			main=main->next;
	}

	if(sum2==0||sum3==0||i<21)
		return -1;
	sum2=sqrt(sum2);
	sum3=sqrt(sum3);
	sim=sum1/(sum2*sum3);
	return (float)sim;
}

//存储前20名相关度最高的用户信息，其余的进行内存回收
//Lyy  2018-03-07
void save_max(float x,buff Buff[],users TempUser){
	int i;
	if(x<=Buff[0].average)
	{
		destroy(TempUser.M);
		return;
	}
	destroy(Buff[0].user.M);
	for(i=1;i<20;i++)
	{
		if(x<=Buff[i].average)
			break;
		Buff[i-1]=Buff[i];
	}
	Buff[i-1].average=x;
	Buff[i-1].user=TempUser;
	
}

//回收内存
//Lyy 2018-03-07
void destroy(movies* p){
	movies* temp;
	if(p==NULL)
		return;
	temp=p->next;
	while(temp!=NULL)
	{
		free(p);
		p=temp;
		temp=temp->next;
	}
	free(p);
}

void show_related(buff Buff[]){
	int i;
	for(i=0;i<20;i++)
	{
		printf("%d : %f  ",Buff[i].user.UserId,Buff[i].average);
	}
	putchar('\n');

}

//进行推荐计算
//Lyy 2018-03-07
float compute_recommend(users main_user,buff Buff[],int n){
	float sum1=0;
	float sum2=0;
	float r;
	int i;
	float Ra=main_user.avrage;
	float pred=0;
	for(i=0;i<20;i++)
	{
		r=findItem(Buff[i].user.M,n);
		if(r!=-1)
		{
			sum1+=Buff[i].average*(r-Buff[i].user.avrage);
			sum2+=Buff[i].average;
		}
	}
	if(sum1==0)
		return -1;
	return pred = Ra+sum1/sum2;
}

//找用户的某项的评分
//Lyy 2018-03-07
float findItem(movies* p,int n){
	while(p!=NULL)
	{
		if(p->MoviesId==n)
			return p->score;
		p=p->next;
	}
	return -1;
}

