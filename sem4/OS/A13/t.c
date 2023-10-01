#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* this data is shared by the thread(s) */
int max,min;
float avg;
int size;

/* threads call these funx */
void *findAvg(void *arg);
void *findMax(void *arg);
void *findMin(void *arg);


int main(int argc, char *argv[])
{
	if(argc==1)
		return -1;
	/* the thread identifiers */
	pthread_t tid1;
	pthread_t tid2; 
	pthread_t tid3;  
	
	/* set of thread attributes */
	pthread_attr_t attr1; 
	pthread_attr_t attr2; 
	pthread_attr_t attr3; 

	int *nums = (int*)malloc((argc - 1)*sizeof(int));
	for(int i = 1; i < argc ; i++)
	{
		nums[i-1] = atoi(argv[i]);
	}
	size=argc-1;

	/* get the default attributes */
	pthread_attr_init(&attr1);
	/* create the thread */
	pthread_create(&tid1,&attr1,findAvg,(void*)nums);
	/* wait for the thread to exit */
	pthread_join(tid1,NULL);
	
	printf("\navg = %f\n",avg);
	
	/* get the default attributes */
	pthread_attr_init(&attr2);
	/* create the thread */
	pthread_create(&tid2,&attr2,findMax,(void*)nums);
	/* wait for the thread to exit */
	pthread_join(tid2,NULL);
	
	printf("\nmax = %d\n",max);
	
	/* get the default attributes */
	pthread_attr_init(&attr3);
	/* create the thread */
	pthread_create(&tid3,&attr3,findMin,(void*)nums);
	/* wait for the thread to exit */
	pthread_join(tid3,NULL);
	
	printf("\nmin = %d\n",min);
}

/* The thread will begin control in this function */
void *findAvg(void *arg)
{
	int *arr = (int *) arg;
	int sum=0;
	for(int i=0;i<size;i++)
	{
		sum+=arr[i];
	}
	avg=sum/size;
	pthread_exit(0);
}

void *findMax(void *arg)
{
	int *arr = (int *) arg;
	max=arr[0];
	for(int i=0;i<size;i++)
	{
		if(max<arr[i])
			max=arr[i];
	}
	pthread_exit(0);
}

void *findMin(void *arg)
{
	int *arr = (int *) arg;
	min=arr[0];
	for(int i=0;i<size;i++)
	{
		if(min>arr[i])
			min=arr[i];
	}
	pthread_exit(0);
}
