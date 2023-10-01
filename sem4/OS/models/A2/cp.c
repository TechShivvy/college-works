#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

void cp(char *arg[],int i)
{
	int src=open(arg[1],O_RDONLY);
	if(src==-1)
	{
		printf("Error");
		close(src);
		return;
	}
	int dest;
	if(i)
	{
		dest=open(arg[2],O_WRONLY);
		char ch;
		if(dest!=-1)
		{
			printf("Overwwrite:");
			scanf(" %c",&ch);
			if(ch=='n'||ch=='N')
			{
				close(dest);
				return;
			}
		}
		close(dest);
	}
	dest=creat(arg[2],0666);
	int nr,nw=0;
	char buf[500];
	
	while((nr=read(src,buf,500))!=0)
	{
		nw+=write(dest,buf,nr);
		memset(buf,0,sizeof(buf));
	}
	if(nw!=-1)
		printf("COPIED!\n");
	else
		printf("Error while copying\n");
		
	close(src);
	close(dest);
	return 0;
}

int main(int argc,char *arg[])
{
	if(argc==3)
		cp(arg,3);
	else if(argc==4)
	{
		if(strcmp(arg[1],"-i")==0)
			cp(++arg,1);
	}
	return;
		
}
