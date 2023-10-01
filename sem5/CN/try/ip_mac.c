#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/ioctl.h>
#include<netinet/in.h>
#include<net/if.h>

char* MAC()
{
	char temp[100], *mac=(char*)malloc(sizeof(char)*500);
	struct ifreq s;
	int fd=socket(PF_INET,SOCK_DGRAM,IPPROTO_IP);
	strcpy(mac,"");
	strcpy(s.ifr_name,"ens33");
	if(ioctl(fd,SIOCGIFHWADDR,&s)==0)
	{
		for(int i=0;i<6;i++)
		{
			sprintf(temp,"%02x%s",(unsigned char)s.ifr_addr.sa_data[i],(i<5?":":""));
			strcat(mac,temp);
		}
	}
	close(fd);
	return mac;
}
char *IP()
{
	char *ip=(char*)malloc(sizeof(char)*500);
	int fd=socket(AF_INET,SOCK_DGRAM,0);
	struct ifreq ifr;
	strncpy(ifr.ifr_name,"ens33",IFNAMSIZ-1);
	ioctl(fd,SIOCGIFADDR,&ifr);
	close(fd);
	sprintf(ip,"%s",inet_ntoa(((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr));
	return ip;
}
int main()
{
	char *mac=MAC();
	printf("%s\n",mac);
	char *ip=IP();
	printf("%s\n",ip);
	return 0;
}
int isValidIP(char *ip)
{
	int dot_cnt=0;
	for(int i=0;ip[i];i++)
	{
		if(ip[i]=='.')
			dot_cnt++;
		else if(ip[i]<'0' || ip[i]>'9')
			return 0;
	}
	if(dot_cnt!=3)
		return 0;
	strcat(ip,".");
	char s[10]={0},temp[2];
	temp[1]='\0';
	int ok=1;
	for(int i=0;ip[i];i++)
	{
		temp[0]=ip[i];	
		if(ip[i]!='.')
			strcat(s,temp);	
		else
		{
			strcat(s,"\0");
  			char *ptr;
   			long num= strtol(s, &ptr, 10);
			ok&=((!num && ptr[0]!='\0')||(num<0 || num>255))?0:1;
    			memset(s, 0, 10);
		}
	}
	ip[strlen(ip)-1]='\0';
	return ok;
}

int isValidMAC(char *mac)
{
	int col_cnt=0;
	for(int i=0;mac[i];i++)
	{
		if(mac[i]==':')
			col_cnt++;
		else if(!isdigit(mac[i]) && (!isalpha(mac[i]) || ( isalpha(mac[i]) && (mac[i]<'a' || mac[i]>'f'))))
			return 0;
	}
	if(col_cnt!=5)
		return 0;
	for(int i=2;mac[i];i=i+3)
		if(mac[i]!=':')
			return 0;
	return 1;
}
