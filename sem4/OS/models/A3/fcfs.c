#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>

typedef struct process
{
	char pid[3];
	int at,bt,tat,wt,rt,ct,id;
}proc;

void swap(proc *x,proc *y)
{
	proc temp=*x;
	*x=*y;
	*y=temp;
}

void sort(proc *P,int n,int mode)
{
	int i,min_i;
	if(mode==0)
	{
		for(i=0;i<n;i++)
		{
			min_i=i;
			for(int j=i;j<n;j++)
	  		{
	  			if(P[j].id<P[min_i].id)
	  				min_i=j;
			}	
			if(min_i!=i)
				swap(&P[min_i],&P[i]);
		}
	}
	
	if(mode==1)
	{
		for(i=0;i<n;i++)
		{
			min_i=i;
			for(int j=i;j<n;j++)
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
				if(P[j].at==P[min_i].at)
					min_i=j;
			}
			if(min_i!=i)
				swap(&P[min_i],&P[i]);
		}
	}
	
	if(mode==2)
	{
		for(i=0;i<n;i++)
		{
			min_i=i;
			for(int j=i;j<n;j++)
	  		{
	  			if(P[j].bt<P[min_i].bt)
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
				if(P[j].bt==P[min_i].bt && P[j].id<P[min_i].id)
					min_i=j;
			}
			if(min_i!=i)
				swap(&P[min_i],&P[i]);
		}
	}
	
}

int input(proc *P,int n)
{
	int sorted=1;
	for(int i=0;i<n;i++)
	{
		printf("Enter pid:");
		scanf("%s",P[i].pid);
		printf("Enter at and bt:");
		scanf("%d%d",&P[i].at,&P[i].bt);
		if(sorted && i)
			sorted=P[i].at>P[i-1].at?1:0;
		P[i].id=i+1;
		P[i].rt=P[i].ct=-1;
	}
	return sorted;
}
void display(struct process P[],int n,float ata,float awt,float art)
{
	printf("-----------------------------------------------------------------------------------");
	printf("\nPID\tArrival Time\tBurst Time   Turnaround Time\tWaiting Time\tResponse Time\n");
	printf("-----------------------------------------------------------------------------------\n");
	for(int i=0;i<n;i++)
		printf("%3s\t%-12d\t%-11d  %-15d\t%-12d\t%-13d\n",P[i].pid,P[i].at,P[i].bt,P[i].tat,P[i].wt,P[i].rt);
	printf("-----------------------------------------------------------------------------------\n");
	printf("%31s      %-15.2f\t%-12.2f\t%0.2f\n","Average",ata,awt,art);
	printf("                       --------------------------------------------------------------\n");
	/*printf("-------------------------------------------------------------------------------------");
	printf("\nPID\tArrival Time\tBurst Time   Turnaround Time\tWaiting Time\tResponse Time\n");
	printf("-------------------------------------------------------------------------------------\n");
	for(int i=0;i<n;i++)
		printf("%3s\t%-12d\t%-11d   %-16d\t%-12d\t%d\n",P[i].pid,P[i].at,P[i].bt,P[i].tat,P[i].wt,P[i].rt);
	printf("-------------------------------------------------------------------------------------\n");
	printf("%31s      %-15.2f\t%-12.2f\t%0.2f\n","Average",ata,awt,art);
	printf("                       --------------------------------------------------------------\n");*/
}


void gantt_chart(char str[])				
{
	int y=0;
	char buf[100],line[1000];
	strcpy(line,"");
	
	for(int i=0;i<strlen(str);i++)
	{
		sprintf(buf,"%c",str[i]=='|'?'+':'-');
		strcat(line,buf);
	}	
	
	printf("%s\n%s\n%s\n",line,str,line);
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
		}
		else
			y=0;	
	}
	printf("\n");
	/*int y=0;
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
	printf("\n");*/
}


void fcfs()
{
	int i=0,n,cur_time=0;
	float tat=0,twt=0,trt=0;
	char buf[100],gantt[1000];
	strcpy(gantt,"|");
	//printf("Enter no of processes:");
	//scanf("%d",&n);
	n=5;
	proc P[n];
	
	strcpy(P[0].pid,"p1");
	P[0].at=10;
	P[0].bt=5;

	strcpy(P[1].pid,"p2");
	P[1].at=8;
	P[1].bt=4;

	strcpy(P[2].pid,"p3");
	P[2].at=12;
	P[2].bt=4;

	strcpy(P[3].pid,"p4");
	P[3].at=3;
	P[3].bt=3;

	strcpy(P[4].pid,"p5");
	P[4].at=15;
	P[4].bt=5;

	
	
//	int sorted=input(P,n);

	int sorted=0;
	if(!sorted)
		sort(P,n,1);
	while(i!=n)
	{
		if(cur_time<P[i].at)
		{
			sprintf(buf,"%*s#%*s|",P[i].at-cur_time,"",P[i].at-cur_time,"");
			strcat(gantt,buf);
			cur_time=P[i].at;
			continue;
		}
		cur_time+=P[i].bt;
		sprintf(buf,"%*s%s%*s|",P[i].bt,"",P[i].pid,P[i].bt,"");
		strcat(gantt,buf);
	    	P[i].ct=cur_time;
		P[i].tat=P[i].ct-P[i].at;
		P[i].wt=P[i].rt=P[i].tat-P[i].bt;
		tat+=P[i].tat;
		twt+=P[i++].wt;
		
	}
	trt=twt;	// cuz np
	sort(P,n,0);	// revert to input order
	printf("\n");
	gantt_chart(gantt);
	printf("\n");
	display(P,n,tat/n,twt/n,trt/n);
}

int main()
{
	fcfs();
	return 0;
}
