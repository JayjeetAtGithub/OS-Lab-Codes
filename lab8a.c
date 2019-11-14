//NAME - Jayjeet Chakraborty
//ROLL - 17CS8036
//ASSIGNMENT 8.1

#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include<signal.h>
#include<random>
#define MAX_SIZE 4096

int main (void)
{
	srand(time(0));
	//random();
	signal(SIGCHLD,SIG_IGN);
	int segment_id = shmget(IPC_PRIVATE, sizeof(int), S_IRUSR | S_IWUSR);
	int *shared_memory = (int*)shmat(segment_id, NULL, 0);
	//sprintf(shared_memory, "IPC using shared memory");
	pid_t pid;
	printf("Enter the initial value - ");
	scanf("%d",shared_memory);
	int res=*shared_memory;
	//*shared_memory=1;
	int n,k;
	//printf("Initial value - %d\n",*shared_memory);
	printf("Enter the number of childs you want to create - ");
	scanf("%d",&n);
	for(int i=0;i<n;++i)
	{
		k=rand()%10;
		pid=fork();
		if(pid==0)
		{
			if(i%2)
			{
				*shared_memory=*shared_memory-2*k;
				printf("child %d completed updating by %dx(-2), shared memory value is = %d\n",i+1,k,*shared_memory);
				shmdt(shared_memory);
				break;
			}
			else
			{
				*shared_memory=*shared_memory+2*k;
				printf("child %d completed updating by %dx(2), shared memory value is = %d\n",i+1,k,*shared_memory);
				shmdt(shared_memory);
				break;
			
			}
		}
	}
	if(pid != 0)
	{
		int w;
		wait(&w);
		printf("final value after all child have executed - %d\n",*shared_memory);
		shmdt(shared_memory);
		shmctl(segment_id, IPC_RMID, NULL);
	}
	return 0;
}
