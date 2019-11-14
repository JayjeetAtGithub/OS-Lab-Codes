//NAME - Shubrojyoti Karmakar
//ROLL - 17CS8016
//ASSIGNMENT 5.1

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
	pid_t store[n],x;
	for(int i=0;i<n;++i)
	{
		x=store[i]=fork();
		if(store[i]==0)
		{
			
			
				printf("i am alive my process id is %d my parent process id is %d value returned - %d\n",getpid(),getppid(),i);
				exit(i);
			
			break;
		}
	}
	
	if(x!=0)
	{
		pid_t max=0;
		for(int i=0;i<n;++i)
		{
			if(store[i]>=max)
			{
				max=store[i];
			}
		}
		//sleep(1);
		int l=0;
		x=waitpid(max,&l,0);
		printf("\nhighest pid is - %d, syncing with it\n",max);
		printf("\nvalue returnned - %d\n",l);
		for(int i=0;i<n;++i)
		{
			printf("\nkilling child -%d\n",store[i]);
			kill(store[i],SIGINT);
		}
		return 0;
	}
}
