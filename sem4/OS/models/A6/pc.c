#define NULL 0
#define BUFSIZE 10
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
struct memory
{
	int count;
	char buffer[BUFSIZE];
	sem_t mutex,full,empty;
};
struct memory *shmptr;
char str[BUFSIZE];
int in=0;
int out=0;

void producer()
{
	do
	{
		sem_wait(&(shmptr->empty));
		sem_wait(&(shmptr->mutex));
		
		shmptr->buffer[shmptr->count++]=str[in++];
		shmptr->buffer[shmptr->count]='\0';
		
		printf("Produced: %c\n",shmptr->buffer[shmptr->count-1]);
		printf("Avail: %s\n",shmptr->buffer);
		
		sem_post(&(shmptr->mutex));
		sem_post(&(shmptr->full));
		sleep(2);
	}while(in<strlen(str));
	wait(NULL);
	printf("All items produced");
	exit(1);
}
void consumer()
{
	do
	{
		sem_wait(&(shmptr->full));
		sem_wait(&(shmptr->mutex));
		
		printf("Consumed: %c\n",shmptr->buffer[out++]);
		shmptr->count--;
		
		printf("Avail: %s\n",shmptr->buffer+out);
		
		sem_post(&(shmptr->mutex));
		sem_post(&(shmptr->empty));
		sleep(1);
	}while(out<strlen(str));
	wait(NULL);
	printf("All items produced");
	exit(1);
}

int main()
{
	int shmid=shmget((key_t)12345,sizeof(struct memory),IPC_CREAT|0600);
	shmptr=(struct memory*)shmat(shmid,NULL,0);
	
	sem_init(&(shmptr->full),1,0);
	sem_init(&(shmptr->empty),1,BUFSIZE);
	sem_init(&(shmptr->mutex),1,1);
	printf("Enter the string(max size 10) : ");
	scanf("%s",str);
	
	int pid=fork();
	if(pid>0)
	{
		producer();	
	}
	else
	{
		consumer();
	}
	shmdt(shmptr);
	shmctl(shmid,IPC_RMID,NULL);
	sem_destroy(&(shmptr->full));
	sem_destroy(&(shmptr->empty));
	sem_destroy(&(shmptr->mutex));
	return 0;
}
