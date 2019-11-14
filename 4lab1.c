//NAME - Shubrojyoti Karmakar
//ROLL - 17CS8016
//ASSIGNMENT 4.1

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<signal.h>
			//creates 10 process and changes odd process group id


int main()
{
	//signal(SIGCHILD,SIG_IGN);
	pid_t x;
	for(int i=1;i<=10;++i)
	{
		x=fork();
		if(x==0)
		{
			if(i%2)
			{
				setpgrp();
			}
			//while(1)
			//{
			//	sleep(1);
				printf("i=%d, parent id = %d, my id = %d, group id = %d\n",i,getppid(),getpid(),getpgrp());
			//}
			break;
		}
	}
	if(x!=0)
	{
		//kill(0,SIGINT);
		wait(NULL);
		sleep(1);
		printf("parent synchronozed whith childen\n");
	}




	return 1;
}
