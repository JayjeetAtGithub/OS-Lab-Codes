/*
Compile: gcc multi_writer.c -o multiwriter -lpthread -lrt
         gcc one_reader.c -o onereader -lpthread -lrt

Run:   ./multiwriter & ./onereader
*/

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
    const char * name7 = "shared_memory7";
    const char * sema7= "mutex7";
    int shm_fd;   //shared memory file discriptor
    int loop=6;
    int * shelf;  
    sem_t * mutex7;
    int value,i,x;

    //create the shared memory segment
    shm_fd = shm_open(name7, O_CREAT | O_RDWR, 0666);
    //configure the size of the shared memory segment
    ftruncate(shm_fd,sizeof(int));

    shelf = mmap(0,sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    
    mutex7 = sem_open(sema7,O_CREAT,0666,1);  

    sem_getvalue(mutex7, &value);
    printf("The initial value of the semaphore is %d\n", value);   

    for(i=0;i<2;i++) // loop will run n times (n=4)
    {
        x=fork();
        if(x==0){
            
            //create the shared memory segment
            shm_fd = shm_open(name7, O_RDWR, 0666);
            //map the shared memory segment in process address space
            shelf = mmap(0,sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

            mutex7 = sem_open(sema7,O_EXCL); 
            sem_getvalue(mutex7, &value);
            printf("The value of the semaphore returned by O_EXCL %d\n", value);
            printf("\n Writer %d : I have started writing.\n",getpid());


            while(loop--){
                sleep(rand()%2+1);
                sem_wait(mutex7);
                sem_getvalue(mutex7, &value);
                printf("The value of the semaphore after sem_wait %d\n", value);
                (* shelf)++;
                sem_post(mutex7);
                sem_getvalue(mutex7, &value);
                printf("The value of the semaphore after sem_post %d\n", value);
                printf("Writer %d : written, now the value is %d.\n",getpid(), * shelf);
            }
            printf("Writer %d I wrote 6 times \n",getpid());
            sleep(rand()%2+1);
            sem_close(mutex7);
            //sem_unlink(sema7);
            /* close and unlink shared memory*/
            close(shm_fd);
            munmap(shelf, sizeof(int));            
            exit(0);
        }
    }
    sleep(50);
    for(i=0;i<2;i++) // loop will run n times (n=2)
        wait(NULL);
    close(shm_fd);
    sem_unlink(sema7);
    munmap(shelf, sizeof(int));
    shm_unlink(name7);
    return 0;
}