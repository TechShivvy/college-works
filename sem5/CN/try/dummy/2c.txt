#include<stdlib.h>
#include<stdio.h>
#include<string.h>
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
	
	int connex=connect(sockS,(struct sockaddr*)&addr,sizeof(addr));
	if(connex+1)
	{
		char data[]="Message from shivi\n";
		send(sockS,data,sizeof(data),0);
		recv(sockS,data,sizeof(data),0);
		printf("%s",data);
	}
	else
		printf("Error..\n");
	close(sockS);
	return 0;
}
