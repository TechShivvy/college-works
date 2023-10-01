#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
int main(int argc,char *arg[])
{
	//checking no of args
	if(argc!=3)
	{
		printf("Invalid no of args!\n");
		return -1;	
	}
	
	//checking src file
	int fd=open(arg[2],O_RDONLY);
	if(fd==-1)
	{
		printf("Source File doesnt exist!\n");
		close(fd);
		return -1;	
	}
	
	char line[100],buf[1024];	
	int l=0,i=0,nr,count=0;
	nr=read(fd,buf,1024);
	close(fd);
	
	while(l<nr)
	{	
		for(i=0;buf[l]!='\n'&&l<nr;i++,l++)
		{
			line[i]=buf[l];
		}
		line[i]='\0';
		l++;
		if(strstr(line,arg[1]))
			count++;
	}
	printf("%d\n",count);	
	return 0;
}
