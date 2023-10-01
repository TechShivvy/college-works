#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/ioctl.h>
#include<netinet/in.h>
#include<net/if.h>
#include<arpa/inet.h>
#include<math.h>

int find_r(int m)
{
	int r=0;
	while(pow(2,r)<m+r+1)
		r++;
	return r;
}
void revStr(char *str)
{
	int n=strlen(str);
	char ch;
	for(int i=0;i<n/2;i++)
	{
		ch=str[i];
		str[i]=str[n-i-1];
		str[n-i-1]=ch;
	}
}
char *gen_enc_code(char *data,int r)
{
	int m=strlen(data),j=m-1;
	char *msg=(char*)malloc(sizeof(char)*(m+r+2));
	msg[0]='-';	
	for(int i=1;i<m+r+1;i++)
		msg[i]=((i&(i-1))==0)?'r':data[j--];
	msg[m+r+1]='\0';
	return msg;
}
void find_msg(char *msg,int r)
{
	for(int skip=1;skip<pow(2,r);skip=skip*2)
	{
		int _1=0;
		for(int i=skip;msg[i];i=i+skip)
		{
			int temp=skip;
			while(temp-- && i<strlen(msg))
			{
				if(msg[i++]=='1')
					_1++;
			}
		}
		msg[skip]=(_1&1)?'1':'0';
	}
}
int check(char *msg,int r)
{
	char red[r];
	red[r]='\0';
	int i_r=0,pos=0;
	for(int skip=1;skip<pow(2,r);skip=skip*2)
	{
		int _1=0;
		for(int i=skip;msg[i];i=i+skip)
		{
				int temp=skip;
				while(temp-- && i<strlen(msg))
				{
					//printf("-%d-",i);
					if(msg[i++]=='1')
						_1++;					
				}
		}
		//printf("\n");
		red[i_r++]=(_1&1)?'1':'0';
	}
	//printf("\nred: %s\n",red);
	printf("red: ");
	for(int i=strlen(red)-1;i>=0;i--)
		printf("%c",red[i]);
	printf("\n");
	for(int i=0;red[i];i++)
		pos+=(red[i]-'0')*pow(2,i);
	return pos;
}


