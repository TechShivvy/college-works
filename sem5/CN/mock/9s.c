#include "9hc.h"

int main(int argc,char *argv[])
{
	int sockS=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(9001);
	addr.sin_addr.s_addr=INADDR_ANY;
	
	bind(sockS,(struct sockaddr*)&addr,sizeof(addr));
	listen(sockS,1);
	int sockC=accept(sockS,NULL,NULL);
	
	char *msg=(char*)malloc(sizeof(char)*(500)),rev_str[255];
	recv(sockC,msg,sizeof(msg),0);
	printf("data recv: %s, %d\n",msg+1,strlen(msg));
	strcpy(rev_str,msg);
	revStr(rev_str+1);
	int pos=check(rev_str,ceil(log2(sizeof(rev_str))));
	if(!pos)
		printf("\nThere's no error in the data recieved\n");
	else
	{
		printf("\nThere's error in the received Data!\n");
		printf("\nBit-position %d is changed!\n",pos);
		rev_str[pos]=(rev_str[pos]=='0'?'1':'0');
		strcpy(msg,rev_str);
		revStr(msg+1);
		printf("\nCorrect Original Data: %s\nProof: ",msg+1);
		check(msg,ceil(log2(sizeof(rev_str))));
	}
	int k=0;
	char data[255];
	for(int i=0;rev_str[i];i++)
		if(i&(i-1))
			data[k++]=rev_str[i];
	data[k]='\0';
	revStr(data);
	close(sockS);
	
	printf("\nTransmitted Data Bit: %s\n",data);
	return 0;
	return 0;
}
