#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>

int main(int argc, char const* argv[])
{

	// create server socket similar to what was done in
	// client program
	int servSockD = socket(AF_INET, SOCK_STREAM, 0);

	// string store data to send to client
	char serMsg[255] ;//= "Message from the server to the client \'Hello Client\' ";

	// define server address
	struct sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(9001);
	servAddr.sin_addr.s_addr = INADDR_ANY;

	// bind socket to the specified IP and port
	bind(servSockD, (struct sockaddr*)&servAddr,sizeof(servAddr));

	// listen for connectionsx`
	listen(servSockD, 1);

	// integer to hold client socket.
	int clientSocket = accept(servSockD, NULL, NULL);
	
	recv(clientSocket, serMsg, sizeof(serMsg), 0);
	printf("Message: %s\n", serMsg);
	printf("Send a Reply: ");
	scanf("%[^\n]s",serMsg);
	send(clientSocket, serMsg, sizeof(serMsg), 0);
	close(servSockD);
	return 0;
}
