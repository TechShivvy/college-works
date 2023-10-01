#include<stdio.h>
#include<stdlib.h>
struct Q
{
	int data[10];
	int f,r,max;	
};
void init(struct Q *q,int max)
{
	q->max=max;
	q->f=q->r=-1;
}
int isFull(struct Q *q)
{
	return q->r==q->max-1;
}
int isEmpty(struct Q *q)
{
	return q->f==-1;
}
void enq(struct Q *q,int key)
{	
	if(isFull(q))
		return;
	else if(isEmpty(q))
		q->f=q->r=0;
	else
		q->r++;
	q->data[q->r]=key;
}	
int deq(struct Q *q)
{
	int ele=q->data[q->f];
	if(isEmpty(q))
		return -1;
	else if(q->r==q->f)
		q->f=q->r=-1;
	else
		q->f++;
	return ele;
}
int main()
{
	struct Q q;
	init(&q,3);
	enq(&q,4);
	enq(&q,10);
	enq(&q,16);
	enq(&q,10);
	printf("%d ",deq(&q));
	printf("%d ",deq(&q));
	printf("%d ",deq(&q));
	printf("%d ",deq(&q));	
	return 0;
}
