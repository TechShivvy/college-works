#define NULL 0
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
	int shmid=shmget((key_t)1234,sizeof(char*),IPC_CREAT|0600);
	
	int pid=fork();
	if(pid>0)
	{
		char *str=(char*)shmat(shmid,NULL,0);	
		printf("Enter string: ");
		scanf("%[^\n]s",str);
		printf("\npress any key to convert: \n");
		wait(NULL);	
		shmdt(str);	
	}
	else
	{
	 	getc(stdin);
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
	shmctl(shmid,IPC_RMID,NULL);
	return 0;
}
