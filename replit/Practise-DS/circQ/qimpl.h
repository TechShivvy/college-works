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
  {
    printf("\nOverflow\n");
    return 1;
  }
  return 0;
}
int isEmpty(struct queue *Q)
{
  if(Q->f==-1 && Q->r==-1)
  {
    printf("\nUnderflow\n");
    return 1;
  }
  return 0;
}
void inQ(struct queue *Q,int val)
{
  if(isEmpty(Q))
  {
    Q->f=0;
    Q->r=0;
    Q->data[Q->r]=val;
  }
  else if(isFull(Q))
    return;
  else
  {
   Q->r=(Q->r+1)%Q->max;
    Q->data[Q->r]=val;
  }
}
int deQ(struct queue *Q)
{
  int item=Q->data[Q->f];
  if(isEmpty(Q))
  {;}
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
    return;
  int i;
  for(i=Q.f;i!=Q.r; i=(i+1)%Q.max)
  {
    printf("\n%d\n",Q.data[i]);
  }
  printf("\n%d\n",Q.data[i]);
}