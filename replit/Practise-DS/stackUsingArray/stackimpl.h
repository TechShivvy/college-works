#include<stdlib.h>
#include<stdio.h>
#include "stackADT.h"
void init(struct stack *s,int max)
{
  s->top=-1;
  s->max=max;
}
int isFull(struct stack *s)
{
  if(s->top==s->max-1)
    return 1;
  return 0;
}
int isEmpty(struct stack *s)
{
  if(s->top==-1)
    return 1;
  return 0;
}
void push(struct stack *s,int val)
{
  if(isFull(s))
  {
    printf("\nOverflow\n");
    return;
  }
  s->top++;
  s->data[s->top]=val;
}
void pop(struct stack *s)
{
  if(isEmpty(s))
  {
    printf("\nUnderflow\n");
    return;
  }
  s->top--;
}
int top(struct stack s)
{
  if(isEmpty(&s))
  {
    printf("\nUnderflow\n");
    return -1;
  }
  return s.data[s.top];
}
void disp(struct stack s)
{
  if(isEmpty(&s))
  {
    printf("\nUnderflow\n");
    return;
  }
  while(s.top>=0)
  {
    printf("\n%d\n",s.data[s.top--]);
  }
}
