#include <netinet/in.h> 
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
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
    printf("Enter Destination MAC: ");
    scanf("%s",strData);
    //strcpy(strData,"40:a8:f0:5c:e7:d4");
    printf("\nRARP request broadcasted..\n\nWaiting for Reply..\n\n");
    int clientsocket[4];
    for(int i=0;i<2;i++)
       clientsocket[i]=accept(servSockD,NULL,NULL);
    for(int i=0;i<2;i++)
		send(clientsocket[i], strData, sizeof(strData), 0);
	int flag=0;
	for(int i=0;i<2;i++)
	{
		recv(clientsocket[i], strData, sizeof(strData), 0);
		if(strcmp(strData,"False"))
		{
			printf("IP of the accepted client %s\n",strData);
			strcpy(strData,"Received");
			send(clientsocket[i], strData, sizeof(strData), 0);
			printf("\nAcknowledgement Sent!\n");
			flag=1;
			break;
		}
	}
	if(!flag)
		printf("\nRARP requeted failed\n");
    return 0;
}
