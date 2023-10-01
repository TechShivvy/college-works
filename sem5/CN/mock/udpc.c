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
 	int sockS=socket(AF_INET,SOCK_DGRAM,0);;
  	struct sockaddr_in addr;
  	char buffer[1024];
  	socklen_t addr_size=sizeof(addr);

  	addr.sin_family = AF_INET;
  	addr.sin_port = htons(9001);
  	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  	strcpy(buffer, "Hello Server\n");
  	sendto(sockS, buffer, 1024, 0, (struct sockaddr*)&addr, sizeof(addr));
  	printf("[+]Data Send: %s", buffer);
	recvfrom(sockS,buffer,1024,0,(struct sockaddr*)&addr,&addr_size);
	printf("\n%s",buffer);
	return 0;
}
