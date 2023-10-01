#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#define YES printf("YES\n")
#define NO printf("NO\n")
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
			if(!num && ptr[0]!='\0')
				return 0;
			if(num<0 || num>255)
				return 0;
    			memset(s, 0, 10);
		}
	}
	return 1;
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
/*
int main()
{
	char ip[100],mac[100];
	strcpy(ip,"125.111.100.256678");
	strcpy(mac,"01:2A:45:67:89:AA");
	isValidIP(ip)?YES:NO;
	printf("\n");
	isValidMAC(mac)?YES:NO;
	return 0;
}8/
