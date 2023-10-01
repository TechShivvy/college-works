#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/ioctl.h>
#include<netinet/in.h>
#include<net/if.h>
#include<arpa/inet.h>
#define YES printf("YES\n")
#define NO printf("NO\n")

char *IP()
{
	struct ifreq ifr;
	int n=socket(AF_INET,SOCK_DGRAM,0);
	ifr.ifr_addr.sa_family=AF_INET;
	strncpy(ifr.ifr_name,"ens33",IFNAMSIZ-1);
	ioctl(n,SIOCGIFADDR,&ifr);
	close(n);
	return inet_ntoa(((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr);
}
char *MAC()
{
	struct ifreq ifr;
	int n=socket(AF_INET,SOCK_DGRAM,0);
	ifr.ifr_addr.sa_family = AF_INET;
	strncpy(ifr.ifr_name,"ens33",IFNAMSIZ-1);
	ioctl(n,SIOCGIFHWADDR,&ifr);
	close(n);
	unsigned char* mac=(unsigned char*)ifr.ifr_hwaddr.sa_data;
	sprintf(mac,"%.2X:%.2X:%.2X:%.2X:%.2X:%.2X",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
	return mac;
}
int main()
{
	char ip[100],mac[100];
	strcpy(ip,"125.11.111.256");
	strcpy(mac,"01:2A:45:67:89:AA");
	struct sockaddr_in addr;
	//strcpy(ip,IP());
	//printf("%s",ip);
	//printf("\n%s",MAC());
	unsigned char *a=(void *)&addr,dummy;
	if(sscanf(ip,"%3hhd.%3hhd.%3hhd.%3hhd%c",a,a+1,a+2,a+3,&dummy)!=4)
		printf("invalid");
	else
		printf("valid");
	printf("%u\n",a+1);
	int arr[4];
	for(int i=0;i<4;i++)
		arr[i]=a[i];
	for(int i=0;i<4;i++)
		printf("%d ",arr[i]);
	printf("\n");
	if(!inet_aton(ip,&addr.sin_addr))
		printf("invalid");
	else
		printf("valid");
	//isValidIP(ip)?YES:NO;
	//printf("\n");
	//isValidMAC(mac)?YES:NO;
	return 0;
}
