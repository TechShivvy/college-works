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
	//Initialization of shared memory and shmget returns an unique identifier in shmid -> Checking whether already created(i.e., whether server is complied b4 client)
	int shmid = shmget((key_t)9876543, sizeof(struct memory), IPC_CREAT | IPC_EXCL|0666);
	if(shmid!=-1)
	{
		printf("Server not active!\n");
		shmctl(shmid, IPC_RMID, NULL);
		return 0;
	}
	
	//Initialization of shared memory and shmget returns an unique identifier in shmid
	shmid = shmget((key_t)9876543, sizeof(struct memory), 0666);
	
	//attachment to shared memory
    	shmptr = (struct memory*)shmat(shmid, NULL, 0);
    	shmptr->status=0;
    	
	while(1)
	{
		printf("Enter the Filename: ");
		scanf("%[^\n]s",shmptr->readbuf);
		getc(stdin);
		wait(NULL);
		shmptr->status=1;
	      	if (strcmp(shmptr->readbuf, "end")==0)
	      	{
			shmptr->status=0;
	      		wait(NULL);
		 	break;
	      	}
	      	printf("Requesting File Contents...\n");
		while(shmptr->status);
		printf("Received File Contents: \n%s\n",shmptr->readbuf);
	}
	//detach from shared memory
	shmdt((void*)shmptr);
	return 0;
}
