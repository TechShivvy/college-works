#include <stdio.h>
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <unistd.h> 

int shmid;
int main(void) 
{ 
  pid_t f=fork();
  shmid=shmget(123,sizeof(char *),IPC_CREAT|0600);
   if(f>0){
    char *a = (char*) shmat(shmid,NULL,0);
    printf("Integer: ");
    scanf("%s", a);
    wait(NULL);
    shmdt(a);
  }
  else{
  getc(stdin);
   char *a = (char*) shmat(shmid,NULL,0);
    if(atoi(a)%2==0) 
    	printf("Even\n");
    else 
    	printf("Odd\n");
    shmdt(a);
  }
  shmctl(shmid,IPC_RMID, NULL);
  return 0;
}
