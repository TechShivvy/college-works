#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include<string.h>
#include<ctype.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "IP_MAC.h"

int main(int argc, char const* argv[])
{
	int port=atoi(argv[1]);
    int sockD = socket(AF_INET, SOCK_STREAM, 0); 
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port= htons(port);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    char *ip=IP();
    char *mac=MAC();
	printf("\nMy MAC:%s\n",mac);
	printf("\nMy IP:%s\n",ip);
    int connectStatus= connect(sockD, (struct sockaddr*)&servAddr,sizeof(servAddr));
    if (connectStatus == -1)
		printf("Error...\n");
    else 
    {
        char strData[255];
        recv(sockD, strData, sizeof(strData),0);
		if(!strcmp(strData,"invalid"))
			return 0;
			
		printf("\nARP request received!\n");
		//printf("\n%s",strData);
		if(!isValidIP(strData))
		{
			strcpy(strData,"invalid");
			send(sockD, strData, sizeof(strData), 0);
			printf("Received an invalid IP");
			return 0;
		}
        
		if(!strcmp(strData,ip))
		{
			printf("\nIP MATCHED! IP = %s received\n",strData); 
        	strcpy(strData,mac);
        }
        else
		{
			printf("\nIP NOT MATCHED! IP = %s received\n",strData);        	
			strcpy(strData,"False");
		}
        send(sockD, strData, sizeof(strData), 0);
        if(!strcmp(strData,mac))
        {
        	recv(sockD, strData, sizeof(strData),0);
        	printf("Ack: %s\n",strData);
        }
    }
    
 	return 0;
 }
