//Client1.c
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include<unistd.h>
#include<time.h>
#include<sys/shm.h>


#include<sys/wait.h>



struct mesgq{
	long type;
	char text[200]; 
}mq;

int blue () {
  printf("\033[0;34m");
  return 1;
}
int green (){
  printf("\033[0;32m");
  return 1;
}
int reset () {
  printf("\033[0m");
  return 1;
}

void main(){
	int msqid1, len;
	key_t key1 = 1000;
	int shmid=shmget((key_t)12345,1024,IPC_CREAT|0666);
	int shmid2=shmget((key_t)1234,1024,IPC_CREAT|0666);
	char *server = (char*) shmat(shmid,NULL,0);
	char *client = (char*) shmat(shmid2,NULL,0);
	if ((msqid1 = msgget(key1, 0644)) == -1){
		printf("Server not active\n");
		exit(1);
	}
	int pid=fork();
	if(pid>0) //parent
	{
		printf("Client 1 Ready!\n");
		printf("Enter your name: ");	//2nd v
		scanf("%s",client);
		printf("\n\nWaiting to receive msg from the other end..\n\n");
		wait(NULL);
		
		//detach from shared memory
		//shmdt(client);	
	}
	else
	{
		sleep(1);
		//sleep(2);
		//attachment to shared memory
		//char *client = (char*) shmat(shmid2,NULL,0);
	//printf("Client 1 Ready!\n");
	//printf("Enter name: ");	//2nd v
	//scanf("%s",client);		//2nd v
	//sleep(3);
	while (msgrcv(msqid1, &mq, sizeof(mq.text), 1, 0) != -1){
		blue();
		printf("\n%s: ",server);	//2nd version
		//printf("\nServer: "); 	//1st version
		reset();
		printf("%s\n", mq.text);
		green();
		printf("You: ");
		reset();
		fgets(mq.text, sizeof(mq.text),stdin);
		len = strlen(mq.text);
		if (mq.text[len-1] == '\n')
		mq.text[len-1] = '\0';
		msgsnd(msqid1, &mq, len+1, 0);
	}
	}
	printf("Server Disconnected\n");
	shmdt(server);
	shmctl(shmid,IPC_RMID,NULL);
	shmdt(client);
	shmctl(shmid2,IPC_RMID,NULL);
}
