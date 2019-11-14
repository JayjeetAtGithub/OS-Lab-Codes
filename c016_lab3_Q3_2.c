//NAME - Shubrojyoti Karmakar
//ROLL - 17CS8016
//ASSIGNMENT 3.2

#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<signal.h>
pid_t x[100],y;
int n;
void f1(int xx)
{
	for(int i=0;i<n;++i)
	{
		printf("killing child %d\n",x[i]);
		kill(x[i],SIGINT);
	}
}
int main(void)
{
	signal(SIGUSR1,f1);
	int i=0,j=0;
	FILE *f=fopen("data.txt","w");
	
	
	for(i=0;i<10000;++i)			//inserting 10,000 random digits to a file
	{
		fprintf(f,"%d\n",(rand()%1000)+1);
	}
	fclose(f);
	
	
	f=fopen("data.txt","a");
	int last=ftell(f)-1;				//getting the file size
	fclose(f);
	
	
	int pp=0;
	int key=0;
	
	printf("Enter the number of child - ");
	scanf("%d",&n);
	
	int cc[n];
	clock_t sp,ep,sc[n],ec[n];			//clock variable
	int step=last/n;
	int s[n];			//start valid file pointer value for each division
	int F[n];			//end valid file pointer value for each division
	FILE *f1[n];
	s[0]=0;
	F[0]=step;
	cc[0]=0;
	f1[0]=NULL;
	for(i=1;i<n;++i)
	{
		cc[i]=0;
		f1[i]=NULL;
		s[i]=F[i-1];
		F[i]=F[i-1]+step;
	}
	
	printf("Enter the key to be searched for among 10,000 random numbers - ");
	scanf("%d",&key);
	int flag=0;
	
	for(i=0;i<n;++i)
	{
		x[i]=fork();
		if(x[i]==0)						//ith child for ith part of file
		{
			flag=0;
			f1[i]=fopen("data.txt","r");
			fseek(f1[i],s[i],SEEK_SET);
			sc[i]=clock();
			while(ftell(f1[i])<=F[i])
			{
				fscanf(f1[i],"%d\n",&n);
				if(n==key)
				{
					printf("found value in child %d, sending parent signal to kill all childrens\n",getpid());
					cc[i]++;
					kill(getppid(),SIGUSR1);
				}
			}
			ec[i]=clock();
			fclose(f1[i]);
			printf("child %d count = %d time taken = %f\n",i+1,cc[i],((double)ec[i]-(double)sc[i])/CLOCKS_PER_SEC);
			break;
		}
		else
		{
			flag=1;
		}
	}
	if(flag==1)
	{
		sleep(1);
	}
	return 0;
}
