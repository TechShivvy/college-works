#include "stackADT.h"
#include<stdio.h>
#include<stdlib.h>
struct stack * push(struct stack *s,int val)
{
  struct stack *ptr=(struct stack*)malloc(sizeof(struct stack *));
  ptr->data=val;
  ptr->next=s;
  s=ptr;
  return s;
}
struct stack * pop(struct stack *s)
{
  if(s==NULL)
    printf("\nUnderflow\n");
  else
  {
    struct stack *ptr=s;
    s=ptr->next;
    free(ptr);
  }
  return s;
}
void display(struct stack *s)
{
  struct stack *ptr=s;
  if(!ptr)
  {
    printf("\nEmpty\n");
  }
  while(ptr)
  {
    printf("\n%d\n",ptr->data);
    ptr=ptr->next;
  }
}