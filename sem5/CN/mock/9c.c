#include "9hc.h"

int main(int argc,char *argv[])
{
	int sockS=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(9001);
	addr.sin_addr.s_addr=INADDR_ANY;
	
	int connex=connect(sockS,(struct sockaddr*)&addr,sizeof(addr));
	char data[]="1011010";
	int r=find_r(strlen(data));
	char *msg=gen_enc_code(data,r);
	printf("Data bit: %s",data);
	find_msg(msg,r);
	int l=strlen(msg),flag=0;
	revStr(msg+1);
	printf("Data to be transmitted to server: %s",msg+1);
	printf("\nWant to change bits(y/n): ");
	char ch;
	scanf(" %c",&ch);
	switch(ch)
	{
		case 'y':
		case 'Y':
				printf("Enter pos(i-%d):",l-1);
				int pos;
				scanf("%d",&pos);
				if(pos<1||pos>l-1)
					printf("Invaid!");
				else
				{
					msg[l-pos]=(msg[l-pos]=='0'?'1':'0');
					flag=1;
				}
				break;
		case 'n':case 'N':break;
		default:	printf("\nInvalid choice!\n");
		}
	char MSG[255];
	strcpy(MSG,msg);
	printf("Data to be transmitted to server: %s",MSG+1);	
	send(sockS,MSG,sizeof(MSG),0);
	printf("\nData has been sent %s!\n",(flag?"with error":"without error"));
	close(sockS);
	return 0;
}
