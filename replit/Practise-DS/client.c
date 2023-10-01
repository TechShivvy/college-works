//Client1.c
#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

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

	if ((msqid1 = msgget(key1, 0644)) == -1){
		printf("Server not active\n");
		exit(1);
	}
	printf("Client 1 Ready!\n");
	while (msgrcv(msqid1, &mq, sizeof(mq.text), 1, 0) != -1){
		blue();
		printf("\nServer: ");
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
	printf("Server Disconnected\n");
}
