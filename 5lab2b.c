//NAME - Shubrojyoti Karmakar
//ROLL - 17CS8016
//ASSIGNMENT 5.2.2

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<signal.h>

int main()
{
	int n;
	printf("Enter the number of child to be created - ");
	scanf("%d",&n);
	pid_t x;
	for(int i=0;i<n;++i)
	{
		x=fork();
		if(x!=0)
		{
			break;
		}
		else
		{
			if(i==1)
				setpgrp();
		}
	}
	//wait();
	int j=10;
	while(j)
	{
		j--;
		//sleep(0.1);
		FILE *f=fopen("hello.txt","w");
		fclose(f);
		f=fopen("hello.txt","w");
		fclose(f);
		f=fopen("hello.txt","w");
		fclose(f);
		f=fopen("hello.txt","w");
		fclose(f);
		printf("PID - %d, PPID - %d GRPID - %d\n",getpid(),getppid(),getpgrp());
	}
	wait();
	return 0;
}
