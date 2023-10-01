#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

void grep(char *arg[],int op)
{
	int src=open(arg[2],O_RDONLY);
	if(src==-1)
	{
		printf("Error");
		close(src);
		return;
	}
	int nr,l=0,count=0,i;
	char *buf=(char*)malloc(sizeof(char*)*500),*line=(char*)malloc(sizeof(char*)*500);
	nr=read(src,buf,10000);
	while(l<nr)
	{
		for(i=0;i<nr && buf[l]!='\n';l++,i++)
			line[i]=buf[l];
		l++;
		line[i]='\0';
		if(op=='n')
			count++;
		if(op=='v' && !strstr(line,arg[1]))
			printf("%s\n",line);
		if(op!='v' && strstr(line,arg[1]))
		{
			if(op==' ')
				printf("%s\n",line);
			else if(op=='c')
				count++;
			else
				printf("%d:%s\n",count,line);
		}
		memset(line,0,sizeof(line));
	}
	free(line);
	if(op=='c')
		printf("%d",count);
	free(buf);
	return;
	
}


int main(int argc,char *arg[])
{
	if(argc==3)
		grep(arg,' ');	
	else if(argc==4)
	{
		if(arg[1][0]=='-')
		{
			++arg;
			if(strcmp(arg[0],"-c")==0)
				grep(arg,'c');
			else if(strcmp(arg[0],"-n")==0)
				grep(arg,'n');
			else if(strcmp(arg[0],"-v")==0)
				grep(arg,'v');
		}
	}
}
