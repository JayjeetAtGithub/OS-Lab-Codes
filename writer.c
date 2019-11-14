//NAME - Jayjeet Chakraborty
//ROLL - 17CS8036
//ASSIGNMENT 9.2b

//10 writer each writing 2 times
#include<signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <semaphore.h>
int main()
{
	signal(SIGCHLD,SIG_IGN);

    const char * name7 = "shared_memory7";
    const char * sema7= "mutex7";
    int shm_fd;   //shared memory file discriptor
    int loop=2;
    int * shelf;  
    sem_t * mutex7;
    int value,i;
    pid_t x;
    //create the shared memory segment
    shm_fd = shm_open(name7, O_CREAT | O_RDWR, 0666);
    //configure the size of the shared memory segment
    ftruncate(shm_fd,sizeof(int));
    //map to the shared memeory segment
    shelf = mmap(0,sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    mutex7 = sem_open(sema7,O_CREAT,0666,1);
    sem_getvalue(mutex7, &value);
    printf("The initial value of the semaphore is %d\n", value);

	FILE *f=fopen("lol.txt","w");
	fclose(f);

    for(i=0;i<10;i++) // loop will run n times (n=4)
    {
        x=fork();
        if(x==0){
            
            //create the shared memory segment
            shm_fd = shm_open(name7, O_RDWR, 0666);
            //map the shared memory segment in process address space
            shelf = mmap(0,sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

            mutex7 = sem_open(sema7,O_EXCL); 
            sem_getvalue(mutex7, &value);


            while(loop--){
                sleep(rand()%2+1);
                sem_wait(mutex7);
                sem_getvalue(mutex7, &value);
                (* shelf)++;
                sem_post(mutex7);
                sem_getvalue(mutex7, &value);
                printf("Writer %d : written, now the value is %d.\n",getpid(), * shelf);
            }
            printf("Writer %d I wrote 2 times \n",getpid());
            sleep(rand()%2+1);
            sem_close(mutex7);
            //sem_unlink(sema7);
            /* close and unlink shared memory*/
            close(shm_fd);
            munmap(shelf, sizeof(int));
            exit(0);
        }
    }
    
    x=wait(&i);

	while(!(f=fopen("lol2.txt","r")));
	fclose(f);

    close(shm_fd);
    sem_unlink(sema7);
    munmap(shelf, sizeof(int));
    shm_unlink(name7);
    return 0;
}
