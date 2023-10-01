#include <netinet/in.h> 
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include<string.h>
#include<ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "IP_MAC.h"

int main(int argc, char const* argv[])
{
	int port=atoi(argv[1]);
    int servSockD = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    servAddr.sin_addr.s_addr = INADDR_ANY;
    bind(servSockD, (struct sockaddr*)&servAddr,sizeof(servAddr));
    listen(servSockD, 3);
    char strData[30];
    char *ip=IP();
    char *mac=MAC();
	printf("\nMy MAC:%s",mac);
	printf("\nMy IP:%s\n",ip);
    printf("Enter Destination ip: ");
    scanf("%s",strData);
    int noc=2;
    int clientsocket[noc];
    for(int i=0;i<noc;i++)
       clientsocket[i]=accept(servSockD,NULL,NULL);
	if(!isValidIP(strData))
	{
		strcpy(strData,"invalid");
		for(int i=0;i<noc;i++)
			send(clientsocket[i], strData, sizeof(strData), 0);
		printf("Invalid IP is entered!\nExiting...\n");
	}
	else
	{
		for(int i=0;i<noc;i++)
			send(clientsocket[i], strData, sizeof(strData), 0);
    	//strcpy(strData,"10.6.10.10");
		printf("\nARP request broadcasted..\n\nWaiting for Reply..\n\n");
		int flag=0;
		for(int i=0;i<noc;i++)
		{
			recv(clientsocket[i], strData, sizeof(strData), 0);
			if(!strcmp(strData,"invalid"))
				printf("\nclient%d received an invalid IP",i+1);
			else
				printf("\nclient%d received a valid IP",i+1);
			if(strcmp(strData,"False"))
			{	
				printf("\nIP has been matched!\n");
				printf("\nMAC of the accepted client %s\n",strData);
				if(isValidMAC(strData))
				{
					printf("\nReceived MAC is a valid one\n");
					strcpy(strData,"Received valid mac");
				}
				else
				{
					printf("\nReceived MAC is a invalid one\n");
					strcpy(strData,"Invalid MAC was sent");
				}
				send(clientsocket[i], strData, sizeof(strData), 0);
				printf("\nAcknowledgement Sent!\n");
				flag=1;
				break;
			}
		}
		if(!flag)
			printf("\n\nARP request failed\n");
	}
    return 0;
}
