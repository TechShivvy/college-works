#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>
#include <string.h>

struct packet
{
	int alpha;
	int vowel;
	int digit;
	int other;
};

int main(int argc, char const* argv[])
{
	int sockD = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(9001); // use some unused port number
	servAddr.sin_addr.s_addr = INADDR_ANY;
	int connectStatus = connect(sockD, (struct sockaddr*)&servAddr,sizeof(servAddr));
	if (connectStatus == -1) 
		printf("Error...\n");
	else 
	{
		char strData[255];
		//char strData[255] = "Message from the client to the server \'Hello Server\' ";
		printf("Enter some text to send: ");
		scanf("%[^.].s",strData);
		strcat(strData,".");
		send(sockD, strData, sizeof(strData), 0);
		struct packet data;
		recv(sockD, &data, sizeof(data), 0);
		printf("\nAlphabets: %d\nVowels: %d\nDigits: %d\nSpl Chars: %d\n",data.alpha,data.vowel,data.digit,data.other);
	}
	close(sockD);
	return 0;
}

