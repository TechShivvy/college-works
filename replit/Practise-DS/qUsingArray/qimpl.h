#include<stdio.h>
#include "qADT.h"
void init(struct queue *Q,int max)
{
  Q->max=max;
  Q->front=-1;
  Q->rear=-1;
}
int isFull(struct queue *Q)
{
  if(Q->rear==Q->max-1)
    return 0;
  return 1;
}
int isEmpty(struct queue *Q)
{
  if(Q->rear<Q->front||Q->front==-1)
    return 1;
  return 0;
}
void inQ(struct queue *Q,int val)
{
  if(isFull(Q))
  {
    printf("\nOverflow\n");
    return;
  }
  if(isEmpty(Q))
  {
    Q->front=0;
    Q->rear=0;
  }
  else
    Q->rear++;
  Q->data[Q->rear]=val;
}
int deQ(struct queue *Q)
{
  int ele=q->data[q->front]
  if(isEmpty(Q))
  {
    printf("\nunderflow\n");
    return;
  }
  if(Q->front==Q->rear)
  {
    Q->front=-1;
    Q->rear=-1;
  }
  else
    Q->front++;
}
void display(struct queue Q)
{
  if(isEmpty(&Q))
  {
    printf("\nunderflow\n");
    return;
  }
  for(int i=Q.front;i<=Q.rear;i++)
  {
    printf("\n%d\n",Q.data[i]);
  }
}