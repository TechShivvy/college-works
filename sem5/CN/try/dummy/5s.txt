#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>

void chat(int sockC)
{
	char text[1024];
	while(1)
	{
		bzero(text,1024);
		recv(sockC,text,1024,0);
		if(strstr(text,"exit"))
			break;
		printf("\r%s\n",text);
		bzero(text,1024);
		printf("Reply:\t");
		scanf("%[^\n]s",text);
		getchar();
		printf("\n");
		send(sockC,text,1024,0);
	}
}
int main(int argc,char *arg[])
{
	int sockS=socket(AF_INET,SOCK_STREAM,0),sockC;
	socklen_t addr_size;
	struct sockaddr_in addrS,addrC;
	addrS.sin_family = AF_INET;
	addrS.sin_port = htons(atoi(arg[1]));
	addrS.sin_addr.s_addr = INADDR_ANY;
	
	bind(sockS,(struct sockaddr*)&addrS,sizeof(addrS));
	listen(sockS,1);
	while(1)
	{
		if((sockC=accept(sockS,(struct sockaddr*)&addrC,&addr_size))<0)
			exit(1);
		printf("Connection accepted from %s:%d\n", inet_ntoa(addrC.sin_addr), ntohs(addrC.sin_port));
		if(fork()==0)
		{
			close(sockS);
			chat(sockC);
			printf("Disconnected from %s:%d\n", inet_ntoa(addrC.sin_addr), ntohs(addrC.sin_port));
		}	
	}
	close(sockC);
	return 0;
}
