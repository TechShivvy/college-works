#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>

void chat(int sockS,char *name)
{
	char text[1024],who[255];
	while(1)
	{
		bzero(text,1024);
		bzero(who,255);
		printf("\nEnter: ");
		scanf("%[^\n]s",text);
		getc(stdin);
		strcpy(who,name);
		strcat(who,":\t");
		strcat(who,text);
		strcpy(text,who);
		send(sockS,text,1024,0);
		if(strstr(text,"exit"))
			break;
		bzero(text,1024);
		recv(sockS,text,1024,0);
		printf("Server: %s\n",text);
		
	}
	
}

int main(int argc,char *arg[])
{
	int sockS=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(arg[1]));
	addr.sin_addr.s_addr = INADDR_ANY;
	
	int connex=connect(sockS,(struct sockaddr*)&addr,sizeof(addr));
	chat(sockS,arg[2]);
	
	close(sockS);
	return 0;
}

