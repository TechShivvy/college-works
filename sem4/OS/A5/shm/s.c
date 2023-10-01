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
#include<ctype.h>

//server -> user 1
//client -> user 2
struct memory 
{
    char readbuf[100];
    int end1,end2,pid1,pid2;
};
struct memory* shmptr;

char *strstrip(char *s)
{
        size_t size;
        char *end;

        size = strlen(s);

        if (!size)
                return s;

        end = s + size - 1;
        while (end >= s && isspace(*end))
                end--;
        *(end + 1) = '\0';

        while (*s && isspace(*s))
                s++;
	strcat(s,"\n");
        return s;
}

// handler function to print message received from user2
void handler(int signum)
{
	// if signum is SIGUSR1, then user 1 is receiving a message from user 2
	if(signum==SIGUSR1)
		printf("\r%43s",shmptr->readbuf);
}



int main()
{
	// process id of server
	int pid = getpid();

	//Initialization of shared memory and shmget returns an unique identifier in shmid
	int shmid = shmget((key_t)9876, sizeof(struct memory), IPC_CREAT | 0666);
	
	//attachment to shared memory
    	shmptr = (struct memory*)shmat(shmid, NULL, 0);
    	
    	//storing pid in shm
    	shmptr->pid1=pid;
    	shmptr->end1=0;
    	shmptr->end2=0;
    	
	// calling the signal function using signal type SIGUSER1
    	signal(SIGUSR1, handler);
    	
    	
    	printf("\n------------------------------------------\n");
	printf("\t      CHAT APPLICATION\n");
	printf("------------------------------------------\n");
	
    	do
    	{
    		
    		//input
    		fgets(shmptr->readbuf, 200, stdin);
    		if(shmptr->end1)
    			break;
   		shmptr->end1=0;
        	//to strip string from l and r (removes spaces)	
        	strcpy(shmptr->readbuf,strstrip(shmptr->readbuf));
     		
     		//if empty string
     		if(strlen(shmptr->readbuf)==0||strcmp(shmptr->readbuf,"\n")==0)
     		{
        		continue;
        	}
        	
        	if(strcmp(shmptr->readbuf,"bye\n")==0)
     			shmptr->end1=1;
     			
     		// sending the message to user2 using kill function
        	kill(shmptr->pid2, SIGUSR2);
        	
    	}while(!(shmptr->end1&&shmptr->end2));
	kill(shmptr->pid2, SIGUSR2);
	
    	//detach from shared memory
	shmdt((void*)shmptr);
	
	// destroy the shared memory
    	shmctl(shmid, IPC_RMID, NULL);
	return 0;
}

