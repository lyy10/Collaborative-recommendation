#include"main.h"

void findsource(FILE *p,int UserId,users* last_user){
	//fpos_t home;//保存一个文件指针的位置
	int ID;
	while(!feof(p))
	{
		//fgetpos(p,&home);
		//num=ftell(p)-i;
		fscanf(p,"%d",&ID);
		if(ID==UserId)
		{
			//if(!(fsetpos(p,&home)));
			//printf("chenggongle");
			//fseek(p,num,0);
			//fscanf(p,"%d",&ID);
			//printf("\n%d",ID);
			last_user->UserId=ID;
			fscanf(p,"%d%f%s\n",&last_user->M->MoviesId,&last_user->M->score,&last_user->M->time);
			return;
		}

		fscanf(p,"%d%f%s\n",&last_user->M->MoviesId,&last_user->M->score,&last_user->M->time);
		//printf("%d    %d     %f    %s\n",ID,x,y,z);

	}
	
	/*num=ftell(p);
	printf("%d\n",num);
	fseek(p,462,0);
	num=ftell(p);
	printf("%d\n",num);
	fscanf(p,"%d",&ID);
	num=ftell(p);
	printf("%d\n",num);
	fseek(p,-1,1);
	num=ftell(p);
	printf("%d\n",num);
	fscanf(p,"%d",&ID);
	fscanf(p,"::%d::%f::%s\n",&x,&y,z);
	printf("%d    %d     %f    %s\n",ID,x,y,z);*/

}