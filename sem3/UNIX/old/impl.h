#include <stdio.h>
#include "adt.h"

void init(struct CQ *q, int s)
{
	printf("here at init %d", q->size);
	q->size=s;
	printf("1");
	q->f=0;
	printf("2");
	q->r=-1;
	printf("3");
	q->iter=0;
	printf("end");
}

int isFull(struct CQ *Q)
{
	if (Q->iter<Q->size)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int isEmpty(struct CQ *q)
{
	if (q->iter==0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void enqueue(struct CQ *q1, struct CQ *q2, char *jnum, int t)
{
	if (isFull(q1) && isFull(q2))
	{
		printf("Both Joblists are Full");
		return;
	}
	else if (isFull(q1) && !isFull(q2))
	{
		q2->iter++;
		q2->r = (++q2->r) % q2->size;
		q2->job[q2->r].jobnum = jnum;
		q2->job[q2->r].time=t;
	}
	else if (!isFull(q1) && isFull(q2))
	{
		q1->iter++;
		q1->r = (++q1->r) % q1->size;
		q1->job[q1->r].jobnum = jnum;
		q1->job[q1->r].time=t;
	}
	else
	{
		int i,sum=0;
        for (i = q1->f; i != (q1->r) ; i = (i + 1) % q1->size) 
		{
            //printf("%d ", q->data[i]);
            sum = sum + q1->job[i].time;
            i++;
        }
        sum = sum + q1->job[i].time;
        int avg1 = sum/i;
        
        i,sum=0;
        for (i = q2->f; i != (q2->r) ; i = (i + 1) % q2->size) 
		{
            //printf("%d ", q->data[i]);
            sum = sum + q2->job[i].time;
            i++;
        }
        sum = sum + q2->job[i].time;
        int avg2 = sum/i;
        
        if (avg1 > avg2)
        {
        	q2->iter++;
		    q2->r = (++q2->r) % q2->size;
		    q2->job[q2->r].jobnum = jnum;
		    q2->job[q2->r].time=t;
		}
		else if (avg1 < avg2)
		{
			q1->iter++;
		    q1->r = (++q1->r) % q1->size;
		    q1->job[q1->r].jobnum = jnum;
		    q1->job[q1->r].time=t;
		}
		else
		{
			q1->iter++;
	    	q1->r = (++q1->r) % q1->size;
	    	q1->job[q1->r].jobnum = jnum;
	    	q1->job[q1->r].time=t;
		}
        
        
	}
}

void dequeue(struct CQ *q)
{
	if (isEmpty(q))
	{
		printf("There are no elements in the Queue");
		return;
	}
	else
	{
		q->iter--;
		printf("The deleted element is %s", q->job[q->f].jobnum);
		q->f=(++q->f)%q->size;
	}
}

void display(struct CQ *q)
{
	if(isEmpty(q))
	{
		printf("The queue is empty");
		return;
	}
	else
	{
        printf("\n Items -> ");
        int i;
        for (i = q->f; i != (q->r) ; i = (i + 1) % q->size) 
		{
            printf("%s  %d\n", q->job[i].jobnum,q->job[i].time);
        }
        printf("%s  %d\n", q->job[i].jobnum,q->job[i].time);
	}
}
