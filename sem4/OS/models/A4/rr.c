#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>

struct queue
{
	int data[100];
	int max,f,r;
};

void init(struct queue *Q,int max)
{
	Q->max=max;
	Q->f=Q->r=-1;
}

int isFull(struct queue *Q)
{
	return ((Q->r+1)%Q->max==Q->f);
}

int isEmpty(struct queue *Q)
{
	return (Q->f==-1 && Q->r==-1);
}

void enQ(struct queue *Q,int x)
{
	if(isFull(Q))
		return;
	else if(isEmpty(Q))
		Q->f=Q->r=0;
	else
		Q->r=(Q->r+1)%Q->max;
	Q->data[Q->r]=x;
}

int deQ(struct queue *Q)
{
	int x=Q->data[Q->f];
	if(isEmpty(Q))
		return -1;
	else if(Q->f==Q->r)
		Q->f=Q->r=-1;
	else
		Q->f=(Q->f+1)%Q->max;
	return x;
}

typedef struct process
{
	char pid[3];
	int at,bt,ct,tat,wt,rt,id,inQ;
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
	if(!mode)
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
	else
	{
		for(i=0;i<n;i++)
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

void gantt_disp(char str[])
{
	char buf[100],line[1000];
	strcpy(line,"");
	for(int i=0;i<strlen(str);i++)
	{
		sprintf(buf,"%c",str[i]=='|'?'+':'-');
		strcat(line,buf);
	}
	
	printf("\n%s\n%s\n%s\n",line,str,line);
	
	int y=0,prev=0,time=0;
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
}

void display(proc P[],int n,float ata,float awt,float art)
{
	printf("---------------------------------------------------------------------------------------------\n");
	printf("PID\tArrival Time\tBurst TIme   Turnaround Time\tWaiting Time\tResponse Time\n");
	printf("---------------------------------------------------------------------------------------------\n");
	
	for(int i=0;i<n;i++)
		printf("%3s\t%-12d\t%-12d  %-15d\t%-12d\t%-13d\n",P[i].pid,P[i].at,P[i].bt,P[i].tat,P[i].wt,P[i].rt);
	printf("---------------------------------------------------------------------------------------------\n");
	printf("%31s      %-15.2f\t%-12.2f\t%0.2f\n","Average",ata,awt,art);
	printf("                                        -----------------------------------------------------\n");
} 


void rr()
{
	int n=5,tq=2,comp=0,cur_time=0;
	float tat=0,trt=0,twt=0;
	char buf[100],gantt[1000];
	strcpy(gantt,"|");
	
	//printf("n:");
	//scanf("%d",&n);
	
	proc P[n];
	
	int sorted=input(P,n);
	if(!sorted)
		sort(P,n,1);
	
	//printf("tq:");
	//scanf("%d",&tq);
	
	int rbt[n+1];
	for(int i=0;i<n;i++)
	{
		rbt[i]=P[i].bt;
		P[i].inQ=0;	
	}
	rbt[n]=0;
	
	int prev=n,min;
	
	struct queue Q;
	init(&Q,50);
	
	display(P,n,tat/n,twt/n,trt/n);
        int k=0;
	while(comp!=n && ++k)
	{	
		for(int i=0;i<n;i++)
		{
			if(!P[i].inQ && cur_time>=P[i].at && rbt[i]>0)
			{
				printf("\n%d\n",k);
				enQ(&Q,i);
				P[i].inQ=1;
			}
		}	
		
		if(rbt[prev]>0)
			enQ(&Q,prev);
		
		if(!isEmpty(&Q))
		{
			prev=deQ(&Q);
			min=rbt[prev]>tq?tq:rbt[prev];
			
			if(P[prev].rt==-1)
				P[prev].rt=cur_time-P[prev].at;
			
			if(rbt[prev]>0)
			{
				rbt[prev]-=min;
				cur_time+=min;
				sprintf(buf,"%*s%s%*s|",min,"",P[prev].pid,min,"");
				strcat(gantt,buf);
			}
			if(rbt[prev]==0)
			{
				comp++;
				P[prev].ct=cur_time;
				P[prev].tat=P[prev].ct-P[prev].at;
				P[prev].wt=P[prev].tat-P[prev].bt;
				twt+=P[prev].wt;
				tat+=P[prev].tat;
				trt+=P[prev].rt;
			}
		}
		else
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
	sort(P,n,0);
	printf("\n");
	gantt_disp(gantt);
	printf("\n");
	display(P,n,tat/n,twt/n,trt/n);
}
	
int main()
{
	rr();
}


