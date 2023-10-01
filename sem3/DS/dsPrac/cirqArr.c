#include<stdio.h>
#include<stdlib.h>
struct cirq
{
	int data[10];
	int f,r,size;
};
void init(struct cirq *Q,int s)
{
	Q->size=s;
	Q->f=Q->r=-1;	
}
int isFull(struct cirq *Q)
{
	return (Q->r+1)%Q->size==Q->f;
}
int isEmpty(struct cirq *Q)
{
	return Q->f==-1&&Q->r==-1;
}
void enq(struct cirq *Q,int key)
{
	if(isFull(Q))
		return;
	else if(isEmpty(Q))
		Q->f=Q->r=0;
	else
		Q->r=(Q->r+1)%Q->size;
	Q->data[Q->r]=key;
}
int deq(struct cirq *Q)
{
	int ele=Q->data[Q->f];
	if(isEmpty(Q))
		return -1;
	else if(Q->f==Q->r)
		Q->f=Q->r=-1;
	else
		Q->f=(Q->f+1)%Q->size;
	return ele;
}
int main()
{
	struct cirq q;
	init(&q,3);
	enq(&q,4);
	enq(&q,10);
	enq(&q,16);
	enq(&q,10);
	printf("%d ",deq(&q));
	enq(&q,69);
	printf("%d ",deq(&q));
	printf("%d ",deq(&q));
	printf("%d ",deq(&q));
	enq(&q,10);
	enq(&q,16);
	enq(&q,10);
	printf("%d ",deq(&q));
	printf("%d ",deq(&q));
	printf("%d ",deq(&q));
	return 0;
}
