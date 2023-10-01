#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/ioctl.h>
#include<netinet/in.h>
#include<net/if.h>
#include<arpa/inet.h>

int main()
{
	int sockS=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in addr;
	char msg[]="hello from shivi";
	addr.sin_family=AF_INET;
	addr.sin_port=htons(9001);
	addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	bind(sockS,(struct sockaddr*)&addr,sizeof(addr));
	recvfrom(sockS,msg, strlen(msg),MSG_WAITALL,(const struct sockaddr *)&addr,sizeof(addr));
	close(sockS);
	return 0;	
}
