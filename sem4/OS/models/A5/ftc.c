#define NULL 0
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/types.h>

struct memory
{
	char buffer[100];
	int status;
};

int main()
{
	struct memory *shmptr;
	int shmid=shmget((key_t)1234,sizeof(struct memory*),IPC_CREAT|IPC_EXCL|0600);
	if(shmid!=-1)
	{
		printf("Srver no");
		shmctl(shmid,IPC_RMID,NULL);
		return -1;
	}
	shmid=shmget((key_t)1234,sizeof(struct memory*),0600);
	shmptr=(struct memory*)shmat(shmid,NULL,0);
	shmptr->status=0;
	
	printf("fname:");
	scanf("%s",shmptr->buffer);
	getc(stdin);
	wait(NULL);
	shmptr->status=1;
	while(shmptr->status);
	printf("%s",shmptr->buffer);
	shmptr->status=1;
	wait(NULL);
	shmdt(shmptr);
	return 0;
}
