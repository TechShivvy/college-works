#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

void grep(char *arg[],char c)
{
	int src=open(arg[2],O_RDONLY);
	if(src==-1)
	{
		printf("Src file error!\n");
		close(src);
		return;
	}
	
	char line[100],*buf=(char *)malloc(sizeof(char)*500);
	int l=0,i=0,nr,count;
	nr=read(src,buf,10000);
	
	while(l<nr)
	{
		line[100];
		for(i=0;buf[l]!='\n' && l<nr;i++,l++)
		{
			line[i]=buf[l];
		}
		line[i]='\0';
		l++;
		if(c=='n')
			count++;
		if(c=='v' && !strstr(line,arg[1]))
			printf("%s\n",line);
		else if( c!='v' && strstr(line,arg[1]))
		{
			if(c==' ')
				printf("%s\n",line);
			else if(c=='c')
				count++;
			else
				printf("%d:%s\n",count,line);
		}
	}
	if(c=='c')
		printf("%d\n",count);	
	free(buf);
}

int main(int argc,char *arg[])
{
	if(argc==3)
		grep(arg,' ');
	if(argc==4)
	{
		if(arg[1][0]=='-')
		{
			if(!strcmp(arg[1],"-c"))
				grep(++arg,'c');
			else if(!strcmp(arg[1],"-v"))
				grep(++arg,'v');
			else if(!strcmp(arg[1],"-n"))
				grep(++arg,'n');
		}
	}
	return 0;
}
