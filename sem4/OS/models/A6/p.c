#define NULL 0
#define BUFSIZE 10
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>

struct memory
{
	int status,count,n;
	int buf[BUFSIZE];
	sem_t empty,full,mutex;
};
struct memory *shmptr;

int main()
{
	srand(time(NULL));
	int shmid=shmget((key_t)123,sizeof(struct memory),IPC_CREAT|0600);
	shmptr=(struct memory*)shmat(shmid,NULL,0);
	shmptr->status=0;
	shmptr->count=0;
	while(!shmptr->status);
	//int i=shmptr->n;
	printf("\n-------Producer and Consumer Problem-------\n");
	while(1)
	{
		if(shmptr->status!=0)
		{
			int i=shmptr->n;
			do
			{
				sem_wait(&(shmptr->empty));
				sem_wait(&(shmptr->mutex));
				shmptr->buf[shmptr->count++]=rand()%100;
				printf("Produced %d\n",shmptr->buf[shmptr->count-1]);
				i--;
				sem_post(&(shmptr->mutex));
				sem_post(&(shmptr->full));
				sleep(1);
			}while(i>0);
			printf("\nAll items produced\n");
			if(i==0)
				break;
		}
	}
	sem_destroy(&(shmptr->empty));
	sem_destroy(&(shmptr->full));
	sem_destroy(&(shmptr->mutex));
	
	shmdt(shmptr);
	shmctl(shmid,IPC_RMID,NULL);
	
	return 0;
}
