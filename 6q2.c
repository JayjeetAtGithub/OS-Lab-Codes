//NAME - Shubrojyoti Karmakar
//ROLL - 17CS8016
//ASSIGNMENT 6.2

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<time.h>
#include<ctype.h>
int CHILD1=0,CHILD2=0;
void *expression( void *ptr );

int main()
{
	srand(time(NULL));
	pthread_t thread1, thread2;
	int iret1, iret2;
	char c[200],c1[150],c2[150],o;
	printf("Enter the expression - \n");
	scanf("%s",c);
	//printf("%s",c);
	int i;
	c1[0]='1';
	for(i=0;c[i]!=')';++i)
	{
		c1[i+1]=c[i];
	}
	c1[i+1]=c[i];
	c1[(++i)+1]='\0';
	o=c[i];
	++i;
	int j;
	c2[0]='2';
	for(j=0;c[i]!='\0';++i,++j)
	{
		c2[j+1]=c[i];
	}
	c2[j+1]='\0';
	
	printf("\n%s\n%s\n",c1,c2);
	printf("child thread calculating\n");
	iret1 = pthread_create( &thread1, NULL, expression, (void*) c1);
	iret2 = pthread_create( &thread2, NULL, expression, (void*) c2);
	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL); 
	if(o=='+')
		printf("the result is - %d\n",CHILD1+CHILD2);
	else
		printf("the result is - %d\n",CHILD1-CHILD2);
}

void *expression( void *ptr )
{
	char *expr=(char *)ptr;
	char c='\0';
	char part=expr[0];
	int sum=0;
	int digit=0;
	int i=1;
	while(expr[i]!='\0')
	{
		
		switch(expr[i])
		{
			case '(':++i;//printf("lol");
				break;
			case ')':++i;//printf("lol");
				break;
			case '+':c=expr[i];//printf("lol");
				++i;
				break;
			case '-':c=expr[i];//printf("lol");
				++i;
				break;
			default:
				digit=0;//printf("lol");
				while(isdigit(expr[i]))
				{
					digit=(digit*10)+(expr[i]-'0');
					++i;
					//printf("hello");
				}
				
				if(c=='+')
					sum=sum+digit;
				if(c=='-')
					sum=sum-digit;
				if(c=='\0')
					sum=digit;
		}
	}
	if(part=='1')
	{
		printf("child thread 1 result - %d\n",sum);
		CHILD1=sum;
	}
	else
	{
		printf("child thread 2 result - %d\n",sum);
		CHILD2=sum;
	}
}
