#include "stackADT.h"
void initstack(struct stack *s,int max)
{
  s->top=-1;
  s->max=max;
}
int isFull(struct stack *s)
{
  if(s->top==s->max-1)
    return 1;
  else 
    return 0;
}
int isEmpty(struct stack *s)
{
  if(s->top==-1)
    return 1;
  else 
    return 0;
}
void push(struct stack *s,int x)
{
  if(isFull(s))
  {printf("Stack is Full");}
  else 
  {
    s->top++;
    s->data[s->top]=x;
  }
}
void pop(struct stack *s)
{
  if(isEmpty(s))
  {printf("Stack is Empty");}
  else 
  {
    s->top--;
  }
  }
void display(struct stack s)
{
  if(isEmpty(&s))
  {printf("Stack is empty");}
  else
  {
    int i=s.top;
    while(i>=0)
      { 
        printf("%d ",s.data[i--]);
      }
  }
}