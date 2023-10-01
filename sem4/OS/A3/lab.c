#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
struct process
{
	char pid[5];
	int bt,at,wt,rt,ta,ct,id;
};

void swap(struct process *xp,struct process *yp);			// to swap processes
void sort(struct process *P,int n,int k);				// to sort processes
int input(struct process *P,int n);					// input processes
void gantt_chart(char str[]);						// print gantt chart
void display(struct process P[],int n,float ata,float awt,float art);// display table;
void FCFS();
void SJF();

int main()
{
	int ch;
	char ch2;
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
			case 1: FCFS();
				break;
			case 2: SJF();
				break;
			case 3: printf("\nExiting...\n");
				break;
			default:printf("\nInavlid Input!\n");
		}
	}while(ch!=3);
	return 0;
}

void FCFS()
{
	int n;
	char buf[100],pid[5],gantt[1000];
	
	strcpy(gantt,"|");
	float tbt=0,tta=0,twt=0,trt=0;
	printf("\n---------------FCFS Scheduler-----------\n");
	printf("Enter no of processes: ");
	scanf("%d",&n);
	if(n<=0)
		return;
	struct process P[n];
	int sorted=input(P,n);
	if(!sorted)	
		sort(P,n,0);	// sort wrt to at
	int cur_time=0;
	for(int i=0;i<n;i++)
	{
	    	if (cur_time < P[i].at)
	    	{
	    		//idle
	    		sprintf(buf,"%*s%s%*s%s",P[i].at-cur_time," ","#",P[i].at-cur_time," ","|");
	    		strcat(gantt,buf);
			cur_time = P[i].at ;
			i--;
	    	}
	    	else 
	    	{
	    		cur_time+=P[i].bt;
	    		sprintf(buf,"%*s%s%*s%s",P[i].bt," ",P[i].pid,P[i].bt," ","|");
	    		strcat(gantt,buf);
	    		P[i].ct=cur_time;
			P[i].ta=P[i].ct-P[i].at;
			P[i].wt=P[i].rt=P[i].ta-P[i].bt;
			tta+=P[i].ta;
			twt+=P[i].wt;
	   	}
	}
	trt=twt;	// cuz np
	sort(P,n,2);	// revert to input order
	printf("\n");
	gantt_chart(gantt);
	printf("\n");
	display(P,n,tta/n,twt/n,trt/n);
}

void SJF()
{
	int n;
	char buf[100],pid[5],gantt[1000];
	strcpy(gantt,"|");
	float tbt=0,tta=0,twt=0,trt=0;
	printf("\n---------------SJF Scheduler-----------\n");
	printf("Enter no of processes: ");
	scanf("%d",&n);
	if(n<=0)
		return;
	struct process P[n];
	int sorted=input(P,n);
	if(!sorted)
		sort(P,n,0);	// sort wrt to at
	int min,min_i;
	int i=0,cur_time=0;
	while(i<n)		// order seq
	 {
	 	if(cur_time<P[i].at)
	  	{
	  		//idle
	  		sprintf(buf,"%*s%s%*s%s",P[i].at-cur_time," ","#",P[i].at-cur_time," ","|");
	    		strcat(gantt,buf);
	 		cur_time=P[i].at;  
	 		continue;
	 	}
	 	min=P[i].bt;
	 	min_i=i;
	 	
	 	// finding the shortest task
		for(int j=i+1;j<n && i!=0;j++)		
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
		// pushing the completed task to front of the array
		if(min_i!=i)					
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
	 sort(P,n,2);	// revert to input order
	 trt=twt;	// cuz np
	 printf("\n");
	 gantt_chart(gantt);
	 printf("\n");
	 display(P,n,tta/n,twt/n,trt/n);
}

void swap(struct process *xp,struct process *yp) 
{ 
    struct process temp = *xp; 
    *xp=*yp; 
    *yp=temp; 
}
void sort(struct process *P,int n,int k)
{
	int min_i;
	
	// to revert back to input order
	if(k==2)						 
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
	
	// sort wrt to at
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
	
	// sort wrt to input order
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
		printf("Enter Arrival time: ");
		scanf("%d",&P[i].at);
		if(i!=0 && sorted)
			sorted=P[i].at>P[i-1].at?1:0;
		printf("Enter burst time: ");
		scanf("%d",&P[i].bt);
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

void display(struct process P[],int n,float ata,float awt,float art)
{
	printf("-------------------------------------------------------------------------------------");
	printf("\nPID\tArrival Time\tBurst Time   Turnaround Time\tWaiting Time\tResponse Time\n");
	printf("-------------------------------------------------------------------------------------\n");
	for(int i=0;i<n;i++)
		printf("%3s\t%-12d    %-10d   %-15d\t%-12d\t%d\n",P[i].pid,P[i].at,P[i].bt,P[i].ta,P[i].wt,P[i].rt);
	printf("-------------------------------------------------------------------------------------\n");
	printf("%31s      %-15.2f\t%-12.2f\t%0.2f\n","Average",ata,awt,art);
	printf("                       --------------------------------------------------------------\n");
}
