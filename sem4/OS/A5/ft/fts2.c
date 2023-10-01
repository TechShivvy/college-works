# define NULL 0
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

struct memory 
{
    char readbuf[100];
    int status;
};

int main()
{
	struct memory* shmptr;
	
	
	//Initialization of shared memory and shmget returns an unique identifier in shmid
	int shmid = shmget((key_t)9876543, sizeof(struct memory), IPC_CREAT | 0666);
	//attachment to shared memory
    	shmptr = (struct memory*)shmat(shmid, NULL, 0);
    	
    	shmptr->status=0;
    	
    	//till input is given
    	while(!shmptr->status)
	{
	}
	
	while(1)
	{
		if(shmptr->status)
		{
			if (strcmp(shmptr->readbuf, "end")==0)
	      		{
	      			printf("\nEnded\n");
		 		break;
	      		}
			printf("\nFilename received: %s\nSending the requested file...\n",shmptr->readbuf);
			int file=open(shmptr->readbuf,O_RDONLY);
		      	sleep(1);	
		      	if(file==-1)
			{
				printf("File Error!\n");
			      	sprintf(shmptr->readbuf,"File Error!\n");
			}
			else
			{
				printf("Sent!\n");
			  	char contents[1024];
			      	read(file,contents,1024);
			      	close(file);
			      	strcpy(shmptr->readbuf,contents);
			}
			shmptr->status=0;
			wait(NULL);
		}
	}
	//detach from shared memory
	shmdt((void*)shmptr);
	
	// destroy the shared memory
    	shmctl(shmid, IPC_RMID, NULL);
	return 0;
}
