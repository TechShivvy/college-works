#define NULL 0
#define BUFSIZE 10
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

struct memory
{
	int status,count,n;
	int buf[BUFSIZE];
	sem_t empty,full,mutex;
};
struct memory *shmptr;

int main()
{
	int shmid=shmget((key_t)123,sizeof(struct memory),0600);
	shmptr=(struct memory*)shmat(shmid,NULL,0);
	sem_init(&(shmptr->full),1,0);
	sem_init(&(shmptr->empty),1,BUFSIZE);
	sem_init(&(shmptr->full),1,1);
	
	shmptr->status=0;
	
	printf("n:");
	scanf("%d",&(shmptr->n));
	shmptr->status=1;
	int c=0;
	//while(shmptr->status);
	do
	{
		sem_wait(&(shmptr->full));
		sem_wait(&(shmptr->mutex));
		printf("Available items : ");
		printf("%d ",shmptr->buf[0]);
		printf("\n");
		printf("Consumed %d\n",shmptr->buf[0]);
		memmove(shmptr->buf,shmptr->buf+1,sizeof(shmptr->buf));
		shmptr->count--;
		c++;
		sem_post(&(shmptr->mutex));
		sem_post(&(shmptr->empty));
		sleep(1);
	}while(c<shmptr->n);
	
	
	sem_destroy(&(shmptr->empty));
	sem_destroy(&(shmptr->full));
	sem_destroy(&(shmptr->mutex));
	shmdt(shmptr);
	return 0;
}

