//NAME - Shubrojyoti Karmakar
//ROLL - 17CS8016
//ASSIGNMENT 2.4

#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int main(void)
{
	pid_t x,y;
	
	int i=0,j=0,n=0;
	FILE *f=fopen("data.txt","w"),*f1=NULL,*f2=NULL,*f3=NULL,*f4=NULL;
	for(i=0;i<10000;++i)			//inserting 10,000 random digits to a file
	{
		fprintf(f,"%d\n",(rand()%1000)+1);
	}
	fclose(f);
	f=fopen("data.txt","a");
	int last=ftell(f)-1;				//getting the file size
	fclose(f);
	clock_t sp,ep,sc[4],ec[4];			//clock variable
	int ca=0,cb=0,cc=0,cd=0,pp=0;
	int key=0;
	int s[4]={0,last/4,(2*last)/4,(3*last)/4};			//start valid file pointer value for each quarter
	int F[4]={last/4,(2*last)/4,(3*last)/4,last};			//end valid file pointer value for each quarter
	printf("Enter the key to be searched for among 10,000 random numbers - ");
	scanf("%d",&key);
	x=fork();
	if(x==0)				//1st child searches first quarter
	{
		f1=fopen("data.txt","r");
		fseek(f1,s[0],SEEK_SET);
		sc[0]=clock();
		while(ftell(f)<=F[0])
		{
			fscanf(f,"%d\n",&n);
			if(n==key)
			{
				ca++;
			}
		}
		ec[0]=clock();
		fclose(f1);
		printf("child 1 count = %d time taken = %f\n",ca,((double)ec[0]-(double)sc[0])/CLOCKS_PER_SEC);		//1st child's count
	}
	else
	{
		x=fork();
		if(x==0)				//2nd child searches second quarter
		{
			f2=fopen("data.txt","r");
			fseek(f2,s[1],SEEK_SET);
			sc[1]=clock();
			while(ftell(f)<=F[1])
			{
				fscanf(f,"%d\n",&n);
				if(n==key)
				{
					cb++;
				}
			}
			ec[1]=clock();
			fclose(f2);
			printf("child 2 count = %d time taken = %f\n",cb,((double)ec[1]-(double)sc[1])/CLOCKS_PER_SEC);		//2nd child's count
		}
		else
		{
			x=fork();
			if(x==0)				//3rd child searches 3rd quarter
			{
				f3=fopen("data.txt","r");
				fseek(f3,s[2],SEEK_SET);
				sc[2]=clock();
				while(ftell(f)<=F[2])
				{
					fscanf(f,"%d\n",&n);
					if(n==key)
					{
						cc++;
					}
				}
				ec[2]=clock();
				fclose(f3);
				printf("child 3 count = %d time taken = %f\n",cc,((double)ec[2]-(double)sc[2])/CLOCKS_PER_SEC);		//3rd child's count
			}
			else
			{
				x=fork();
				if(x==0)				//4th child searches 4th quarter
				{
					f4=fopen("data.txt","r");
					fseek(f4,s[3],SEEK_SET);
					sc[3]=clock();
					while(ftell(f)<=F[3])
					{
						fscanf(f,"%d\n",&n);
						if(n==key)
						{
							cd++;
						}
					}
					ec[3]=clock();
					fclose(f4);
					printf("child 4 count = %d time taken = %f\n",cd,((double)ec[3]-(double)sc[3])/CLOCKS_PER_SEC);		//4th child's count
				}
				else
				{
					f=fopen("data.txt","r");
					sp=clock();
					while(!feof(f))
					{
						fscanf(f,"%d\n",&n);
						if(n==key)
						{
							pp++;
						}
					}
					ep=clock();
					printf("parent count = %d time taken = %f\n",pp,((double)ep-(double)sp)/CLOCKS_PER_SEC);		//parent's count
					fclose(f);
				}
			}
		}
	}
	return 0;
}
