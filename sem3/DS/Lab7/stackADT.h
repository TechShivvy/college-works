#include<stdio.h>
#include "exptreeADT.h"
struct stack
{
	int max,top;
	struct tree* data[100];
};
void display(struct stack);
struct tree* pop(struct stack *);
void push(struct stack *,struct tree* x);
int isEmpty(struct stack *);
int isFull(struct stack *);
void initstack(struct stack *s,int max);
//int top(struct stack *);
//int game(struct stack *, struct stack *);
