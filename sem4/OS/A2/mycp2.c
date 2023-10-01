#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
int main(int argc,char *arg[])
{
	//checking no of args
	if(argc<3)
	{
		printf("Some of the args are missing!\n");
		return -1;	
	}
	
	//checking src file	
	int fds=open(arg[1],O_RDONLY);
	if(fds==-1)
	{
		printf("Source File doesnt exist!\n");
		close(fds);
		return -1;	
	}
	
	//checking dest file
	int fdd=open(arg[2],O_WRONLY|O_CREAT,0600);
	if(fdd==-1)
	{
		printf("Dest error\n");
		return -1;	
	}
		
	//reading src and writing into dest
	char buf[500];	
	int nr,nw=0;
	
	while((nr=read(fds,buf,500))!=0)
        	nw+=write(fdd,buf,nr);
        	
        if(nw!=-1)
		printf("COPIED!\n");
	else
		printf("Error while copying\n");
		
	close(fds);
	close(fdd);
	return 0;
}
