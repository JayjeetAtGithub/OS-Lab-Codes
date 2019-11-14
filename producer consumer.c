//NAME - Jayjeet Chakraborty
//ROLL - 17CS8036
//ASSIGNMENT 9.1
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 5

sem_t full, empty , mutp, mutc;

int buffer[BUFFER_SIZE];

int counter;

pthread_t tid;

void *producer(void *param);
void *consumer(void *param);

void initializeData()
{

	sem_init(&mutp,0,1);
	sem_init(&mutc,0,1);
  	sem_init(&full,0,0);
  	sem_init(&empty,0,BUFFER_SIZE);
  	counter=0;
}


int insert_item(int item)
{
  	if(counter < BUFFER_SIZE)
	{
    		buffer[counter] = item;
    		(counter++)% BUFFER_SIZE;
    		return 0;
  	}
  	else
    		return -1;
}



int remove_item(int *item)
{
  	if(counter > 0)
	{
    		*item = buffer[(counter-1)];
    		counter--;
    		return 0;
  	}
  	else
    		return -1;

}


void *producer(void *param)
{
	int item;
  	while(1)
	{
    		sleep(5);
    		item=rand();
    		sem_wait(&empty);
    		sem_wait(&mutp);
		insert_item(item);
    		printf("producer produced item : %d\n",item);
    		sem_post(&mutp);
    		sem_post(&full);
  	}
}



void *consumer(void *param)
{
  	int item;
  	while(1)
	{
    		sleep(5);
		sem_wait(&full);
		sem_wait(&mutc);
		remove_item(&item);
    		printf("Consumer consumed %d\n",item);
		sem_post(&mutc);
		sem_post(&empty);
  	}
}

int main()
{
 	int i;
  	int prod = 10;
  	int cons = 10; 

  	initializeData();

  	for(i=0;i<prod;i++)
	{
    		pthread_create(&tid,NULL,producer, NULL);
  	}


  	for(i=0;i<cons;i++)
	{
    		pthread_create(&tid,NULL,consumer, NULL);
  	}

  	sleep(5);
  	exit(0);
}
