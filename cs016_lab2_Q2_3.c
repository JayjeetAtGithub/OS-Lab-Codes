//NAME - Shubrojyoti Karmakar
//ROLL - 17CS8016
//ASSIGNMENT 2.3

#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
int main(void)						//conditioned child generation
{
	pid_t x,y;
	int i=0,j=0,n=0;
	//printf("parent - my parent id is = %d\n",getppid());
	printf("enter the no of levels - ");
	scanf("%d",&n);
	printf("//parent// parent id = %d, my id = %d\n",getppid(),getpid());
	
	for(i=0;i<n-1;++i)
	{
		x=fork();
		if(x!=0)			//parent breaks out
		{
			break;
		}
		if(x==0)				//conditions for child
		{
			printf("//child// parent id = %d, my id = %d\n",getppid(),getpid());
			if(getpid()%5==0)			//no further child created if child id %5==0
			{
				break;
			}
			else
			{
				if(getpid()%2)			//if child id is odd then continue for further creation
				{
					continue;
				}
				else
				{				//even child id creates 2 child of itself
					y=fork();
					if(y==0)
					{
						printf("//child// parent id = %d, my id = %d\n",getppid(),getpid());
						++i;
					}
				}
			}
		}
	}
	if(x!=0)
	{
		sleep(1);
	}
	return 0;
}
