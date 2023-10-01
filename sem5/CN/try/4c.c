#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

void chat(int sockS)
{
	char text[255];
	while(1)
	{
		bzero(text,255);
		scanf("%[^\n]s",text);
		getchar();
		send(sockS,text,255,0);
		bzero(text,255);
		recv(sockS,text,255,0);
		printf("\r%42s\n",text);
		if(strstr(text,"exit"))
			break;
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
	
	chat(sockS);
	
	close(sockS);
	return 0;
}
