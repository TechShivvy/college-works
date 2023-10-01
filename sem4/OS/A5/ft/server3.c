#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include<math.h>

#define FIFO_FILE "/tmp/fifo_twoway"

void delay()
{
	for (int c = 1; c <= 32767; c++) 
       		for (int d = 1; d <= 32767; d++) 
       			{}
}

void reverse_string(char *);
int main()
{
	int fd;
   	char readbuf[1024];
   	char end[10];
	int to_end;
	int read_bytes;
   	char str[15];
  	/* Create the FIFO if it does not exist */
   	mkfifo(FIFO_FILE, S_IFIFO|0640);
   	strcpy(end, "end");
  	fd = open(FIFO_FILE, O_RDWR);
   	while(1)
   	{
        	read_bytes = read(fd, readbuf, sizeof(readbuf));
      		readbuf[read_bytes] = '\0';
      		printf("\nFile received: %s\nSending contents of requested file...\n",readbuf);
      		to_end = strcmp(readbuf, end);
      		if (to_end == 0)
      		{
         		close(fd);	
         		break;
      		}
      		int file=open(readbuf,O_RDONLY);

	        if(file==-1)
	        {
	      		strcpy(str,"File Error!\n");
	      		sprintf(readbuf,"File Error!");
	      	}
	      	else
	      	{
	      		strcpy(str,"Sent!\n");
	      		char contents[1024];
	      		read(file,contents,1024);
	      		//printf("%s",contents);
	      		close(file);
	      		strcpy(readbuf,contents);
	      	}	

	      	delay();
	      	printf("%s",str);
	      	write(fd, readbuf, strlen(readbuf));
	      	/*
	      	sleep - This is to make sure other process reads this, otherwise this
	      	process would retrieve the message
	      	*/
	      	sleep(3);
	}
  	return 0;
}

