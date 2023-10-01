#include<stdio.h>
#include<stdlib.h>
struct stack 
{
	int data[10];
	int top,size;
};
void sInit(struct stack *s,int size);
int sIsFull(struct stack *s);
int sIsEmpty(struct stack *s);
void push(struct stack *s,int x);
int pop(struct stack *s);
int peek(struct stack *s);


