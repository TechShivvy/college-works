#include "stackADT.h"
void sInit(struct stack *s,int size)
{
	s->top=-1;
	s->size=size;
} 
int sIsFull(struct stack *s)
{
	return s->top==s->size-1;
}
int sIsEmpty(struct stack *s)
{
	return s->top==-1;
}
void push(struct stack *s,int x)
{
	if(sIsFull(s))
		return;
	s->data[++s->top]=x;
}
int pop(struct stack *s)
{
	if(sIsEmpty(s))
		return -1;
	return s->data[s->top--];
}
int peek(struct stack *s)
{
	if(sIsEmpty(s))
		return -1;
	return s->data[s->top];
}

