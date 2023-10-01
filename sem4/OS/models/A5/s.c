#define NULL 0
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
#define SIGUSR3 SIGWINCH

struct memory
{
	int status,pid1,pid2,pid3;
	char buf[100];
};

struct memory* shmptr;
void handler(int signum)
{
	if(signum==SIGUSR1)
		printf("\r%43s",shmptr->buf);
}


int main()
{
	int shmid=shmget((key_t)1234,sizeof(struct memory),IPC_CREAT|0600);
	shmptr=(struct memory*)shmat(shmid,NULL,0);
	shmptr->pid1=getpid();
	shmptr->status=1;
	signal(SIGUSR1,handler);
	do
	{
		fgets(shmptr->buf,sizeof(shmptr->buf),stdin);
		if(strcmp(shmptr->buf,"bye\n")==0)
			shmptr->status=0;
		kill(shmptr->pid2,SIGUSR2);
		kill(shmptr->pid3,SIGUSR3);
	}while(shmptr->status);
	shmdt(shmptr);
	shmctl(shmid,IPC_RMID,NULL);
}
