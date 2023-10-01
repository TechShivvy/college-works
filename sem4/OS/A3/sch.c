#include<stdio.h>
#include<stdlib.h>
struct proc
{
	char name[5];
	float bt;
	float at;
	float wt;
	float rt;
	float ta;
};
void FCFS()
{
	int n;
	float tbt=0,tta=0,twt=0,trt=0;
	printf("\n---------------FCFS Scheduler-----------\n");
	printf("Enter no of processes: ");
	scanf("%d",&n);
	struct proc P[n];
	for(int i=0;i<n;i++)
	{
		printf("\nEnter process ID: ");
		scanf("%s",P[i].name);
		printf("Arrival Time: ");
		scanf("%f",&P[i].at);
		printf("Burst Time: ");
		scanf("%f",&P[i].bt);
		if(i==0)
			P[i].wt=0;
		else
			P[i].wt=tbt-P[i].at;
		P[i].ta=P[i].wt+P[i].bt;
		tta+=P[i].ta;
		tbt+=P[i].bt;
		P[i].rt=P[i].wt;
		trt+=P[i].rt;
		twt+=P[i].wt;
	}
	printf("\n");
	for(int i=0;i<n;i++)
		printf("%s \t %0.2f \t %0.2f \t %0.2f \t %0.2f \t %0.2f\n",P[i].name,P[i].at,P[i].bt,P[i].ta,P[i].wt,P[i].rt);
	printf("\nAvg WT=%0.2f\tTotal Turnaround=%0.2f\tAvg RT=%0.2f",twt/n,tta/n,trt/n);
}
void SJF()
{

}
int main()
{
	int ch,ch2;
	do
	{
	printf("\nMenu:\n");
	printf("1.FCFS\n");
	printf("2.SJF\n");
	printf("3.EXIT\n");
	printf("Choice: ");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:FCFS();
			break;
		case 2:SJF();
			break;
		case 3: printf("\nExiting...\n");
			break;
		default:printf("\nInavlid Input!\n");	
	}
	}while(ch!=3);
}
