#include<stdio.h>
#include "qADT.h"
void init(struct queue *Q,int val)
{
  Q->max=val;
  Q->f=-1;
  Q->r=-1;
}
int isFull(struct queue *Q)
{
  if((Q->r+1)%Q->max==Q->f)
    return 1;
  return 0;
}
int isEmpty(struct queue *Q)
{
  if(Q->f==-1 && Q->r==-1)
    return 1;
  return 0;
}
void enQ(struct queue *Q,int val)
{
  if(isFull(Q))
  {
    printf("\nOverflow!\n");
    return;
  }
  else if(isEmpty(Q))
  {
    Q->f=0;
    Q->r=0;
  }
  else
    Q->r=(Q->r+1)%Q->max;
  Q->data[Q->r]=val;
}
void enQ2(struct queue *Q,int J,int t)
{
  if(isFull(Q))
  {
    printf("\nOverflow!\n");
    return;
  }
  else if(isEmpty(Q))
  {
    Q->f=0;
    Q->r=0;
  }
  else
    Q->r=(Q->r+1)%Q->max;
  Q->J[Q->r]=J;
  Q->T[Q->r]=t;
}
int deQ(struct queue *Q)
{
  int item=Q->data[Q->f];
  if(isEmpty(Q))
  {
    printf("\nUnderflow!\n");
    return -1;
  }
  else if(Q->f==Q->r)
  {
    
    Q->f=-1;
    Q->r=-1;
  }
  else
    Q->f=(Q->f+1)%Q->max;
  return item;
}
void display(struct queue Q)
{
  if(isEmpty(&Q))
  {
    printf("\nUnderflow!\n");
    return;
  }
  int i;
  printf("Queue:");
  for(i=Q.f;i!=Q.r; i=(i+1)%Q.max)
  {
    printf("\n%d",Q.data[i]);
  }
printf("\n%d\n",Q.data[i]);
}
int rear(struct queue Q)
{
  return Q.r;
}
int avg(struct queue Q)
{
  int avg=0;
  for(int i=0;i<Q.r+1;i++)
	avg+=Q.data[i];
  avg/=(Q.r+1);
}
void display2(struct queue Q)
{
  if(isEmpty(&Q))
  {
    printf("\nUnderflow!\n");
    return;
  }
  int i;
  printf("Queue %d:",Q.J[Q.f]);
  for(i=Q.f;i!=Q.r; i=(i+1)%Q.max)
  {
    printf(" (J%d,%d);",Q.J[i],Q.T[i]);
  }
printf(" (J%d,%d)\n",Q.J[i],Q.T[i]);
}
