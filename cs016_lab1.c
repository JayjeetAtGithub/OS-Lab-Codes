#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>


void main()
{
	struct timeval tv;
	int counter=500;
	float balance=0.0;
	FILE *log;
	int k=0,l=0;
	

		while(counter--)
		{
		FILE *F;
		F=fopen("document.bin.txt","wb+");
		gettimeofday(&tv,NULL);
		log=fopen("log.txt","a");
		fread(&balance,sizeof(float),1,F);
		fprintf(log,"%d %d %d ",getppid(),getpid(),(int)tv.tv_usec);
		fprintf(log,"%f ",balance);		
		balance++;
		fprintf(log,"%f \n",balance);
		fwrite(&balance,sizeof(float),1,F);
		for(k=0;k<=5000;++k){
		for(l=0;l<=5000;++l){}}
		fclose(F);
		fclose(log);	
	}
	
	
}
