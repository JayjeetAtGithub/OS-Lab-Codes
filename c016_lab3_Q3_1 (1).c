//NAME - Shubrojyoti Karmakar
//ROLL - 17CS8016
//ASSIGNMENT 3.1

#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<signal.h>
pid_t x[100],y;
int n;
int main(void)
{
	int i=0,j=0;
	FILE *f=fopen("data.txt","w");
	
	
	for(i=0;i<10000;++i)			//inserting 10,000 random digits to a file
	{
		fprintf(f,"%d\n",(rand()%1000)+1);
	}
	fclose(f);
	
	
	f=fopen("data.txt","a");
	int last=ftell(f)-1;				//getting the file size
	fclose(f);
	
	
	int pp=0;
	int key=0;
	
	printf("Enter the number of child - ");
	scanf("%d",&n);
	
	int cc[n],avgp=0;
	clock_t sp,ep,sc[n],ec[n];			//clock variable
	int step=last/n,avg[n];
	int s[n];			//start valid file pointer value for each division
	int F[n];			//end valid file pointer value for each division
	FILE *f1[n];
	s[0]=0;
	F[0]=step;
	cc[0]=0;
	f1[0]=NULL;
	avg[0]=0;
	for(i=1;i<n;++i)
	{
		cc[i]=0;
		f1[i]=NULL;
		s[i]=F[i-1];
		avg[i]=0;
		F[i]=F[i-1]+step;
	}
	
	int flag=0;
	
	for(i=0;i<n;++i)
	{
		x[i]=fork();
		if(x[i]==0)						//ith child for ith part of file
		{
			flag=0;
			f1[i]=fopen("data.txt","r");
			fseek(f1[i],s[i],SEEK_SET);
			sc[i]=clock();
			while(ftell(f)<=F[i])
			{
				fscanf(f,"%d\n",&n);
				cc[i]++;
				avg[i]+=n;
			}
			ec[i]=clock();
			fclose(f1[i]);
			printf("child %d average = %f time taken = %f\n",i+1,((float)avg[i])/cc[i],((double)ec[i]-(double)sc[i])/CLOCKS_PER_SEC);
			break;
		}
		else
		{
			flag=1;
		}
	}
	if(flag==1)
	{
		f=fopen("data.txt","r");
		sp=clock();
		while(!feof(f))
		{
			fscanf(f,"%d\n",&n);
			pp++;
			avgp+=n;
		}
		ep=clock();
		sleep(1);
		printf("parent average = %f time taken = %f\n",((float)avgp)/pp,((double)ep-(double)sp)/CLOCKS_PER_SEC);		//parent's average
		fclose(f);
	}
	return 0;
}
