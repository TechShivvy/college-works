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
#define U1 1 //server
#define U2 2 //client
struct memory 
{
    char readbuf[100];
    int status;
};
void print(int user)
{
    if (user == U1)
    {
        printf("%32s", shmptr->content);
    }
}
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
    	while(1)
    	{
    		if(strcmp(shmptr->readbuf,"\0")!=0)
    			print(shmptr->status);
	}
    	
    	//detach from shared memory
	shmdt((void*)shmptr);
	return 0;
}

