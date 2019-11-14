//NAME - Shubrojyoti Karmakar
//ROLL - 17CS8016
//ASSIGNMENT 6.1

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<time.h>


int Array[100];

void *addition( void *ptr );

int main()
{
	srand(time(NULL));
	for(int i=0;i<100;++i)			//inserting 100 random digits to an array
	{
		Array[i]=(rand()%100)+1;
	}
	pthread_t thread1, thread2;
	int message1 = 0;
	int *m1=&message1;
	int message2 = 50;
	int*m2=&message2;
	int iret1, iret2;
	printf("child thread calculating\n");
	iret1 = pthread_create( &thread1, NULL, addition, (void*) m1);
	iret2 = pthread_create( &thread2, NULL, addition, (void*) m2);
	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL); 
	printf("inside parent for conformation\n");
	int sum=0;
	for(int i=0;i<50;++i)
	{
		sum=sum+Array[i];
	}
	printf("sum1 = %d\n",sum);
	sum=0;
	for(int i=50;i<100;++i)
	{
		sum=sum+Array[i];
	}
	printf("sum2 = %d\n",sum);
}

void *addition( void *ptr )
{
	int *A=(int *)ptr;
	int sum=0;
	for(int i=*A;i<*A+50;++i)
	{
		//printf("%d\n",sum);
		sum=sum+Array[i];
	}
	if(*A==1)
	printf("sum1 = %d\n",sum);
	else
	
	printf("sum2 = %d\n",sum);
}
