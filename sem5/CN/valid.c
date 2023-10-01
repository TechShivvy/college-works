#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define YES printf("YES\n")
#define NO printf("NO\n")
int isValidIP(char *ip)
{
	/*struct sockaddr_in sa;
    	int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
    	return result != 0;*/
    	int bytes[4]={0};
    	if(4!=sscanf(ip, "%03d.%03d.%03d.%03d", &bytes[0], &bytes[1], &bytes[2], &bytes[3]))
    		return 0;
    	int len=3;
    	for(int i=0;i<4;i++)
    		len+=(bytes[i]?((int)log10((double)bytes[i]) + 1):1);
    	if(ip[len]=='.')
    		return 0;
    	int n=strlen(ip);
    	int i=n-1;
    	printf("ok");
	int ok=1;
    	for(int i=0;i<4;i++)
    	{
    		ok&=(bytes[i]<0 || bytes[i]>255)?0:1;
    		printf("%d\n",bytes[i]);
    	}
    	string s;
    	return ok;
}

int isValidMAC(char *mac)
{
	int bytes[6]={0};

    	if(6!=sscanf(mac, "%02x:%02x:%02x:%02x:%02x:%02x", &bytes[0], &bytes[1], &bytes[2], &bytes[3], &bytes[4], &bytes[5]))
    		//return 0;
    	printf("ok");
    	int ok=1;
    	for(int i=0;i<6;i++)
    	{
    		ok&=(bytes[i]<0 || bytes[i]>255)?0:1;
    		printf("%d\n",bytes[i]);
    	}
    	return ok;
}

int main()
{
	char ip[100],mac[100];
	strcpy(ip,"125.111.100.255d");
	strcpy(mac,"01:2A:45:67:89:AG");
	isValidIP(ip)?YES:NO;
	printf("\n");
	isValidMAC(mac)?YES:NO;
	return 0;
}
