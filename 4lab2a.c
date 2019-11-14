//NAME - Shubrojyoti Karmakar
//ROLL - 17CS8016
//ASSIGNMENT 4.2.1

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
	pid_t x,z;
	int y;
	for(int i=1;i<=10;++i)
	{
		x=fork();
		if(x==0)
		{
			if(i%2)
			{
				setpgrp();
			}
			printf("i=%d, parent id = %d, my id = %d, group id = %dreturnning %d\n",i,getppid(),getpid(),getpgrp(),i+1);
			exit(i+1);
		}
	}
	if(x!=0)
	{
		z=wait(&y);
		sleep(1);
		printf("child %d sent %d",z,y);
	}
	return 1;
}
