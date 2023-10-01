#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct process
{
	char pid[3];
	int at,bt,ct,tat,wt,rt,id;
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
			for(int j=i+1;j<n;j++)
			{
				if(P[j].id<P[min_i].id)
					min_i=j;
			}
			if(min_i!=i)
				swap(&P[i],&P[min_i]);
		}
	}
	else if(mode==1)
	{
		for(i=0;i<n-1;i++)
		{
			min_i=i;
			for(int j=i+1;j<n;j++)
			{
				if(P[j].at<P[min_i].at)
					min_i=j;
			}
			if(min_i!=i)
				swap(&P[i],&P[min_i]);
		}	
		for(i=0;i<n;i++)
		{
			min_i=i;
			for(int j=i+1;j<n;j++)
			{
				if(P[j].at==P[min_i].at && P[j].id<P[min_i].id)
					min_i=j;
			}
			if(min_i!=i)
				swap(&P[i],&P[min_i]);
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
		printf("at and bt:");
		scanf("%d%d",&P[i].at,&P[i].bt);
		if(sorted && i)
			sorted=P[i].at>P[i-1].at?1:0;
		P[i].id=i+1;
		P[i].ct=P[i].rt=-1;
	}
	return sorted;
}

void gantt_disp(char str[])
{
	int y;
	char buf[100], line[1000];
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
}

void disp_table(proc P[],int n,float ata,float awt,float art)
{
	printf("-----------------------------------------------------------------------------------\n");
	printf("PID\tArrival Time\tBurst Time   Turnaround time\tWaiting time\tResponse Time\n");
	printf("-----------------------------------------------------------------------------------\n");
	for(int i=0;i<n;i++)
		printf("%3s\t%-12d\t%-11d  %-15d\t%-12d\t%-13d\n",P[i].pid,P[i].at,P[i].bt,P[i].tat,P[i].wt,P[i].rt);
	printf("-----------------------------------------------------------------------------------\n");
	printf("%31s      %-15.2f\t%-12.2f\t%0.2f\n","Average",ata,awt,art);
	printf("                                 ----------------------------------------------------\n");	
		
}

void sjf()
{
	int min_i,n=5,i=0,cur_time=0;
	float tat=0,twt=0,trt=0;
	char buf[100],gantt[1000];
	strcpy(gantt,"|");
	//printf("n:");
	//scanf("%d",&n);
	
	proc P[n];
	//int sorted=input(P,n);
	
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


	int sorted=0;
	if(!sorted)
		sort(P,n,1);
	while(i<n)
	{
		if(cur_time<P[i].at)
		{
			sprintf(buf,"%*s#%*s|",P[i].at-cur_time,"",P[i].at-cur_time,"");
			strcat(gantt,buf);
			cur_time=P[i].at;
			continue;
		}
		
		min_i=i;
		for(int j=i+1;j<n && i;j++)
		{
			if(cur_time>=P[j].at && P[j].bt<P[min_i].bt)
				min_i=j;
		}
		if(min_i!=i)
			swap(&P[i],&P[min_i]);
		cur_time+=P[i].bt;
		sprintf(buf,"%*s%s%*s|",P[i].bt,"",P[i].pid,P[i].bt,"");
		strcat(gantt,buf);
		P[i].ct=cur_time;
		P[i].tat=P[i].ct-P[i].at;
		P[i].wt=P[i].rt=P[i].tat-P[i].bt;
		tat+=P[i].tat;
		twt+=P[i++].wt;	
	}
	sort(P,n,0);
	printf("\n");
	gantt_disp(gantt);
	printf("\n");
	disp_table(P,n,tat/n,twt/n,twt/n);
}


int main()
{
	sjf();
}
