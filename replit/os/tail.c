#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
#include<fcntl.h>
int c=0,comp=0;
int len;
void tail(char *buf,int C)
{
  if(comp)
    return;
  char k='\0';
  if(C>c)
  {
    k=buf[len-1];
    if(k=='\n')
      c++;
    if(c==C)
      comp=1;
    len--;
    tail(buf,C);
      
  }
  if(!comp)
  {
    printf("%c",k);
  }
  comp=0;
}
int main(int argc, char *arg[])
{
  int fd=open(arg[1],O_RDONLY);
  char buf[1000]={0};
  len=read(fd,buf,1000);
  tail(buf,8);
  printf("/n%s",buf);
}