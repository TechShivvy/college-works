#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
int cp(char *arg[],int i)
{	
	//checking src file	
	int fds=open(arg[1],O_RDONLY);
	if(fds==-1)
	{
		printf("Source File doesnt exist!\n");
		close(fds);
		return -1;	
	}
	int fdd;
	
	//checking dest file
	if(i) // cp -i 
	{
		fdd=open(arg[2],O_WRONLY);
		if(fdd!=-1) //if the file exists 
		{
			char ch;
			printf("Overwrite %s file?(y/n) ",arg[2]);
			scanf(" %c",&ch);
			if(!(ch=='y'||ch=='Y')) //other than y/Y
			{
				close(fdd);
				return -1;
			}
		}
		close(fdd);
	}
	fdd=creat(arg[2],0600); //even if the file exists or doesnt	
	
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

int main(int argc,char *arg[])
{
	if(argc==3)
		cp(arg,0);
	else if(argc==4)
	{
		if(strcmp(arg[1],"-i")==0)
		{
			cp(++arg,1);
		}
	}
	return 0;
}


