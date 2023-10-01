#include<stdio.h>
struct stack
{
 int max,top,data[100];
};
void display(struct stack);
void pop(struct stack *);
void push(struct stack *,int x);
int isEmpty(struct stack *);
int isFull(struct stack *);
void initstack(struct stack *s,int max);
int top(struct stack *);
//int game(struct stack *, struct stack *);
