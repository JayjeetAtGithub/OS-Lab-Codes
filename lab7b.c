//NAME - Jayjeet Chakraborty
//ROLL - 17CS8036
//ASSIGNMENT 7.2

#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include<stdlib.h>
#include<time.h>
#include<signal.h>
#define MAX_SIZE 4096

int main (void)
{
	srand(time(NULL));
	signal(SIGCHLD,SIG_IGN);
	int n;
	printf("Enter the number of steps - ");
	scanf("%d",&n);
	n=n*2;
	int segment_id = shmget(IPC_PRIVATE, sizeof(int)*n, S_IRUSR | S_IWUSR);
	int *shared_memory = (int*)shmat(segment_id, NULL, SHM_RND);
	//sprintf(shared_memory, "IPC using shared memory");
	pid_t pid;
	for(int i=0;i<n;++i)
	{
		shared_memory[i]=0;
	}
	int i=0;
	pid=fork();
	while(i<n)
	{
		if(pid==0)
		{
			if(i%2)
			{
				while(shared_memory[i-1]==0)
				{
					printf("lol\n");
				}
				shared_memory[i]=shared_memory[i-1]+100;
				++i;
			}
			else
				++i;
		}
		if(pid)
		{
			if(i%2==0)
			{
				shared_memory[i]=rand()%100+1;
				++i;
			}
			else
			{
				++i;
			}
		}
	}
	if(pid==0)
	{
		int sum=0;
		for(int j=0;j<n;j+=2)
		{
			sum+=shared_memory[j];
		}
		printf("\nChild calculating sum of parent cells - %d\n",sum);
	}
	if(pid!=0)
	{
		int w;
		wait(&w);
		int sum=0;
		for(int j=1;j<n;j+=2)
		{
			sum+=shared_memory[j];
		}
		printf("\nParent calculating sum of child cells - %d\n",sum);
		printf("\ncontent of array is follows\n");
		for(int i=0;i<n;++i)
		{
			printf("%d ",shared_memory[i]);
		}
		printf("\n");
		shmdt(shared_memory);
		shmctl(segment_id, IPC_RMID, NULL);
	}
	return 0;
}
