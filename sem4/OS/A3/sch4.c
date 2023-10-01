#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
struct process
{
	char pid[5];
	int bt;
	int at;
	int wt;
	int rt;
	int ta;
	int ct;
	int id;
};
char time[1000][5];
int maxt;
void swap(struct process *xp,struct process *yp) 
{ 
    struct process temp = *xp; 
    *xp=*yp; 
    *yp=temp; 
}
void sort(struct process *P,int n,int k)
{
	int min_i;
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
	if(!k)
	{
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
	else
	{
		for(int i=0;i<n-1;i++) 				//sort wrt bt
		{  
			min_i=i; 
			for(int j = i+1; j < n; j++) 
			{
				if(P[j].at==P[min_i].at) 
			    	{
			    		if(P[j].bt<P[min_i].bt)
			    			min_i=j;	
			    	}
			}
			if(min_i!=i)
				swap(&P[min_i],&P[i]); 
		 } 
		 for(int i=0;i<n;i++)
		 {
			min_i=i;
			for(int j=i+1;j<n;j++)
			{
				if(P[j].at==P[min_i].at && P[j].bt==P[min_i].bt && P[j].id<P[min_i].id)
					min_i=j;
			}
			if(min_i!=i)
				swap(&P[min_i],&P[i]);
		 } 
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
		P[i].ct=P[i].rt=-1;
		printf("\n");
	}
	return sorted;
}
void output(char str[])
{
	int y=0;
	for(int i=0;i<strlen(str);i++)
		printf("%c",str[i]=='|'?'+':'-');
	printf("\n%s\n",str);
	for(int i=0;i<strlen(str);i++)
		printf("%c",str[i]=='|'?'+':'-');
	printf("\n");
	int time=0,prev=0;
	for(int i=0;i<strlen(str);i++)
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
			//printf(" ");
		}
		else
		{
			y=0;
			//printf(" ");
		}
	}
	printf("\n");
}
void print_gantt_chart(struct process p[], int n) {
  puts(" ");
  puts("GANTT CHART          ");
  puts("***********          ");

  
  printf("+");
  int cur = 0, cnt = 1;
  for (int i = 1; i <= maxt; i ++ )
  {
  	if (!strcmp(time[i], time[i - 1]))
  		cnt ++;
	else 
	{
		printf("-");
		for (int j = 0; j < cnt; j ++) 
			printf("--");
		cnt = 1;
		printf("-+");
	}
  }
  puts("");
  printf("|");
  cur = 0, cnt = 1;
  for (int i = 1; i <= maxt; i ++ ) 
  {
  	if (!strcmp(time[i], time[i - 1])) 
  		cnt ++;
	else 
	{
		for (int j = 0; j < cnt; j ++)
			printf(" "); 
		printf("%s", time[i - 1]);
		for (int j = 1; j < cnt; j ++)
			printf(" ");
		cnt = 1;
		printf(" |");
	}
  }  
  
  puts("");
  cur = 0, cnt = 1;
  printf("+");
  for (int i = 1; i <= maxt; i ++ ) 
  {
  	if (!strcmp(time[i], time[i - 1]))
  		cnt ++;
	else 
	{
		printf("-");
		for (int j = 0; j < cnt; j ++)
			printf("--");
		cnt = 1;
		printf("-+");
	}
  }
  cur = 0, cnt = 1;
  printf("\n0");
  for (int i = 1; i <= maxt; i ++ ) 
  {
  	if (!strcmp(time[i], time[i - 1])) 
  		cnt ++;
	else 
	{
		printf(" ");
		for (int j = 0; j < cnt; j ++) 
			printf("  ");
		cur += cnt;
		cnt = 1;
		printf("%2d", cur);
	}
  }
  
  puts("");
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
	//printf("%s \t %0.2f \t %0.2f \t %0.2f \t %0.2f \t %0.2f\n",P[i].name,P[i].at,P[i].bt,P[i].ta,P[i].wt,P[i].rt);
}
void FCFS()
{
	int n;
	char pid[5],gantt[1000];
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
		sort(P,n,0);
	int cur_time=0;
	for(int i=0;i<n;i++)
	{
		P[i].wt = P[i].rt = cur_time - P[i].at;
		if (P[i].wt < 0) 
			P[i].wt = P[i].rt = 0;
	   	P[i].ta = P[i].wt + P[i].bt;
	    	if (cur_time < P[i].at)
	    	{
	    		
	    		for (int j = 0; j < (P[i].at-cur_time); j ++) 
	    		{
					strcat(gantt," ");
	    		}
	    		strcat(gantt,"#");
	    		for (int j = 0; j < (P[i].at-cur_time); j ++) 
	    		{
					strcat(gantt," ");
	    		}
	    		strcat(gantt,"|");
			cur_time = P[i].at + P[i].bt;
			for (int j = 0; j < cur_time-P[i].at; j ++) 
	    		{
					strcat(gantt," ");
	    		}
	    		//sprintf(pid,"%-2s",P[i].pid);
	    		strcat(gantt,P[i].pid);
	    		for (int j = 0; j < cur_time-P[i].at; j ++) 
	    		{
					strcat(gantt," ");
	    		}
			
	    		for (int j = P[i].at; j < cur_time; j ++) 
	    		{
	    			strcpy(time[j], P[i].pid);
	    		}
	    		strcat(gantt,"|");
	    	}
	    	else 
	    	{
	    		cur_time = cur_time + P[i].bt;
	    		for (int j = 0; j < P[i].bt; j ++) 
	    		{
					strcat(gantt," ");
	    		}
	    		//sprintf(pid,"%-2s",P[i].pid);
	    		strcat(gantt,P[i].pid);
	    		for (int j = 0; j < P[i].bt; j ++) 
	    		{
					strcat(gantt," ");
	    		}
	    		strcat(gantt,"|");
	    		for (int j = 1; j <= P[i].bt; j ++) 
	    		{
				strcpy(time[cur_time - j], P[i].pid);
			}
	   	}
	    	twt += P[i].wt;
	    	tta += P[i].ta;
	}
	trt=twt;
	sort(P,n,2);
	printf("\n");
	output(gantt);
	printf("\n");
	display(P,n,tta/n,twt/n,trt/n);
}
void SJF()
{
	int n;
	char pid[5],gantt[1000];
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
		sort(P,n,1);
	int min,min_i;
	 //first process will run now
	 int i=0,cur_time=0;
	while(i<n)				//order seq
	 {
	 	if(cur_time<P[i].at)
	  	{
	  		for (int j = 0; j < (P[i].at-cur_time); j ++) 
	    		{
					strcat(gantt," ");
	    		}
	    		strcat(gantt,"#");
	    		for (int j = 0; j < (P[i].at-cur_time); j ++) 
	    		{
					strcat(gantt," ");
	    		}
	    		strcat(gantt,"|");
	 		cur_time=P[i].at;  
	 		continue;
	 	}
	 	min=P[i].bt;
	 	min_i=i;
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
		if(min_i!=i)
			swap(&P[min_i],&P[i]);
		cur_time+=P[i].bt;
		P[i].ct=cur_time;
		P[i].ta=P[i].ct-P[i].at;
		P[i].wt=P[i].rt=P[i].ta-P[i].bt;
		tta+=P[i].ta;
		twt+=P[i].wt;
		for (int j = 0; j < P[i].bt; j ++) 
	    		{
					strcat(gantt," ");
	    		}
	    		//sprintf(pid,"%-2s",P[i].pid);
	    		strcat(gantt,P[i].pid);
	    		for (int j = 0; j < P[i].bt; j ++) 
	    		{
					strcat(gantt," ");
	    		}
	    		strcat(gantt,"|");
		for (int j = 1; j <= P[i].bt; j ++) 
	    	{
			strcpy(time[cur_time - j], P[i].pid);
		}
		i++;
	 }
	 sort(P,n,2);
	 trt=twt;
	 maxt=cur_time;
	 output(gantt);
	 printf("\n");
	 print_gantt_chart(P,n);
	 printf("\n");
	 display(P,n,tta/n,twt/n,trt/n);
}
void SRTF()
{
	int n,t=0;
	char pid[5],gantt[1000];
	strcpy(gantt,"|");
	float tbt=0,tta=0,twt=0,trt=0;
	printf("\n---------------SJF-P Scheduler-----------\n");
	printf("Enter no of processes: ");
	scanf("%d",&n);
	if(n<=0)
		return;
	struct process P[n+1];
	int sorted=input(P,n);
	if(!sorted)
		sort(P,n,0);
	
	int rbt[n+1];
	for(int i=0;i<n;i++)					//input
	{
		rbt[i]=P[i].bt;
	}
	int shortest_task,prev=0,s=0,comp=0,cur_time=0;
	rbt[n]=INT_MAX;
	for(cur_time=0;comp!=n;cur_time++)
	{
		int min=INT_MAX;
		shortest_task=n;
		for(int j=0;j<n;j++)
		{
			if( (rbt[j]<rbt[shortest_task]) && (P[j].at<=cur_time && rbt[j]>0))
				shortest_task=j;
						
		}
		//if(shortest_task!=n)
		{
			/*strcat(gantt,P[prev].pid);
		    	for (int j = 0; j < s; j ++) 
		    	{
					strcat(gantt," ");
		    	}
		    	strcat(gantt,"|");
		    	strcat(gantt," ");
		    	i=1;*/
			rbt[shortest_task]-=1;
			if(P[shortest_task].rt==-1)
				P[shortest_task].rt=cur_time-P[shortest_task].at;
			/*if(shortest_task!=prev)
			{
				for (int j = 0; j < P[prev].bt-rbt[prev]; j ++) 
		    		{
						strcat(gantt," ");
		    		}
		    		//sprintf(pid,"%-2s",P[i].pid);
		    		strcat(gantt,P[prev].pid);
		    		for (int j = 0; j < P[prev].bt-rbt[prev]; j ++) 
		    		{
						strcat(gantt," ");
		    		}
		    		strcat(gantt,"|");
			}*/
			if(shortest_task==prev)
			{
				strcat(gantt," ");
				s++;
			}
			else
			{
		    		//sprintf(pid,"%-2s",P[i].pid);
		    		strcat(gantt,prev==n?"#":P[prev].pid);
		    		for (int j = 0; j < s; j ++) 
		    		{
						strcat(gantt," ");
		    		}
		    		strcat(gantt,"|");
		    		strcat(gantt," ");
		    		s=1;
			}
			strcpy(time[t], P[shortest_task].pid);
		}
		/*else
		{
			strcat(gantt," ");
				i++;
		}*/
		if(rbt[shortest_task]==0)
		{
			comp++;
			P[shortest_task].ct=cur_time+1;	
			P[shortest_task].ta=P[shortest_task].ct-P[shortest_task].at;
			P[shortest_task].wt=P[shortest_task].ta-P[shortest_task].bt;
			trt+=P[shortest_task].rt;
			tta+=P[shortest_task].ta;
			twt+=P[shortest_task].wt;
		}t+=1;
		prev=shortest_task;
	}
	
		    		//sprintf(pid,"%-2s",P[i].pid);
		    		strcat(gantt,P[prev].pid);
		    		for (int j = 0; j < s; j ++) 
		    		{
						strcat(gantt," ");
		    		}
		    		strcat(gantt,"|");
	maxt=cur_time;
	output(gantt);
	printf("\n");
	print_gantt_chart(P,n);
	printf("\n");
        display(P,n,tta/n,twt/n,trt/n);
}
int main()
{
	int ch;
	char ch2;
	for (int i = 0; i < 1000; i ++) 
		strcpy(time[i], "  ");
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
			case 2: printf("\n---------------SJF Scheduler-----------\n");
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
						case 'A': SJF();
							  break;
						case 'b': 
						case 'B': SRTF();
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
