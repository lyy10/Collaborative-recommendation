#include"main.h"
/*�Ƽ�ϵͳ���۵�һ����ҵ
  ʹ��Эͬ���˷����Ƽ���������
  Lyy 2018-03-06
  */

// ʹ��Эͬ����һ�㷽��
// ʹ�ö�̬����

int main(){
	//begianing
	buff Buff[20];	//	�洢20������ص��û��ڵ�
	FILE * fp;		//	�ļ�ָ��
	users main_user;//ҪԤ����û�������Ϊ
	users TempUser;	//��ÿ���û���������Լ���Ļ������
	int i;
	users last_user;movies temp;//����ļ���λ������������ÿ���û���һ��Ԫ��
	float x=0;
	//*************��ʼ��***************************
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
	main_user.UserId=405;//����� 1
	findsource(fp,main_user.UserId,&last_user);//ָ�붨λ
	ReadData(fp,&main_user,&last_user);//��ȡ����
	//fseek(fp,0,0);//ָ���λ
	fclose(fp);
	fp = fopen("u1.base","r");
	//**********************************************
	//**************������ض�**********************
	last_user.UserId=1;
	printf("������ض�:\n");
	for(i=0;!feof(fp);)
	{
		i++;	//�������ֹcontinue;ʹi���ڼ�һ
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
		//�洢
	}
	putchar('\n');
	show_related(Buff);
	fclose(fp);

	//�Ƽ�����
	//2018-03-08
	x=compute_recommend(main_user,Buff,288);
	if(x==-1)
		printf("\n����ص�û��288��һ��");
	else
		printf("\nԤ������405 �û��� 288 ����Ϊ�� %f",x);
	for(i=0;i<20;i++)
	{
		destroy(Buff[i].user.M);
		Buff[i].user.M=NULL;
	}
	putchar('\n');
	system("pause");
}