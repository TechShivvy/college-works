#include<stdlib.h>
#include<string.h>
#include<stdio.h>
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
	int sockS=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(arg[1]));
	addr.sin_addr.s_addr = INADDR_ANY;
	
	int connex=connect(sockS,(struct sockaddr*)&addr,sizeof(addr));
	char buf[255]="f1.txt";
	send(sockS,buf,sizeof(buf),0);
	
	recv(sockS,buf,sizeof(buf),0);
	if(!strcmp(buf,"-1"))
		printf("No\n");
	else
	{
		int fd=open("new.txt",O_CREAT|O_WRONLY,0777);
		printf("\n%s\n",buf);
		write(fd,buf,strlen(buf));
		printf("\nDone\n");
		close(fd);
	}
	
	close(sockS);
	return 0;
}
