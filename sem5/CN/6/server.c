#include <netinet/in.h> 
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char const* argv[])
{
	int port=atoi(argv[1]);
	
    int servSockD = socket(AF_INET, SOCK_STREAM, 0);
    
    char serMsg1[255];
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    servAddr.sin_addr.s_addr = INADDR_ANY;
    
    bind(servSockD, (struct sockaddr*)&servAddr,sizeof(servAddr));
    
    listen(servSockD, 1);
    
    int clientSocket = accept(servSockD, NULL, NULL);
    
    recv(clientSocket, serMsg1, sizeof(serMsg1), 0);
    int fd = open(serMsg1, O_RDONLY);
    char buf[255];
    if(fd < 0) {
        printf("Does not exist!\n");
        strcpy(buf,"-1");
    	send(clientSocket, buf, sizeof(buf), 0);
    }
    else{
    	read(fd,buf,sizeof(buf));
    	send(clientSocket, buf, sizeof(buf), 0);
    	printf("Read from file and sent to client\n");
    	close(fd);
    }

    return 0;
}

