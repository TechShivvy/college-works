#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

void grep(char *arg[],char c)
{
	
	//checking src file
	int fd=open(arg[2],O_RDONLY);
	if(fd==-1)
	{
		printf("Source File doesnt exist!\n");
		close(fd);
		return ;	
	}
	
	char line[100],*buf=(char *)malloc(sizeof(char*)*500); //char buf[2000];
	int l=0,i=0,nr,count=0;
	nr=read(fd,buf,10000); 				 // nr=read(fd,buf,2000);
	close(fd);
	while(l<nr)
	{	
		line[100];
		for(i=0;buf[l]!='\n'&&l<nr;i++,l++)
		{
			line[i]=buf[l]; 	      //extracting lines
		}
		if(c=='n')
			count++;
		line[i]='\0';
		l++;
		if(c=='v' && (!strstr(line,arg[1]))) // -v
			printf("%s\n",line);
		else if(c!='v' && strstr(line,arg[1]))
		{
			if(c==' ')                   //  basic grep
				printf("%s\n",line);
			else if(c=='c')              //  -c
				count++;
			else 			      //  -n
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
	else if(argc==4)
	{
		if(arg[1][0]=='-')
		{
			if(strcmp(arg[1],"-c")==0)
				grep(++arg,'c');
			else if(strcmp(arg[1],"-v")==0)
				grep(++arg,'v');
			else if(strcmp(arg[1],"-n")==0)
				grep(++arg,'n');
			else
				printf("Invalid option\n");
		}
		else
			printf("Invalid command\n");
	}
	else
		printf("Invalid command\n");
	return 0;
}
