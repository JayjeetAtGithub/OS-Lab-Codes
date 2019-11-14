//NAME - Jayjeet Chakraborty
//ROLL - 17CS8036
//ASSIGNMENT 7.1

#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include<signal.h>
#define MAX_SIZE 4096

int main (void)
{
	signal(SIGCHLD,SIG_IGN);
	int segment_id = shmget(IPC_PRIVATE, sizeof(int), S_IRUSR | S_IWUSR);
	int *shared_memory = (int*)shmat(segment_id, NULL, 0);
	//sprintf(shared_memory, "IPC using shared memory");
	pid_t pid;
	*shared_memory=1;
	int n;
	printf("Initial value - %d\n",*shared_memory);
	printf("Enter the number of childs you want to create - ");
	scanf("%d",&n);
	for(int i=0;i<n;++i)
	{
		pid=fork();
		if(pid==0)
		{
			*shared_memory=*shared_memory+1;
			shmdt(shared_memory);
			break;
		}
	}
	if(pid != 0)
	{
		int w;
		wait(&w);
		printf("expected final value = %d\nfinal value after all child have executed - %d\n",n+1,*shared_memory);
		shmdt(shared_memory);
		shmctl(segment_id, IPC_RMID, NULL);
	}
	return 0;
}
