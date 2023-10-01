#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include "q.h"
struct process
{
	char pid[5];
	int bt,at,wt,rt,ta,ct,id,p,inQ;
};
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
	int n,tq;
	char buf[100],pid[5],gantt[1000];
	strcpy(gantt,"|");
	float tbt=0,tta=0,twt=0,trt=0;
	struct queue Q;
	init(&Q,50); 
	printf("\n---------------RR Scheduler-----------\n");
	printf("Enter no of processes: ");
	scanf("%d",&n);
	if(n<=0)
		return;
	struct process P[n];
	int sorted=input(P,n,0);
	if(!sorted)	
		sort(P,n,0);
	int rbt[n+1];	
	for(int i=0;i<n;i++)				
	{	
		P[i].inQ=0;		//inQ->in the queue or not
		rbt[i]=P[i].bt;	//copy of burst time -> remianing time
	}
	printf("Enter time quantum: ");
	scanf("%d",&tq);
	int min,idx=n,k=0,comp=0,cur_time=0;
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
			enQ(&Q,idx);


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
void priorNon()
{
	int n;
	char buf[100],pid[5],gantt[1000];
	strcpy(gantt,"|");
	float tbt=0,tta=0,twt=0,trt=0;
	printf("\n---------------P-NP Scheduler-----------\n");
	printf("Enter no of processes: ");
	scanf("%d",&n);
	if(n<=0)
		return;
	struct process P[n+1];
	int sorted=input(P,n,1);
	if(!sorted)
		sort(P,n,0);			// sort wrt to at
	int min,min_i;
	int i=0,cur_time=0;
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
	 	min=P[i].p;
	 	min_i=i;
		for(int j=i+1;j<n && i!=0;j++)		// finding the highest priority process
		{
			if(cur_time>=P[j].at)
			{
				if(min>P[j].p)
				{
					min=P[j].p;
					min_i=j;
				}
				if(min==P[j].p && P[j].id<P[min_i].id)
					min_i=j;
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
void priorPre()
{
	int n;
	char buf[200],pid[5],gantt[1000];
	strcpy(gantt,"|");
	float tbt=0,tta=0,twt=0,trt=0;
	printf("\n---------------P-P Scheduler-----------\n");
	printf("Enter no of processes: ");
	scanf("%d",&n);
	if(n<=0)
		return;
	struct process P[n+1];
	int sorted=input(P,n,1);
	if(!sorted)
		sort(P,n,0);
	
	int rbt[n+1];					// copy of burst time -> remaining time
	for(int i=0;i<n;i++)				
	{
		rbt[i]=P[i].bt;
	}
	
	int shortest_task,prev=0,k=0,comp=0,cur_time=0;
	rbt[n]=INT_MAX;
	P[n].p=INT_MAX;
	strcpy(P[n].pid,"#");
	for(cur_time=0;comp!=n;cur_time++)
	{
		shortest_task=n;
		for(int j=0;j<n;j++)
		{
			if( (P[j].p<P[shortest_task].p) && (P[j].at<=cur_time && rbt[j]>0))
				shortest_task=j;
			if( (P[j].p==P[shortest_task].p && P[j].id<P[shortest_task].id) && (P[j].at<=cur_time && rbt[j]>0))
					shortest_task=j;
						
		}
		
		rbt[shortest_task]-=1;
		if(P[shortest_task].rt==-1)		// response time
			P[shortest_task].rt=cur_time-P[shortest_task].at;
		if(shortest_task==prev)
			k++;
		else if(cur_time==0)
			k++;
		else if(cur_time!=0)
		{
			sprintf(buf,"%*s%s%*s%s",k," ",P[prev].pid,k," ","|");
	    		strcat(gantt,buf);
		    	k=1;
		}
		if(rbt[shortest_task]==0)
		{
			comp++;
			P[shortest_task].ct=cur_time+1;	
			P[shortest_task].ta=P[shortest_task].ct-P[shortest_task].at;
			P[shortest_task].wt=P[shortest_task].ta-P[shortest_task].bt;
			trt+=P[shortest_task].rt;
			tta+=P[shortest_task].ta;
			twt+=P[shortest_task].wt;
		}
		prev=shortest_task;
	}
	sprintf(buf,"%*s%s%*s%s",k," ",P[prev].pid,k," ","|");
	strcat(gantt,buf);
	sort(P,n,2);
	printf("\n");
	gantt_chart(gantt);
	printf("\n");
        display(P,n,tta/n,twt/n,trt/n);
}
int main()
{
	int ch;
	char ch2;
	do
	{
		printf("\nMenu:\n");
		printf("1.Round Robin\n");
		printf("2.Priority\n");
		printf("3.EXIT\n");
		printf("Choice: ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: rr();
				break;
			case 2: printf("\n---------------Priority Scheduler-----------\n");
				do
				{
					printf("\na.Non-Preemptive\n");
					printf("b.Preemptive\n");
					printf("c.Go back\n");
					printf("d.Exit\n");
					printf("Choice: ");
					scanf(" %c",&ch2);
					switch(ch2)
					{
						case 'a': 
						case 'A':priorNon();
							  break;
						case 'b': 
						case 'B': priorPre();
							  break;
						case 'c': 
						case 'C': break;
						case 'd':
						case 'D': printf("\nExiting...\n");
							  return 0;
						default: printf("\nInavlid Input!\n");					
					}
				}while(!(ch2-97>=0 && ch2-99<=0||ch2-65>=0 && ch2-67<=0));
				break;
			case 3: printf("\nExiting...\n");
				break;
			default:printf("\nInavlid Input!\n");
		}
	}while(ch!=3);
	return 0;
}
