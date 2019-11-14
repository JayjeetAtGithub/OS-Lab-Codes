//NAME - Shubrojyoti Karmakar
//ROLL - 17CS8016
//ASSIGNMENT 2.1

#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
int main(void)						//multiple child
{
	pid_t x;
	int i=0;
	printf("parent - my parent id is = %d\n",getppid());
	printf("hello\n");
	for(i=0;i<100;++i)
	{
		x=fork();
		if(x==0)
		{
			//sleep(50);
			printf("parent id = %d, my id = %d, child's id = %d ",getppid(),getpid(),x);
			if(getpid()%2)
			{
				printf("odd\n");
			}
			else
			{
				printf("even\n");
			}
			break;
		}
	}
	if(x!=0)
	{
	//sleep(500);		
	printf("bye\n");
	}

	return 0;
}
