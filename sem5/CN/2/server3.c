#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>
#include <ctype.h>
struct packet
{
	int alpha;
	int vowel;
	int digit;
	int other;
}defaultValue={0,0,0,0};
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
	printf("Message received: %s\n", serMsg);
	struct packet data=defaultValue;
	int i=0;
	while(serMsg[i]!='\0')
    	{
		if(isalpha(serMsg[i]))
		{
		    data.alpha++;
		    char c=tolower(serMsg[i]);
		    if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u')
		    	data.vowel++;
		}
		else if(isdigit(serMsg[i]))
		    data.digit++;
		else
		    data.other++;
		i++;
    	}
	send(clientSocket, &data, sizeof(data), 0);
	printf("\nStatistics sent!\n");
	close(servSockD);
	return 0;
}
