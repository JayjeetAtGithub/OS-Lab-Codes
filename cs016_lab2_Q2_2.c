//NAME - Shubrojyoti Karmakar
//ROLL - 17CS8016
//ASSIGNMENT 2.2

#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
int main(void)					//multilevel child
{
	pid_t x;
	int i=0,n=0;
	printf("parent - my parent id is = %d\n",getppid());
	printf("enter the no of levels - ");
	scanf("%d",&n);
	printf("parent id = %d, my id = %d\n",getppid(),getpid());
	for(i=0;i<n-1;++i)
	{
		x=fork();
		if(x!=0)			//multilevel
		{
			break;
		}
		printf("parent id = %d, my id = %d\n",getppid(),getpid());
	}
	return 0;
}
