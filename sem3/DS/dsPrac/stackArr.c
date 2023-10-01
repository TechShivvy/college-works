#include<stdio.h>
#include<stdlib.h>
struct stack
{
	int data[10];
	int top,size;
};
void init(struct stack *s,int max)
{
	s->size=max;
	s->top=-1;
}
int isFull(struct stack *s)
{
	return s->top==s->size-1;
}
int isEmpty(struct stack *s)
{
	return s->top==-1;
}
void push(struct stack *s,int x)
{
	if(isFull(s))
		return;
	s->data[++s->top]=x;
}
int pop(struct stack *s)
{
	if(isEmpty(s))
		return -1;
	return s->data[s->top--];
}
int main()
{
	struct stack *s=(struct stack *)malloc(sizeof(struct stack));
	init(s,3);
	push(s,2);
	push(s,5);
	push(s,10);
	push(s,11);
	push(s,1);
	printf("%d ",pop(s));
	printf("%d ",pop(s));
	printf("%d ",pop(s));
	printf("%d ",pop(s));		
	return 0;
}
