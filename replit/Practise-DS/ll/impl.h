#include<stdio.h>
#include "ADT.h"
#include<stdlib.h>
void * delete(struct node *l)
{
  
}
void * insertFront(struct node *l,int val)
{
  struct node *temp=(struct node*)malloc(sizeof(struct node *));
  temp->data=val;
  temp->next=header->next;
  header->next=temp;
}
void disp(struct node *l)
{

}
void * insertEnd(struct node *l,int val)
{
  struct node *temp=(struct node*)malloc(sizeof(struct node *)),*ptr=l;
  temp->data=val;
  while(ptr->next)
    ptr=ptr->next;
  temp->next=ptr->next;
  ptr->next=temp;
}