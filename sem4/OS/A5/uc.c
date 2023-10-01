# define NULL 0
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>
int main()
{
	//key_t key = ftok("shmfile",65);
	//int shmid = shmget(key,1024,0666|IPC_CREAT);
	
	//Initialization of shared memory and shmget returns an unique identifier in shmid
	int shmid=shmget((key_t)12345,1024,IPC_CREAT|0666);

	int pid=fork();

	if(pid>0) //parent
	{
		//attachment to shared memory
		char *str = (char*) shmat(shmid,NULL,0);
		
		//input
		printf("Enter a string: ");
		scanf("%[^\n]s",str);
		printf("\nPress anykey to convert to uppercase\n"); //2
		wait(NULL);
		
		//detach from shared memory
		shmdt(str);	
	}
	else	//child
	{
		getc(stdin);	//2
		//sleep(3);	//1
		//attachment to shared memory
		char *str = (char*) shmat(shmid,NULL,0);
		
		//output
		for (int i=0; str[i]!='\0';i++)
		{
      			if(str[i]>='a' && str[i]<='z')
      		   		str[i] = str[i]-32;
   		}
   		printf("String in Upper Case = %s\n", str);

		//detach from shared memory
		shmdt(str);
	}
	
	// destroy the shared memory
	shmctl(shmid,IPC_RMID,NULL);
	
	return 0;
}

