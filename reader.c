//NAME - Jayjeet Chakraborty
//ROLL - 17CS8036
//ASSIGNMENT 9.2a

//10 readers each read 10 times

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include<signal.h>
#include<sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>
int main()
{
	signal(SIGCHLD,SIG_IGN);
	FILE *f=NULL;
	while(!(f=fopen("lol.txt","r")));
	fclose(f);

    const char * name7 = "shared_memory7";
    const char * sema7="mutex7";
    int shm_fd; //file descriptor of
    int * shelf;
    int loop=2;
    int value;
    int i;
	pid_t x;
    sem_t  * mutex7;
	
	
	const char *countername = "counter";
	const char *cmutx = "cmutex";
	int *counter;
	int count_fd=0;
	sem_t  * rmutex;
	count_fd=shm_open(countername, O_CREAT | O_RDWR,0666);
	ftruncate(count_fd,sizeof(int));
	counter=mmap(0,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,count_fd,0);
	rmutex=sem_open(cmutx,O_CREAT,0666,1);
	
	
	
	
	
	for(i=0;i<10;++i)
	{
		x=fork();
		if(x==0)
		{
			count_fd=shm_open(countername,O_RDWR,0666);
			counter=mmap(0,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,count_fd,0);
			rmutex=sem_open(cmutx,O_EXCL);
			
			/* open the shared memory segment */
			shm_fd = shm_open(name7, O_RDWR, 0666);
			/* now map the shared memory segment in the address space of the process*/
			shelf = mmap(0,sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
			mutex7 = sem_open(sema7,O_EXCL);
			sem_getvalue(mutex7, &value);
			while(loop--)
			{
				sleep(rand()%2+1);
				sem_wait(rmutex);
				(*counter)++;
				if(*counter==1)
				{
					sem_wait(mutex7);
				}
				sem_post(rmutex);
				printf("\n Reader %d : I have read %d.\n",getpid(),* shelf);
				sem_wait(rmutex);
				(*counter)--;
				if(*counter==0)
				{
					sem_post(mutex7);
				}
				sem_post(rmutex);
			}
		sem_close(mutex7);
		sem_close(rmutex);
		munmap(counter,sizeof(int));
		munmap(shelf, sizeof(int));
		close(shm_fd);
		close(count_fd);
		shm_unlink(name7);
		shm_unlink(countername);
		exit(0);
		}
	}
	x=wait(&i);
	f=fopen("lol2.txt","w");
	fclose(f);
	close(count_fd);
	sem_unlink(cmutx);
	munmap(counter,sizeof(int));
	shm_unlink(countername);
	return 0;
}
