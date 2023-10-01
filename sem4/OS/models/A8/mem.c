#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

struct node
{
	int id,start,end,size;
	char pid[3];
	struct node *next;
};

struct node* newNode(int start,int end,int id)
{	
	struct node *temp=(struct node*)malloc(sizeof(struct node));
	temp->start=start;
	temp->end=end;
	temp->size=end-start;
	temp->id=id;
	strcpy(temp->pid,"H");
	temp->next=NULL:
	return temp;
}

void insertEnd(struct node **p,struct node *temp)
{
	struct node* ptr=*p;
	if(!ptr)
	{
		*p=temp;
		return;
	}
	while(ptr->next)
		ptr=ptr->next;
	ptr->next=temp;
	return;
}

void insert(struct node **head,struct node *temp)
{
	if(!temp)
		return 0;
	struct node *p=*head;
	if(!p)
	{
		insertEnd(head,temp);
		return 1;
	}
	if(temp->start<p->start)
	{
		temp->next=*head;
		*head=temp;
		return 1;
	}
	while(ptr->next && temp->start>ptr->start)
		ptr=ptr->next;
	temp->next=ptr->next;
	ptr->next=temp;
	return 1;
}

struct node* clone(struct node* list)
{
    if(!list) 
    	return NULL;

    struct node* result = (struct node*)malloc(sizeof(struct node));
    result->start = list->start;
    result->end = list->end;
    result->size=list->size;
    result->id=list->id;
    strcpy(result->status,list->status);
    result->next = clone(list->next);
    return result;
}

struct node* merge(struct node* h1, struct node* h2)
{
    if (!h1)
        return h2;
    if (!h2)
        return h1;
    if (h1->start < h2->start)
    {
        h1->next = merge(h1->next, h2);
        return h1;
    }
    else
    {
        h2->next = merge(h1, h2->next);
        return h2;
    }
}
