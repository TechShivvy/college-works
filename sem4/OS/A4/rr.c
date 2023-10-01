#include<stdio.h>
#include<stdlib.h>
struct process
{
	char pid[5];
	int at,bt,tat,wt,rt,st,ct,id,comp;
};
char time[1000][5];
void swap(struct process *xp,struct process *yp)
{
	struct process temp=*xp;
	*xp=*yp;
	*yp=temp;
}
void sort(struct process *P,int n)
{
	int min_i;
	for(int i=0;i<n;i++)
	{
		min_i=i;
		for(int j=i+1;j<n;j++)
		{
			if(P[j].at<P[min_i].at)
				min_i=j;
		}
		if(min_i!=i)
			swap(&P[min_i],&P[i]);
	}
	for(int i=0;i<n;i++)
	{
		min_i=i;
		for(int j=i+1;j<n;j++)
		{
			if(P[j].at==P[min_i].at && P[j].id<P[min_i].id)
				min_i=j;
		}
		if(min_i!=i)
			swap(&P[min_i],&P[i]);
	}
}

int input(struct process *P,int n)
{
	int sorted=1;
	for(int i=0;i<n;i++)
	{
		printf("Enter pid: ");
		scanf("%s",P[i].pid);
		printf("Enter Ariival time: ");
		scanf("%d",&P[i].at);
		if(i!=0 && sorted)
			sorted=P[i].at>P[i-1].at?1:0;
		printf("Enter burst time: ");
		scanf("%d",&P[i].bt);
		P[i].id=i+1;
		printf("\n");
	}
	return sorted;
}

void output(struct process P[],int n)
{
	for(int i=0;i<n;i++)
	{
		printf("pid: %s\n",P[i].pid);
		printf("Ariival time: %d\n",P[i].at);
		printf("burst time: %d\n\n",P[i].bt);
	}
}

void roundRobin()
{
	int n,comp=0,count=0;
	printf("Enter the number of processes: ");
	scanf("%d",&n);
	struct process P[n];
	int sorted=input(P,n);
	if(!sorted)
	{
		sort(P,n);
	}
	//output(P,n);
	int tq;
	printf("Enter time quantum: ");
	scanf("%d",&tq);
	int rem_t[n];
	for(int i=0;i<n;i++)
		P[i].bt=rem_t[i];
	int k=0,timer=0;
	
    	while(1)
    	{
    		/*int flag = 0;
		for(int i = 0; i < n; i++){
		    if(comp){
		        flag +=1;
		        break;
		    }
		}
		if(flag==n)
		    break;*/
		if(count==n)
			break;
		if(timer<P[k].at)
			timer+=P[k].at;
		else
		{
			if(!rem_t[k])
			{
				count++;
				P[k].comp=1;
				P[k].ct=timer;
				continue;
			}
			if(rem_t[k]>=tq)
			{
				rem_t[k]-=tq;
				timer+=tq;
			}
			else
			{
				if(rem_t[k]>=0)
				{
					timer+=rem_t[k];
					rem_t[k]=0;
				}
			}	
		}
    	}
	/*do
	{
		for(i=0;i<n;i++)
		{
			if(curr_time<P[i].at)
				cur_time+=P[i--].at;
			else
			{
				if(!rem_t[i])
				{
					comp++;
					continue;
				}
				if(rem_t[i]>=tq)
				{
					rem_t[i]-=tq;
					cur_time+=tq;
				}
				else
				{
					if(rem_t>=0)
					{
						rem_t[i]=0;
					}
				}
			}
		}
	}while(n!=comp);*/
}

void priority()
{
	int n;
	printf("Enter the number of processes: ");
	scanf("%d",&n);
	struct process P[n];
	input(P,n);
}

int main()
{
	int ch;
	for(int i=;i<1000;i++)
		strcpy(time[i],"  ");
	printf("\nMenu:\n");
	printf("1.ROUND ROBIN\n");
	printf("2.PRIORITY\n");	
	printf("Enter you choice: ");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1: printf("\nROUND ROBIN SHCEDULER\n");
			roundRobin();
			break;
		case 2: printf("\nPRIORITY SHCEDULER\n");
			priority();
			break;
	}
	return 0;
}
