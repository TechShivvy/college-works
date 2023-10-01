#include<stdio.h>
#include<stdlib.h>
#include "dlADT.h"
struct node * insertFront(struct node *header, char c)
{
  struct node *ptr=(struct node *)malloc(sizeof(struct node));
  ptr->c=c;
  if(header==NULL)
    ptr->next=NULL;
  else
  {
    ptr->next=header;
    header->prev=ptr;
  }
  ptr->prev=NULL;
  header=ptr;
  return header;
}
struct node * insertEnd(struct node *header, char c)
{
  struct node *ptr=(struct node *)malloc(sizeof(struct node));
  ptr->c=c;
  if(header==NULL)
  {
    ptr->next=NULL;
    ptr->prev=NULL;
    header=ptr;
  }
  else
  {
    struct node *temp=header;
    while(temp->next!=NULL)
    {temp=temp->next;}
    temp->next=ptr;
    ptr->prev=temp;
    ptr->next=NULL;
  }
  return header;
}
struct node * insertMiddle(struct node *header, char c, char d)
{
  struct node *ptr=(struct node *)malloc(sizeof(struct node));
  ptr->c=d;
  if(header==NULL)
  {
    ptr->next=NULL;
    ptr->prev=NULL;
    header=ptr;
  }
  else
  {
    struct node *temp=header;
    while(temp->next!=NULL&&temp->c!=c)
    {temp=temp->next;}
    if(temp->next!=NULL)
    {
      ptr->next=temp->next;
      ptr->prev=temp;
      temp->next->prev=ptr;    
      temp->next=ptr;  
    }
    else
    {
      temp->next=ptr;
      ptr->prev=temp;
      ptr->next=NULL;
    }
  }
  return header;
}
void displayItems(struct node *L)
{
  struct node *ptr=L;
  if(ptr==NULL)
    printf("\nList Empty\n");
  else 
  {
    printf("\nForward:\n");
    while(ptr->next!=NULL)
    {
      printf("%c ",ptr->c);
      ptr=ptr->next;
    }
    printf("%c ",ptr->c);
    //ptr=ptr->next;
    printf("\nRev:\n");
    while(ptr!=NULL)
    {
      printf("%c ",ptr->c);
      ptr=ptr->prev;
    }
  }
}
struct node * deleteItem(struct node *header, char c)
{
  struct node *ptr=header;
  if(ptr==NULL)
    printf("\nEmpty List\n");
  else
  {
    /*if(ptr->c==c)
    {
      header=ptr->next;
      header->prev=NULL;
      free(ptr);
      return header;
    }
    ptr=ptr->next;
    while(ptr->c!=c)
    {
      
    }*/
    while(ptr->c!=c&&ptr->next!=NULL)
    {
      ptr=ptr->next;
    }
    if(ptr->next==NULL&&ptr->c!=c)
    {
      printf("\nElement not found\n");
    }
    else{

    if(header==ptr)
      header=ptr->next;
    if(ptr->next!=NULL)
      ptr->next->prev=ptr->prev;
    if(ptr->prev!=NULL)
      ptr->prev->next=ptr->next;
    free(ptr);
    }
  }
  return header;
}
void seperation(struct node *header,struct node **C,struct node **V)
{
  struct node *ptr=header;
  /*if(ptr==NULL)
    printf("\nEmpty List\n");*/
  while(ptr!=NULL)
  {
    if(ptr->c=='a'||ptr->c=='e'||ptr->c=='i'||ptr->c=='o'||ptr->c=='u'||ptr->c=='A'||ptr->c=='E'||ptr->c=='I'||ptr->c=='O'||ptr->c=='U')
      *V=insertEnd(*V,ptr->c);
    else  
      *C=insertEnd(*C,ptr->c);
    ptr=ptr->next;
  }
}
int searchItem(struct node *header, char c)
{
  struct node *ptr=header;
  int count=0;
  if(ptr==NULL)
    printf("\nEmpty List,Cant search\n");
  else
  {
    while(ptr!=NULL)
    {
      if(ptr->c==c)
        count++;
      ptr=ptr->next;
    }
  }
  return count;
}
int palindrome(struct node *header)
{
	struct node *start=header;
	struct node *tail=header;
	if(header==NULL)
	{
		printf("\nEmpty List\n");
		return -1;	
	}
	while(tail->next!=NULL)
	{
		tail=tail->next;
	}
	while(start!=tail && tail->next!=start)
	{
		if(start->c!=tail->c)
			return 0;
		start=start->next;
		tail=tail->prev;
	}
	return 1;
}
int total(struct node *header)
{
  int count=1;
  struct node *ptr=header;
  while(ptr->next)
  {
    ptr=ptr->next;
    count++;
  }
  return count;
}
struct node* swapfl(struct node *header)
{
  struct node *start=header;
  struct node *tail=header;
  while(tail->next)
  {tail=tail->next;}
  tail->prev->next=start;
  start->prev=tail->prev;
  tail->next=start->next;
  start->next->prev=tail;
  tail->prev=NULL;
  start->next=NULL;
  return tail;
}
void swapk(struct node *header,int k,int count)
{
  struct node *p=header;
  struct node *q=header;
  int i=0;
  while(q->next)
  {
    q=q->next;
  }
  if(k>count)
  {
    printf("\nInvalid value for k!\n");
    return;
  }
  if(count%2?k==count/2+1:0)
    return;
  if(k>count/2)
    k=count-k+1;
  while(i<k-1)
  {
    p=p->next;
    q=q->prev;
    i++;
  }
  if(p->next==q)
  {
    p->next=q->next;
    q->next->prev=p;
    p->prev->next=q;
    q->prev=p->prev;
    q->next=p;
    p->prev=q;
    return;
  }
  struct node *p1=p->prev;
  struct node *p2=p->next;
  struct node *q1=q->prev;
  struct node *q2=q->next;
  p1->next=q;
  q->prev=p1;
  q->next=p2;
  p2->prev=q;
  q1->next=p;
  p->prev=q1;
  p->next=q2;
  q2->prev=p;
}