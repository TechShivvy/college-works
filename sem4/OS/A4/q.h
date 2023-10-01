#include<stdio.h>
struct queue
{
  int max;
  int f,r;
  int keys[100];
};
void init(struct queue *,int);
int isFull(struct queue *);
int isEmpty(struct queue *);
void enQ(struct queue *,int);
int deQ(struct queue *);
void disp(struct queue);

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
  Q->keys[Q->r]=val;
}
int deQ(struct queue *Q)
{
  int item=Q->keys[Q->f];
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
void disp(struct queue Q)
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
    printf("\n%d",Q.keys[i]);
  }
printf("\n%d\n",Q.keys[i]);
}
