//NAME - Shubrojyoti Karmakar
//ROLL - 17CS8016
//ASSIGNMENT 3.4

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

int main()
{
	int original=0;
	printf("enter the size of file - ");
	scanf("%d",&original);
	FILE *f=fopen("data.txt","w");
	for(int i=0;i<original;++i)			//inserting 10,000 random digits to a file
	{
		fprintf(f,"%d\n",(rand()%1000)+1);
	}
	fclose(f);
	
	int c_start=0,c_end=original;
	int size1 =original/2,size2=original-size1;
	pid_t x;
	int total=0,n;
	float avg=0;
	while(original>25)			//creating bst structure of parent and child
	{
		size1 =original/2;		//original for subchild 1 at each each level
		size2=original-size1;		//original for subchild 2 at each each level
		x=fork();
		if(x==0)
		{
			c_end=c_start+size1;
			printf("parent id %d, my id = %d\n",getppid(),getpid());
			original=size1;
		}
		else
		{
			x=fork();
			if(x!=0)	//parent and child as parent to exit the wile loop construct
			{
				break;
			}
			c_start=c_end-size2;
			printf("parent id %d, my id = %d\n",getppid(),getpid());
			original=size2;
		}
	}
	if(x==0)			//code part for leaf nodes
	{
		printf("my id =%d, my portion size=%d,starting = %d, ending = %d\n",getpid(),original,c_start,c_end);
		FILE *f=fopen("data.txt","r");
		fseek(f,c_start,SEEK_SET);
		while(ftell(f)<=c_end)
		{
			fscanf(f,"%d\n",&n);
			total+=n;
		}
		avg=((float)total/(c_end-c_start));
		printf("\nAverage calculated by child having group id = %d is = %f\n\n",getpid(),avg);
		fclose(f);
	}
	
	return 0;
}
