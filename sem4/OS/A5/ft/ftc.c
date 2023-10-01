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
    int on;
};

int main()
{
	struct memory* shmptr;
	//Initialization of shared memory and shmget returns an unique identifier in shmid
	int shmid = shmget((key_t)69, sizeof(struct memory), IPC_CREAT | 0666);
	
	//attachment to shared memory
    	shmptr = (struct memory*)shmat(shmid, NULL, 0);
    	shmptr->status=0;
    	shmptr->on=0;
    	wait(NULL);
    	
    	//server active or not
    	if(shmptr->on!=1)
    	{
    		printf("Server is not active!\n");
    		return 0;
    	}
	
	
	do
	{
		printf("Enter the Filename: ");
		scanf("%[^\n]s",shmptr->readbuf);
		getc(stdin);
		wait(NULL);
		shmptr->status=1;
	      	if (strcmp(shmptr->readbuf, "end")==0)
	      	{
	      		shmptr->on=0;
	      		wait(NULL);
		 	break;
	      	}
		while(shmptr->status);
		printf("\nReceived File Contents: \n%s\n",shmptr->readbuf);
	}while(shmptr->on);
	
	//detach from shared memory
	shmdt((void*)shmptr);
	
	// destroy the shared memory
    	shmctl(shmid, IPC_RMID, NULL);
	return 0;
}
