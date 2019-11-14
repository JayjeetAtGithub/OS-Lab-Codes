//NAME - Shubrojyoti Karmakar
//ROLL - 17CS8016
//ASSIGNMENT 5.2.3

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
		if(x==0)
		{
			break;
		}
		else
		{
			if(i==1)
			{
				nice(10);
			}
		}
	}
	int j=10;
	while(j)
	{
		j--;
		
		FILE *f=fopen("hello.txt","w");
		fclose(f);
		f=fopen("hello.txt","w");
		fclose(f);
		f=fopen("hello.txt","w");
		fclose(f);
		f=fopen("hello.txt","w");
		fclose(f);
		printf("PID - %d, PPID - %d GRPID - %d priority - %d\n",getpid(),getppid(),getpgrp(),getpriority(0,0));
	}
	wait();
	return 0;
}
