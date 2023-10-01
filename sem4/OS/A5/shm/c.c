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

struct memory 
{
    char readbuf[100];
    int end1,end2,pid1,pid2;
};
struct memory* shmptr;

char *strstrip(char *s) // to strip the string from l and r
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
    // if signum is SIGUSR2, then user 2 is receiving a message from user1
	if(signum==SIGUSR2)
		printf("\r%43s",shmptr->readbuf);
}

int main()
{
	//pid of client
	int pid = getpid();
	
	//Initialization of shared memory and shmget returns an unique identifier in shmid -> Checking whether already created(i.e., whether server is complied b4 client)
	int shmid = shmget((key_t)9876, sizeof(struct memory), IPC_CREAT | IPC_EXCL|0666);
	if(shmid!=-1)
	{
		printf("Server not active!\n");
		shmctl(shmid, IPC_RMID, NULL);
		return 0;
	}
	
	//Initialization of shared memory and shmget returns an unique identifier in shmid
	shmid = shmget((key_t)9876, sizeof(struct memory), 0666);

	//attachment to shared memory
    	shmptr = (struct memory*)shmat(shmid, NULL, 0);

	//storing pid in shm
	shmptr->pid2 = pid;
	shmptr->end1=0;
	shmptr->end2=0;
	
	// calling the signal function using signal type SIGUSR2
	signal(SIGUSR2, handler);
	
	printf("\n------------------------------------------\n");
	printf("\t     CHAT APPLICATION\n");
	printf("------------------------------------------\n");

	
    	do
    	{
    		//input
    		fgets(shmptr->readbuf, 200, stdin);
    		if(shmptr->end1)
    			break;
    		shmptr->end2=0;
    		//to strip string from l and r (removes spaces)	
        	strcpy(shmptr->readbuf,strstrip(shmptr->readbuf));
     		
     		//if empty string
     		if(strlen(shmptr->readbuf)==0||strcmp(shmptr->readbuf,"\n")==0)
	     		continue;
     		
     		if(strcmp(shmptr->readbuf,"bye\n")==0)
     			shmptr->end2=1;
     		
             	//sending the message to user1 using kill function
        	kill(shmptr->pid1, SIGUSR1);
        	
    	}while(!(shmptr->end1&&shmptr->end2));
    	kill(shmptr->pid1, SIGUSR1);
    	
    	//detach from shared memory
	shmdt((void*)shmptr);
	return 0;
}

