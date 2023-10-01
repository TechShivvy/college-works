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
    printf("\n%c",Q.data[i]+65);
  }
printf("\n%c\n",Q.data[i]+65);
}
