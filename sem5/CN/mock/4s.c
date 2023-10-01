#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<net/if.h>

void chat(int sockC)
{
	char text[255];
	while(1)
	{
		bzero(text,255);
		recv(sockC,text,255,0);
		printf("\r%42s\n",text);
		scanf("%[^\n]s",text);
		getchar();
		send(sockC,text,255,0);
		if(strstr(text,"exit"))
			break;
	}
}

int main(int argc,char *argv[])
{
	int sockS= socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9010);
	addr.sin_addr.s_addr = INADDR_ANY;

	bind(sockS,(struct sockaddr*)&addr,sizeof(addr));
	listen(sockS,1);
	int sockC=accept(sockS,NULL,NULL);
	
	chat(sockC);
	
	close(sockC);
	close(sockS);

	return 0;
}
