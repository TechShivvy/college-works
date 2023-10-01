#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include "q.h"
char buf[100],pid[5],gantt[1000];
int n;
strcpy(gantt,"|");
float tbt=0,tta=0,twt=0,trt=0;
int cur_time=0;
int rbt[n+1];	
struct process
{
	char pid[5];
	int bt,at,wt,rt,ta,ct,id,p,inQ;
};

struct process P[100],Q[100];

void swap(struct process *xp,struct process *yp) 
{ 
    struct process temp = *xp; 
    *xp=*yp; 
    *yp=temp; 
}
void sort(struct process *P,int n,int k)
{
	int min_i;
	if(k==2)						// to revert back to input order 
	{
		for(int i=0;i<n;i++)
		{
			min_i=i;
			for(int j=i+1;j<n;j++)
			{
				if(P[j].id<P[min_i].id)
					min_i=j;
			}
			if(min_i!=i)
				swap(&P[min_i],&P[i]);
		}	
		return;
	}
	for(int i=0;i<n;i++)					// sort wrt to at
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
	for(int i=0;i<n;i++)				// sort wrt to input order
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
int input(struct process *P,int n,int k)				// to get input
{
	int sorted=1;
	for(int i=0;i<n;i++)
	{
		printf("Enter pid: ");
		scanf("%s",P[i].pid);
		printf("Enter Arrival time: ");
		scanf("%d",&P[i].at);
		if(i!=0 && sorted)
			sorted=P[i].at>P[i-1].at?1:0;
		printf("Enter burst time: ");
		scanf("%d",&P[i].bt);
		if(k)
		{
			printf("Enter Priority: ");
			scanf("%d",&P[i].p);
		}
		P[i].id=i+1;
		P[i].ct=P[i].rt=-1;
		printf("\n");
	}
	return sorted;
}
void gantt_chart(char str[])				
{
	int y=0;
	for(int i=0;i<strlen(str);i++)			// top line
		printf("%c",str[i]=='|'?'+':'-');
	printf("\n%s\n",str);					// chart
	for(int i=0;i<strlen(str);i++)
		printf("%c",str[i]=='|'?'+':'-');		// bottom line
	printf("\n");
	int time=0,prev=0;
	for(int i=0;i<strlen(str);i++)			// to print time stamps
	{
		if(str[i]=='|')
		{
			printf("%*d",i-prev,time);
			prev=i;
			y=1;
		}
		else if(str[i]==' ')
		{
			if(y)
				time++;
		}
		else
			y=0;
	}
	printf("\n");
}

void display(struct process P[],int n,float ata,float awt,float art)		// display table
{
	printf("-------------------------------------------------------------------------------------");
	printf("\nPID\tArrival Time\tBurst Time   Turnaround Time\tWaiting Time\tResponse Time\n");
	printf("-------------------------------------------------------------------------------------\n");
	for(int i=0;i<n;i++)
		printf("%3s\t%-12d    %-10d   %-15d\t%-12d\t%d\n",P[i].pid,P[i].at,P[i].bt,P[i].ta,P[i].wt,P[i].rt);
	printf("-------------------------------------------------------------------------------------\n");
	printf("%31s      %-15.2f\t%-12.2f\t%0.2f\n","Average",ata,awt,art);
	printf("                       --------------------------------------------------------------\n");
	//printf("%s \t %0.2f \t %0.2f \t %0.2f \t %0.2f \t %0.2f\n",P[i].name,P[i].at,P[i].bt,P[i].ta,P[i].wt,P[i].rt);
}

void rr()
{
	int tq;
	

	struct queue Q;
	init(&Q,50); 
	//printf("\n---------------RR Scheduler-----------\n");
	
	printf("Enter time quantum: ");
	scanf("%d",&tq);
	int min,idx=n,k=0,x=0,comp=0,cur_time=0;
	rbt[n]=0;
	while(comp!=n)
	{
		for(int i=0;i<n;i++)		// loop to add all the processes that has not been in the queue already
		{
			if(P[i].at<=cur_time && !P[i].inQ && rbt[i]>0)	
			{
				enQ(&Q,i);
				P[i].inQ=1;
			}
		}
		if(rbt[idx]>0)			// add the dequeued process if its not completed
		{
			Q[x++]=P[idx];
			comp++;
		}

		if(!isEmpty(&Q))
		{
			idx=deQ(&Q);
			min=rbt[idx]<tq?rbt[idx]:tq;	
			if(P[idx].rt==-1)	// response time
				P[idx].rt=cur_time-P[idx].at;
			if(rbt[idx]>0)
			{
				rbt[idx]-=min;
				cur_time+=min;
				sprintf(buf,"%*s%s%*s%s",min," ",P[idx].pid,min," ","|");
				strcat(gantt,buf);
			}
			if(rbt[idx]==0)	
			{	
				comp++;
				P[idx].ct=cur_time;
				P[idx].ta=P[idx].ct-P[idx].at;
				P[idx].wt=P[idx].ta-P[idx].bt;
				tta+=P[idx].ta;
				twt+=P[idx].wt;
				trt+=P[idx].rt;
			}
			
		}
		else		// idle
		{
			for(int i=0;i<n;i++)
			{
				if(rbt[i]>0)
				{
					min=i;
					break;
				}
			}	
			sprintf(buf,"%*s%s%*s%s",P[min].at-cur_time," ","#",P[min].at-cur_time," ","|");
			strcat(gantt,buf);
			cur_time=P[min].at;
		}	
	}
					
	sort(P,n,2);	// revert to input order			
	printf("\n");
	gantt_chart(gantt);
	printf("\n");
	display(P,n,tta/n,twt/n,trt/n);
}
void SJF()
{
	
	/*char buf[100],pid[5],gantt[1000];
	strcpy(gantt,"|");
	float tbt=0,tta=0,twt=0,trt=0;
	printf("\n---------------SCJ-NP Scheduler-----------\n");
	printf("Enter no of processes: ");
	scanf("%d",&n);
	if(n<=0)
		return;
	struct process P[n];
	int sorted=input(P,n);
	if(!sorted)
		sort(P,n,0);			// sort wrt to at
	int min,min_i;
	int i=0,cur_time=0;*/
	while(i<n)				//order seq
	 {
	 	if(cur_time<P[i].at)
	  	{
	  		//idle
	  		sprintf(buf,"%*s%s%*s%s",P[i].at-cur_time," ","#",P[i].at-cur_time," ","|");
	    		strcat(gantt,buf);
	    		//
	    		
	 		cur_time=P[i].at;  
	 		continue;
	 	}
	 	min=P[i].bt;
	 	min_i=i;
		for(int j=i+1;j<n && i!=0;j++)		// finding the shortest task
		{
			if(cur_time>=P[j].at)
			{
				if(min>P[j].bt)
				{
					min=P[j].bt;
					min_i=j;
				}
			}
		}
		if(min_i!=i)					// pushing the completed task to front of the array
			swap(&P[min_i],&P[i]);
		cur_time+=P[i].bt;
		P[i].ct=cur_time;
		P[i].ta=P[i].ct-P[i].at;
		P[i].wt=P[i].rt=P[i].ta-P[i].bt;
		tta+=P[i].ta;
		twt+=P[i].wt;
		sprintf(buf,"%*s%s%*s%s",P[i].bt," ",P[i].pid,P[i].bt," ","|");
	    		strcat(gantt,buf);
		i++;
	 }
	 sort(P,n,2);			// revert to input order
	 trt=twt;			// cuz np
	 printf("\n");
	 gantt_chart(gantt);
	 printf("\n");
	 display(P,n,tta/n,twt/n,trt/n);
}
int main()
{
	printf("Enter no of processes: ");
	scanf("%d",&n);
	if(n<=0)
		return;
	int sorted=input(P,n,0);
	if(!sorted)	
		sort(P,n,0);

	for(int i=0;i<n;i++)				
	{	
		P[i].inQ=0;		//inQ->in the queue or not
		rbt[i]=P[i].bt;	//copy of burst time -> remianing time
	}
}
