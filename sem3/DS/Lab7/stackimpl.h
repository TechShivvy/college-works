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
void push(struct stack *s,struct tree* x)
{
  if(isFull(s))
  {printf("\nStack is Full!\n");}
  else 
  {
    s->top++;
    s->data[s->top]=x;
  }
}
/*void pop(struct stack *s)
{
  if(isEmpty(s))
  {printf("\nStack is Empty!\n");}
  else 
  {
    s->top--;
  }
  }*/
struct tree* pop(struct stack *s1)
{
   if(isEmpty(s1))
     return NULL;
   else
     return s1->data[s1->top--];  
}
/*void display(struct stack s)
{
  if(isEmpty(&s))
  {printf("\nStack is empty!\n");}
  else
  {
    printf("Stack:\n");
    int i=s.top;
    while(i>=0)
      { 
        printf("%d\n",s.data[i--]);
      }
  }
}*/
/*int top(struct stack *s)
{
	if(isEmpty(s))
	{
		//printf("Empty Stack!");
		return -1;
	}
	else
		return s->data[s->top];
}*/
