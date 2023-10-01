#define NULL 0
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
struct memory
{
	int status,pid1,pid2,pid3;
	char buf[100];
};


struct memory* shmptr;

void handler(int signum)
{
	if(signum==SIGUSR2)
		printf("\r%43s",shmptr->buf);
}

int main()
{
	int shmid=shmget((key_t)1234,sizeof(struct memory),IPC_CREAT|IPC_EXCL|0600);
	if(shmid!=-1)
	{
		printf("Srver no");
		shmctl(shmid,IPC_RMID,NULL);
		return -1;
	}
	shmid=shmget((key_t)1234,sizeof(struct memory*),0600);
	shmptr=(struct memory*)shmat(shmid,NULL,0);
	shmptr->pid2=getpid();
	shmptr->status=1;
	signal(SIGUSR2,handler);
	do
	{
		fgets(shmptr->buf,sizeof(shmptr->buf),stdin);
		if(strcmp(shmptr->buf,"bye\n")==0)
			shmptr->status=0;
		kill(shmptr->pid1,SIGUSR1);
	}while(shmptr->status);
	shmdt(shmptr);
	shmctl(shmid,IPC_RMID,NULL);
}
