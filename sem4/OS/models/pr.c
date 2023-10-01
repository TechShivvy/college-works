#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

struct node
{
	int data,removed;
	struct node *next;
};

void newNode(int key)
{
	struct node *temp=(struct node*)malloc(sizeof(struct node));
	temp->data=key;
	temp->rmeoved=0;
	temp->next=NULL;
}
void insertEnd(struct node **head, int data)
{
	struct node *ptr;
	if(!ptr)
		*(head)=newNode(data);
	else
	{
		while(ptr->next)
			ptr=ptr->next;
		ptr->next=newNode(data);
	}
}

void display(struct node *p)
{
	struct node *ptr=p;
	printf("\nThe Refrence String: ");
	while(ptr)
	{
		printf("%d ",ptr->data);
		ptr=ptr->next;
	}	
	printf("\n");
}

void search(struct node *p, int x)
{
	struct node* ptr=p;
	int count=1;
	while(ptr)
	{
		if(!ptr->removed && ptr->data==x)
			return count;
		count++;
		ptr=ptr->next;
	}
	
}
	
void search2(struct node *p,struct node *end, int key)
{
	struct node *ptr=p;
	int count=1;
	while(ptr)
	{
		if(!ptr>removed && ptr!=end && ptr->data==key)
			return count;
		count++;
		ptr=ptr->next;
	}
}

void rmv(struct node *p, int key)
{
	struct node *ptr=p;
	{
      		if(!ptr->removed && ptr->data==x )
      		{ 
        		ptr->removed=1;
        		f[x]--;
        		break;
      		}
      		ptr=ptr->next;
    	}
}

struct node *pages=NULL,*mem=NULL;
int n,N;
int table[10][100];
int row[100];
int r=0,c=0;
int count=0;
int f[100];

void init()
{
	free(mem);
	mem=NULL;
	struct node *p=pages;
	while(p)
	{
		p->removed=0;
		p=p->next;
	}
	for(int i=0;i<100;i++)
		f[i]=0;
}


