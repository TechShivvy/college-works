#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <sys/types.h>
#include <unistd.h>
extern int errno;
#define SIZE 10
#define SHMPERM 0666
int segid;
int empty_id;
int full_id;
int mutex_id;
char *buff;
char *input_string;
sem_t *empty;
sem_t *full;
sem_t *mutex;
int p = 0, c = 0;

// Producer function
//void produce() {
int produce(void) {
int i = 0; while (1) {
if (i >= strlen(input_string)) {
printf("\nProducer %d exited!\n", getpid());
wait(NULL);
//return;
}
printf("\nProducer %d trying to acquire Semaphore Empty...\n", getpid());
sem_wait(empty);
printf("\nProducer %d successfully acquired Semaphore Empty!\n", getpid());
printf("\nProducer %d trying to acquire Semaphore Mutex...\n", getpid());
sem_wait(mutex);
printf("\nProducer %d successfully acquired Semaphore Mutex!\n", getpid());
buff[p] = input_string[i];
printf("\nProducer %d produced item [ %c ] !\n", getpid(), input_string[i]);
i++; p++;
printf("\nNumber of items written in Buffer: %d \n", p); sem_post(mutex);
printf("\nProducer %d released Semaphore Mutex!\n", getpid());
sem_post(full);
printf("\nProducer %d released Semaphore Full!\n", getpid()); sleep(2); }
}
// Consumer function
//void consume() {
int consume(void){
int i = 0; while (1) {
if (i >= strlen(input_string)) {
printf("\n Consumer %d exited \n", getpid());
//return;
}
printf("\nConsumer %d trying to acquire Semaphore Full... \n", getpid());
sem_wait(full);
printf("\nConsumer %d successfully acquired Semaphore Full!\n", getpid());
printf("\nConsumer %d trying to acquire Semaphore Mutex...\n", getpid());
sem_wait(mutex);
printf("\nConsumer %d successfully acquired Semaphore Mutex!\n", getpid());
printf("\nConsumer %d consumed item [ %c ]! \n", getpid(), buff[c]);
buff[c] = ' ';
c++;
printf("\nNumber of items read in Buffer: %d \n", c);
i++;
sem_post(mutex);
printf("\nConsumer %d released Semaphore Mutex! \n", getpid());
sem_post(empty);
printf("\nConsumer %d released Semaphore Empty! \n", getpid());
sleep(1);
}
}
int main() {
pid_t temp_pid;
segid = shmget(IPC_PRIVATE, SIZE, IPC_CREAT |IPC_EXCL | SHMPERM);
empty_id = shmget(IPC_PRIVATE, sizeof(sem_t), IPC_CREAT | IPC_EXCL | SHMPERM);
full_id = shmget(IPC_PRIVATE, sizeof(sem_t), IPC_CREAT | IPC_EXCL | SHMPERM);
mutex_id = shmget(IPC_PRIVATE, sizeof(sem_t), IPC_CREAT | IPC_EXCL | SHMPERM);
buff = shmat(segid, (char *) 0, 0);
empty = shmat(empty_id, (char *) 0, 0);
full = shmat(full_id, (char *) 0, 0);
mutex = shmat(mutex_id, (char *) 0, 0);
sem_init(empty, 1, SIZE);
sem_init(full, 1, 0);
sem_init(mutex, 1, 1);
printf("\nMain Process Started...\n");
printf("\nEnter the input string (20 characters MAX) : ");
input_string = (char *) malloc(20);
scanf("%s", input_string);
getchar();
printf("\nEntered string : %s\n", input_string);
temp_pid = fork();
if (temp_pid > 0) {
produce();
  sleep(10);
}
else {
consume();
}
shmdt(buff);
shmdt(empty);
shmdt(full);
shmdt(mutex);
shmctl(segid, IPC_RMID, NULL);
semctl(empty_id, 0, IPC_RMID, NULL);
semctl(full_id, 0, IPC_RMID, NULL);
semctl(mutex_id, 0, IPC_RMID, NULL);
sem_destroy(empty); sem_destroy(full);
sem_destroy(mutex);
printf("\nMain process exited \n");
return (0);
}