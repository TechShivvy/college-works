#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/ioctl.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<net/if.h>
#include<netdb.h>

void main(int argc, char *argv[])
{
  	int sockS=socket(AF_INET,SOCK_DGRAM,0);
  	struct sockaddr_in addr,caddr;
  	char buffer[1024];
  	socklen_t addr_size;
  	addr.sin_family = AF_INET;
  	addr.sin_port = htons(9001);
  	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  	bind(sockS, (struct sockaddr*)&addr, sizeof(addr));
  	addr_size = sizeof(caddr);
  	recvfrom(sockS, buffer, 1024, 0, (struct sockaddr*)&caddr, &addr_size);
  	printf("[+]Data Received: %s", buffer);
	strcpy(buffer,"heele,efjwhjefbwejkqg");
	sendto(sockS,buffer,1024,0,(struct sockaddr*)&caddr,addr_size);
	return 0;
}

