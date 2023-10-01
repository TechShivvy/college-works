#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

typedef struct process
{
	char pid[3];
	int at,bt,ct,wt,rt,tat,id;
}proc;

void gantt_disp(char str[])
{
	char buf[100],line[1000];
	strcpy(line,"");
	for(int i=0;i<strlen(str);i++)
	{
		sprintf(buf,"%c",str[i]=='|'?'+':'-');
		strcat(line,buf);
	}
	
	printf("\n%s\n%s\n%s\n\n",line,str,line);
	
	int y=0,time=0,prev=0;
	
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

void display(proc P[],int n,float ata,float awt, float art)
{
	printf("-------------------------------------------------------------------------------------\n");
	printf("PID\tArrival Time\tBurst Time   Turnaround Time\tWaiting Time\tResponse Time\n");
	printf("-------------------------------------------------------------------------------------\n");
	
	for(int i=0;i<n;i++)
		printf("%3s\t%-12d\t%-11d  %-15d\t%-11d\t%-13d\n",P[i].pid,P[i].at,P[i].bt,P[i].tat,P[i].wt,P[i].rt);
	printf("-------------------------------------------------------------------------------------\n");	
	
	printf("%31s      %-15.2f\t%-12.2f\t%0.2f\n","Average",ata,awt,art);
	printf("                                       ----------------------------------------------\n");
}

void swap(proc *x,proc *y)
{
	proc temp=*x;
	*x=*y;
	*y=temp;
}

void sort(proc *P,int n, int mode)
{
	int min_i;
	if(!mode)
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
				swap(&P[i],&P[min_i]);
		}
	}
	else
	{
		for(int i=0;i<n;i++)
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
		for(int i=0;i<n;i++)
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
	strcpy(P[0].pid,"p1");
	P[0].at=0;
	P[0].bt=3;

	strcpy(P[1].pid,"p2");
	P[1].at=1;
	P[1].bt=1;

	strcpy(P[2].pid,"p3");
	P[2].at=3;
	P[2].bt=2;

	strcpy(P[3].pid,"p4");
	P[3].at=9;
	P[3].bt=5;

	strcpy(P[4].pid,"p5");
	P[4].at=12;
	P[4].bt=5;
	for(int i=0;i<n;i++)
	{
		//printf("pid:");
		//scanf("%s",P[i].pid);
		//printf("at and bt:");
		//scanf("%d%d",&P[i].at,&P[i].bt);
		if(sorted && i)
			sorted=P[i].at>P[i-1].at?1:0;
		P[i].id=i+1;
		P[i].ct=P[i].rt=-1;
	}
	return sorted;
}

void srtf()
{
	int n=5,st,comp=0,prev=n,k=0,cur_time;
	float tat=0,trt=0,twt=0;
	char buf[100],gantt[1000];
	strcpy(gantt,"|");
	
	//printf("n:");
	//scanf("%d",&n);
	
	proc P[n+1];
	int sorted=input(P,n);
	if(!sorted)
		sort(P,n,1);
	
	int rbt[n+1];
	for(int i=0;i<n;i++)
		rbt[i]=P[i].bt;
		
	strcpy(P[n].pid,"#");
	rbt[n]=INT_MAX;
	
	for(cur_time=0;comp!=n;cur_time++)
	{
		st=n;
		for(int i=0;i<n;i++)
		{
			if(cur_time>=P[i].at && rbt[i] && rbt[i]<rbt[st])
				st=i;
		}
		
		rbt[st]--;
		
		if(P[st].rt==-1)
			P[st].rt=cur_time-P[st].at;
		
		if(prev==st||cur_time==0)
			k++;
		else
		{
			sprintf(buf,"%*s%s%*s|",k,"",P[prev].pid,k,"");
			strcat(gantt,buf);
			k=1;
		}
		
		if(!rbt[st])
		{
			comp++;
			P[st].ct=cur_time+1;
			P[st].tat=P[st].ct-P[st].at;
			P[st].wt=P[st].tat-P[st].bt;
			twt+=P[st].wt;
			tat+=P[st].tat;
			trt+=P[st].rt;
		}	
		prev=st;
	}
	
	sprintf(buf,"%*s%s%*s|",k,"",P[st].pid,k,"");
	strcat(gantt,buf);
	sort(P,n,0);
	printf("\n");
	gantt_disp(gantt);
	printf("\n");
	display(P,n,tat/n,twt/n,trt/n);
}


int main()
{
	srtf();
}
