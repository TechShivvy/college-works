#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
// parent writing a char in shared memory and child reads it and prints it.
int main(){
int pid;
char *a,*b;
int id,n,i;
// you can create a shared memory between parent and child here or you can
//create inside them separately.
pid=fork();
if(pid>0) //parent
{
key_t key = ftok("shmfile",65);
int id = shmget(key,1024,0666|IPC_CREAT);
a=shmat(id,NULL,0);
printf("Enter name: \n");
scanf("%s",a);
wait(NULL);
shmdt(a);
}
else //child
{
sleep(3);
key_t key = ftok("shmfile",65);
int id = shmget(key,1024,0666|IPC_CREAT);
b=shmat(id,NULL,0);
for(i=0; b[i]; i++){
b[i] = toupper(b[i]);
}
printf("\nUpper: %s\n",b);
shmdt(b);
}
shmctl(id, IPC_RMID,NULL);
}
