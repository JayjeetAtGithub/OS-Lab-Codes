//NAME - Jayjeet Chakraborty
//ROLL - 17CS8036
//ASSIGNMENT 7.3

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

int y=10;
void*task(void*x)
{
	printf("i Am thread %d\n",*(int*)x);
	pthread_exit((void*)&y);
}

int main()
{
	pthread_attr_t thread_attr;
	pthread_attr_init(&thread_attr);
	pthread_attr_setdetachstate(&thread_attr,PTHREAD_CREATE_DETACHED);
	int i,*tres,n;
	printf("Enter the number of threads to be created - ");
	scanf("%d",&n);
	pthread_t thread_id[n];
	int farg[n];
	for(i=0;i<n;++i)
	{
		farg[i]=i+1;
		if(i%2)
		{
			pthread_attr_setdetachstate(&thread_attr,PTHREAD_CREATE_DETACHED);
			pthread_create(&thread_id[i],&thread_attr,task,(void*)&farg[i]);
		}
		else
		{
			pthread_attr_init(&thread_attr);
			pthread_create(&thread_id[i],&thread_attr,task,(void*)&farg[i]);
		}
	}
	for(i=0;i<n;++i)
	{
		if(!(i%2))
		{	pthread_join(thread_id[i],(void**)&tres);
			printf("received %d\n",*tres);}
	}
	return 0;
}
