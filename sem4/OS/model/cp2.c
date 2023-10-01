#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

void cp(char *arg[],int i)
{
	int src=open(arg[1],O_RDONLY);
	if(src==-1)
	{
		printf("Src file Error!");
		close(src);
		return ;
	}
	
	int dest;
	
	if(i)
	{
		dest=open(arg[2],O_WRONLY);
		if(dest!=-1)
		{
			char ch;
			printf("Overwrite?");
			scanf(" %c",&ch);
			if(!(ch=='y'||ch=='Y'))
			{
				close(dest);
				return;			
			}
		}
		close(dest);
	}
	
	dest=creat(arg[2],0600);
	
	int buf[500];
	int nr,nw=0;
	
	while((nr=read(src,buf,500)))
		nw+=write(dest,buf,nr);
	
	if(nw!=-1)
		printf("COPIED");
	else
		printf("Error while copying");
	 close(dest);
	 close(src);
	 return;
}

int main(int argc,char *arg[])
{
	if(argc==3)
		cp(arg,0);
	else if(argc==4)
	{
		if(!strcmp(arg[1],"-i"))
			cp(++arg,1);
	}
	return 0;
}

