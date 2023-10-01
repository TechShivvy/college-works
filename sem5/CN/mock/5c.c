#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<net/if.h>

void chat(int sockS,char *name)
{
	char text[255],who[255];
	while(1)
	{
		bzero(text,255);
		bzero(who,255);
		scanf("%[^\n]s",text);
		getc(stdin);
		strcpy(who,name);
		strcat(who,":\t");
		strcat(who,text);
		strcpy(text,who);
		send(sockS,text,255,0);
		if(strstr(text,"exit"))
			break;
		bzero(text,255);
		recv(sockS,text,255,0);
		printf("Server: %s\n",text);
	}
}
int main(int argc,char *argv[])
{
	int sockS=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[1]));
	addr.sin_addr.s_addr = INADDR_ANY;
	
	int connex=connect(sockS,(struct sockaddr*)&addr,sizeof(addr));
	
	chat(sockS,argv[2]);
	return 0;
}
