#include<stdio.h>
struct stack
{
 int max,top,data[100];
};
void display(struct stack s);
void pop(struct stack *s);void push(struct stack *s,int x);int isEmpty(struct stack *s);int isFull(struct stack *s);