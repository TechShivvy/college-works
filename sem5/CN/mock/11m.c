#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/ioctl.h>
#include<netinet/in.h>
#include<net/if.h>
#include<arpa/inet.h>
#include<netdb.h>

int main(int argc,char *argv[])
{
	char domain[100],path[100],buff[1000];
	sscanf(argv[1],"https://%[^/]%[^\n]",domain,path);
	printf("%s\t%s\n",domain,path);
	struct hostent *server=gethostbyname(domain);
	struct in_addr **ip=(struct in_addr**)server->h_addr_list;
	int sockS=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(80);
	addr.sin_addr.s_addr=inet_addr(inet_ntoa(*ip[0]));
	connect(sockS,(struct sockaddr*)&addr,sizeof(addr));
	sprintf(buff,"GET %s HTTP/1.1\r\nHost: %s \r\n\r\n",path,domain);
	send(sockS,buff,sizeof(buff),0);
	bzero(buff,1000);
	FILE *fp=fopen("temp.html","w");
	while(recv(sockS,buff,sizeof(buff),0))
	{
		for(int i=0;i<1000;i++)
		{
			if(feof(fp))
				break;
			fputc(buff[i],fp);
		}
	}
	fclose(fp);
	close(sockS);
	return 0;
}
