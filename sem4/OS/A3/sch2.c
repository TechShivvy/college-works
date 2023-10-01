#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
struct proc
{
	char name[5];
	float bt;
	float at;
	float wt;
	float rt;
	float ta;
	float st;
	int ct;
	int end;
};
char time[1000][5];
int maxt;
void swap(struct proc *xp,struct proc *yp) 
{ 
    struct proc temp = *xp; 
    *xp=*yp; 
    *yp=temp; 
} 
void print_gantt_chart(struct proc p[], int n) {
  puts(" ");
  puts("GANTT CHART          ");
  puts("***********          ");

  
  printf("+");
  int cur = 0, cnt = 1;
  for (int i = 1; i <= maxt; i ++ ) {
  	if (!strcmp(time[i], time[i - 1])) {
  		cnt ++;
	}
	else {
		printf("-");
		for (int j = 0; j < cnt; j ++) {
			printf("--");
		}
		cnt = 1;
		printf("-+");
	}
  }
  puts("");
  printf("|");
  cur = 0, cnt = 1;
  for (int i = 1; i <= maxt; i ++ ) {
  	if (!strcmp(time[i], time[i - 1])) {
  		cnt ++;
	}
	else {
		for (int j = 0; j < cnt; j ++) {
			printf(" ");
		} 
		printf("%s", time[i - 1]);
		for (int j = 1; j < cnt; j ++) {
			printf(" ");
		}
		cnt = 1;
		printf(" |");
	}
  }  
  
  puts("");
  cur = 0, cnt = 1;
  printf("+");
  for (int i = 1; i <= maxt; i ++ ) {
  	if (!strcmp(time[i], time[i - 1])) {
  		cnt ++;
	}
	else {
		printf("-");
		for (int j = 0; j < cnt; j ++) {
			printf("--");
		}
		cnt = 1;
		printf("-+");
	}
  }
  cur = 0, cnt = 1;
  printf("\n0");
  for (int i = 1; i <= maxt; i ++ ) {
  	if (!strcmp(time[i], time[i - 1])) {
  		cnt ++;
	}
	else {
		printf(" ");
		for (int j = 0; j < cnt; j ++) {
			printf("  ");
		}
		cur += cnt;
		cnt = 1;
		printf("%2d", cur);
	}
  }
  
  puts("");
}


void display(struct proc P[],int n,float ata,float awt,float art)
{
	printf("-------------------------------------------------------------------------------------");
	printf("\nPID\tArrival Time\tBurst Time   Turnaround Time\tWaiting Time\tResponse Time\n");
	printf("-------------------------------------------------------------------------------------\n");
	for(int i=0;i<n;i++)
		printf("%3s\t%-12.2f    %-10.2f   %-15.2f\t%-12.2f\t%0.2f\n",P[i].name,P[i].at,P[i].bt,P[i].ta,P[i].wt,P[i].rt);
	printf("-------------------------------------------------------------------------------------\n");
	printf("%31s      %-15.2f\t%-12.2f\t%0.2f\n","Average",ata,awt,art);
	printf("                       --------------------------------------------------------------\n");
	//printf("%s \t %0.2f \t %0.2f \t %0.2f \t %0.2f \t %0.2f\n",P[i].name,P[i].at,P[i].bt,P[i].ta,P[i].wt,P[i].rt);
}
void FCFS()
{
	int n,sorted=1;
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
		if(i!=0 && sorted)
			sorted=P[i].at>P[i-1].at?1:0;
		printf("Burst Time: ");
		scanf("%f",&P[i].bt);
	}
	if(!sorted)
	{
		int min_i;
	    	for(int i=0;i<n-1;i++) 
	    	{  
			min_i=i; 
			for(int j = i+1; j < n; j++) 
			{
				if(P[j].at<P[min_i].at) 
			    		min_i=j;
			}
			if(min_i!=i)
				swap(&P[min_i],&P[i]); 
	    	} 
	}
	/*for(int i=0;i<n;i++)
	{
		if(i==0)
			P[i].wt=0;
		else
			P[i].wt=tbt-P[i].at;  //P[i].wt=P[i-1].bt-P[i-1].wt 
		P[i].ta=P[i].wt+P[i].bt;
		tta+=P[i].ta;
		tbt+=P[i].bt;
		P[i].rt=P[i].wt;
		trt+=P[i].rt;
		twt+=P[i].wt;
	}*/
	int cur_time=0;
	for(int i=0;i<n;i++)
	{
		P[i].wt = P[i].rt = cur_time - P[i].at;
		if (P[i].wt < 0) 
			P[i].wt = P[i].rt = 0;
	   	P[i].ta = P[i].wt + P[i].bt;
	    	if (cur_time < P[i].at)
	    	{
			cur_time = P[i].at + P[i].bt;
	    		for (int j = P[i].at; j < cur_time; j ++) 
	    		{
	    			strcpy(time[j], P[i].name);
	    		}
	    	}
	    	else 
	    	{
	    		cur_time = cur_time + P[i].bt;
	    		for (int j = 1; j <= P[i].bt; j ++) 
	    		{
				strcpy(time[cur_time - j], P[i].name);
			}
	   	}
	    	twt += P[i].wt;
	    	tta += P[i].ta;
	}
	trt=twt;
	maxt=cur_time;
	printf("\n");
	print_gantt_chart(P,n);
	printf("\n");
	display(P,n,tta/n,twt/n,trt/n);
}
void SJF()
{
	int n,sorted=1;
	float tbt=0,tta=0,twt=0,trt=0;
	printf("\n---------------SCJ Scheduler-----------\n");
	printf("Enter no of processes: ");
	scanf("%d",&n);
	struct proc P[n];
	int at[n],rbt[n];
	for(int i=0;i<n;i++)					//input
	{
		printf("\nEnter process ID: ");
		scanf("%s",P[i].name);
		printf("Arrival Time: ");
		scanf("%f",&P[i].at);
		if(i!=0 && sorted)				//increasing order broken
			sorted=P[i].at>P[i-1].at?1:0;
		printf("Burst Time: ");
		scanf("%f",&P[i].bt);
		P[i].end=0;
		P[i].rt=-1;
		rbt[i]=P[i].bt;
		at[i]=P[i].at;
	}
	if(!sorted)						//sort wrt at
	{
		int min_i;
	    	for(int i=0;i<n-1;i++) 
	    	{  
			min_i=i; 
			for(int j = i+1; j < n; j++) 
			{
				if(P[j].at<P[min_i].at) 
			    		min_i=j;
			}
			if(min_i!=i)
				swap(&P[min_i],&P[i]); 
	    	} 
	}
	int min,min_i;
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
	 //first process will run now
	 int i=0,cur_time=0;
	while(i<n)				//order seq
	 {
	 	if(cur_time<P[i].at)
	  	{
	 		cur_time=P[i].at;  
			/*for (int j = P[i].at; j < cur_time; j ++) 
	    		{
	    			strcpy(time[j], P[i].name);
	    		}*/
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
		P[min_i].end=1;
		if(min_i!=i)
			swap(&P[min_i],&P[i]);
		cur_time+=P[i].bt;
		P[i].ct=cur_time;
		P[i].ta=P[i].ct-P[i].at;
		P[i].wt=P[i].rt=P[i].ta-P[i].bt;
		tta+=P[i].ta;
		twt+=P[i].wt;
		for (int j = 1; j <= P[i].bt; j ++) 
	    		{
				strcpy(time[cur_time - j], P[i].name);
			}
		/*if(i==0)
			P[i].wt=0;
		else
			P[i].wt=tbt-P[i].at;  //P[i].wt=P[i-1].bt-P[i-1].wt 
		P[i].ta=P[i].wt+P[i].bt;
		//scur_time=bt;
		tta+=P[i].ta;
		tbt+=P[i].bt;
		P[i].rt=P[i].wt;
		trt+=P[i].rt;
		twt+=P[i].wt;*/
		i++;
	 }
	 trt=twt;
	 maxt=cur_time;
	printf("\n");
	print_gantt_chart(P,n);
	printf("\n");
	 display(P,n,tta/n,twt/n,trt/n);
}
void SRTF()
{
	int n,sorted=1,t=0;
	float tbt=0,tta=0,twt=0,trt=0;
	printf("\n---------------SCJ Scheduler-----------\n");
	printf("Enter no of processes: ");
	scanf("%d",&n);
	struct proc P[n];
	int at[n],rbt[n+1];
	for(int i=0;i<n;i++)					//input
	{
		printf("\nEnter process ID: ");
		scanf("%s",P[i].name);
		printf("Arrival Time: ");
		scanf("%f",&P[i].at);
		if(i!=0 && sorted)				//increasing order broken
			sorted=P[i].at>P[i-1].at?1:0;
		printf("Burst Time: ");
		scanf("%f",&P[i].bt);
		P[i].end=0;
		P[i].rt=-1;
		rbt[i]=P[i].bt;
		at[i]=P[i].at;
	}
	if(!sorted)						//sort wrt at
	{
		int min_i;
	    	for(int i=0;i<n-1;i++) 
	    	{  
			min_i=i; 
			for(int j = i+1; j < n; j++) 
			{
				if(P[j].at<P[min_i].at) 
			    		min_i=j;
			}
			if(min_i!=i)
				swap(&P[min_i],&P[i]); 
	    	} 
	}
	/*int min,min_i;
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
	 }*/

	
/*for(int i=0;i<n;i++)					//order seq
	 {
	 	min=P[i].bt;
	 	min_i=i;
		for(int j=i+1;j<n && i!=0;j++)
		{
			if(P[i-1].bt>P[j].at && P[j].end==0)
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
	 }*/
	 int shortest_task,comp=0,cur_time=0,start[n];
	/* while(comp<n)
	 {
	 	i=i%n;
	 	if(cur_time<P[i].at && !P[i].end)
	  	{
	 		cur_time=P[i].at;
	 		continue;
	 	}
	 	if(!P[i].end)
	 	{
	 		for(int j=(i+1)%n;j!=i;j=(j+1)%n)
	 		{
	 			if(!P[j].end)
	 			{
	 				cur_time=P[j].at;
	 				rbt[i]-=P[j].at;
	 				break;
	 			}
	 		}
	 	}
	 }*/
		rbt[n]=INT_MAX;
	 for(cur_time=0;comp!=n;cur_time++)
						{
							shortest_task=n;
							for(int j=0;j<n;j++){
								if( (rbt[j]<rbt[shortest_task]) && (P[j].at<=cur_time && rbt[j]>0)){
									shortest_task=j;
								}
							}
							if(shortest_task!=n)
							{rbt[shortest_task]-=1;
							strcpy(time[t], P[shortest_task].name);}
							if(rbt[shortest_task]==0){
								comp++;
							P[shortest_task].ct=cur_time+1;	
		P[shortest_task].ta=P[shortest_task].ct-P[shortest_task].at;
		P[shortest_task].wt=P[shortest_task].ta-P[shortest_task].bt;
		tta+=P[shortest_task].ta;
		twt+=P[shortest_task].wt;
							
								/*task[shortest_task].waiting_time=current_time+1-task[shortest_task].burst_time-task[shortest_task].arrival_time;
								task[shortest_task].turnaround_time=current_time+1-task[shortest_task].arrival_time;*/
							}t+=1;
						}
						trt=twt;
	 maxt=cur_time;
	printf("\n");
	print_gantt_chart(P,n);
	printf("\n");
	 /*printf("helloo");
	 while(comp!=n)
	 {
	 	for(int i=0;i<n;i++)
	 	{
	 		min=P[i].bt;
	 	min_i=i;
	 		for(int j=1;j<n&&j!=i;j++)
	 		{
	 			if(cur_time>=P[i].at && P[i].end==0)
	 			{
	 				if(min>P[j].bt)
				{
					min=P[j].bt;
					min_i=j;
				}
	 				if(P[i].rt==-1)
	 					start[i]=cur_time;
	 			}
	 			else
	 			{
	 				cur_time++;
	 				continue;
	 			}
	 		}
	 	}
	 		rbt[i]=rbt[i]-1;
	 		cur_time++;
	 		if(rbt[i]==0&&P[i].end==0)
	 		{
	 			P[i].ta=cur_time-P[i].at;
	 			tta+=P[i].ta;
	 			P[i].wt=P[i].ta-P[i].bt;
	 			twt+=P[i].wt;
	 			P[i].rt=start[i]-P[i].at;
	 			trt+=P[i].rt;
	 			P[i].end=1;
	 			comp++;
	 		}
	 		
	 	}
	 }*/
	/* int idle=0,prev=0,k=1;
	 printf("%s->",P[0].name); ;
	 while(comp!=n)
	 {
	 int idx = -1;
        int mn = 10000000;
        
        for(int i = 0; i < n; i++) {
            if(P[i].at <= cur_time && P[i].end == 0) {
                if(rbt[i] < mn) {
                    mn = rbt[i];
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            if(rbt[idx] == P[idx].bt) {
                start[idx] = cur_time;
                idle += start[idx] - prev;
            }
            rbt[idx] -= 1;
            cur_time++;
            prev = cur_time;
            if(rbt[idx] == 0&&P[idx].end==0) {
            	
                //p[idx].completion_time = cur_time;
                P[idx].ta = cur_time - P[idx].at;
                P[idx].wt = P[idx].ta - P[idx].bt;
                P[idx].rt= start[idx] - P[idx].at;

                tta += P[idx].ta;
                twt += P[idx].wt;
                trt += P[idx].rt;
		printf("%s->",P[idx].name);
                P[idx].end = 1;
                comp++;
                k=1;
            }
        }
        else {
        if(k)
        {printf("#->");}
        printf("cur:%d",cur_time);
             cur_time++;
             	k=0;
        }
        }
        printf("\n");
        for(int i=0;i<n;i++)
        	printf("%d->",start[i]);*/
        display(P,n,tta/n,twt/n,trt/n);
}
int main()
{
	//struct proc P[5];
	//display(P,5,13.0,14.0,15.0);
	//return 0;
	int ch,ch2;
	for (int i = 0; i < 1000; i ++) strcpy(time[i], "  ");
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
			case 4:SRTF();
				break;
			case 3: printf("\nExiting...\n");
				break;
			default:printf("\nInavlid Input!\n");	
		}
	}while(ch!=3);
	return 0;
}
