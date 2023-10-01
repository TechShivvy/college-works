#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
void cp(char *arg[],int i)
{
	int src=open(arg[1],O_RDONLY);
	if(src==-1)
	{
		printf("Source file doesn't exist");
		close(src);
		return;
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
				return ;
			}
		}
		close(dest);
	}
	dest=creat(arg[2],0600);
	
	char buf[500];
	int nr,nw=0;
	while((nr=read(src,buf,500))!=0)
		nw+=write(dest,buf,nr);
	if(nw!=-1)
		printf("COPIED!\n");
	else
		printf("Error while copying\n");
	close(src);
	close(dest);
	return;
}

int main(int argc,char *arg[])
{
	if(argc==3)
		cp(arg,0);
	else if(argc==4)
	{
		if(strcmp(arg[1],"-i")==0)
			cp(++arg,1);
	}	
	return 0;
}
