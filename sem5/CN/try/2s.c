#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main(int argc,char *arg[])
{
	int sockS=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(arg[1]));
	addr.sin_addr.s_addr = INADDR_ANY;
	
	bind(sockS,(struct sockaddr*)&addr,sizeof(addr));
	listen(sockS,1);
	int sockC=accept(sockS,NULL,NULL);
	char data[255];
	recv(sockC,data,sizeof(data),0);
	printf("%s",data);
	send(sockC,data,sizeof(data),0);
	close(sockC);
	close(sockS);
	return 0;
}
