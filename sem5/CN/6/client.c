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
	
    int sockD = socket(AF_INET, SOCK_STREAM, 0); 
    
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port= htons(port);
    servAddr.sin_addr.s_addr = INADDR_ANY;
    
    int connectStatus= connect(sockD, (struct sockaddr*)&servAddr,sizeof(servAddr));
    if (connectStatus == -1) {
        printf("Error...\n");
    }
    else {
        char strData1[255],strData2[255];
        
        printf("Enter the file to be copied:");
        scanf("%s",strData1);
        send(sockD,strData1, sizeof(strData1), 0);
        
        char rep[255];
        recv(sockD, rep, sizeof(rep), 0);
        
        if(!strcmp(rep,"-1"))
        	printf("Does not exist!\n");
        else
        {
        
		printf("Enter the file to be copied in:");
		scanf("%s",strData2);

		printf("%s",rep);
		
		int fd = open(strData2,O_CREAT|O_WRONLY, 0777);
		write(fd,rep,strlen(rep));
		printf("Copied to file2\n");
		close(fd);
	}
    }
    return 0;
}
