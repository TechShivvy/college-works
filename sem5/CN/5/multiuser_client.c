#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>	

#define PORT 3230

int main(int argc,char* argv[]){

	int clientSocket, ret;
	struct sockaddr_in serverAddr;
	

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("Error in connection.\n");
		exit(1);
	}

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(atoi(argv[1]));
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("Error in connection.\n");
		exit(1);
	}
	char buffer[1024],who[1024],temp[1024];
	while(1){
	memset(who, 0, sizeof(who));
		memset(buffer, 0, sizeof(buffer));
		memset(temp, 0, sizeof(temp));
		strcpy(who,argv[2]);
		strcat(who,": \t");
		printf("%s: \t",argv[2]);
		scanf("%[^\n]s",temp);
		getc(stdin);
		strcpy(buffer,temp);
		strcat(who,buffer);
		send(clientSocket, who, sizeof(who), 0);
		
		if(strcmp(buffer, ":exit") == 0){
		memset(buffer, 0, sizeof(buffer));
			close(clientSocket);
			printf("Disconnected from server.\n");
			exit(1);
		}
		memset(buffer, 0, sizeof(buffer));
		if(recv(clientSocket, buffer, 1024, 0) < 0){
			printf("[-]Error in receiving data.\n");
		}else{
			printf("Server: \t%s\n", buffer);
		}
		
	}

	return 0;
}

