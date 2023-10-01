#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/ioctl.h>
#include<netinet/in.h>
#include<net/if.h>
#include<arpa/inet.h>
#include<fcntl.h>

int main(int argc,char *arg[])
{
	int sockS=socket(AF_INET,SOCK_STREAM,0),nr;
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(arg[1]));
	addr.sin_addr.s_addr = INADDR_ANY;
	
	bind(sockS,(struct sockaddr*)&addr,sizeof(addr));
	listen(sockS,1);
	
	char data[100];
	int sockC=accept(sockS,NULL,NULL);
	recv(sockC,data,sizeof(data),0);
	
	int fd=open(data,O_RDONLY);
	if(fd<0)
	{
		printf("Error\n");
		strcpy(data,"-1");
		send(sockC,data,sizeof(data),0);
	}
	else
	{
		nr=read(fd,data,sizeof(data));
		printf("Sent\n");
		send(sockC,data,nr,0);
		close(fd);
	}	
	close(sockC);
	close(sockS);
	return 0;	
}
