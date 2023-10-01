#define NULL 0
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

struct memory
{
	char buffer[100];
	int status;
};

int main()
{
	struct memory *shmptr;
	int shmid=shmget((key_t)1234,sizeof(struct memory*),IPC_CREAT|0600);
	shmptr=(struct memory*)shmat(shmid,NULL,0);
	shmptr->status=0;
	while(!shmptr->status);
	
	int file=open(shmptr->buffer,O_RDONLY);
	int nr;
	char *buf=(char*)malloc(500*sizeof(char));
	nr=read(file,buf,10000);
	strcpy(shmptr->buffer,buf);
	shmptr->status=0;
	
	wait(NULL);
	while(!shmptr->status);
	shmdt(shmptr);
	shmctl(shmid,IPC_RMID,NULL);
}
