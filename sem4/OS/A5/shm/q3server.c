#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
# include<unistd.h>
# include<stdio.h>
# include<stdlib.h>
# include<string.h>
#include <sys/wait.h>
#include<ctype.h>
#include <signal.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h> 

struct memory{
    
    char content[200];
    int status,pid1,pid2;
};

struct memory* shmptr;

void handler(int signum)
{
    if(signum==SIGUSR1){

        printf("\r%32s",shmptr->content);
    }
}

int main()
{

    int pid=getpid();

    int shmid=shmget(111,sizeof(struct memory),IPC_CREAT|0666);

    shmptr=(struct memory *)shmat(shmid,NULL,0);

    shmptr->pid1=pid;
    shmptr->status=0;

    signal(SIGUSR1, handler);

    printf("\n-------------------------------\n");
    printf("\tCHAT APPLICATION\n");
    printf("-------------------------------\n");
    
    do
    {
        
        fgets (shmptr->content, 200, stdin);
        //printf("\n");
        //scanf("%s",shmptr->content);
        kill(shmptr->pid2,SIGUSR2);
    } while (1);

    shmdt((void*)shmptr);
    shmctl(shmid, IPC_RMID, NULL);
    
}
