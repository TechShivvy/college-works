#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
int f[100];						//freq

struct node
{
	int data;
	int removed;
	int id;
	struct node* next;
};
struct node* newNode(int key,int id);			//new node alloc
struct node * insertEnd(struct node **p,int data,int id);	//insert at end
void display(struct node *p);				//disp of ele used to disp ref str
int search(struct node* p, int x);			//basic l search over ll,returns index of 1st occurance if found else 0
int search_imm_left(struct node* p, struct node *end,int x);	//returns the last occurance of an ele inbtw start & end
void rmv(struct node *p,int x);			//removes and reduces the freq of ele


struct node* newNode(int key,int id)
{
	struct node *temp=(struct node *)malloc(sizeof(struct node));
	temp->data=key;
	temp->next=NULL;
  	temp->removed=0;
  	temp->id=id;
	return temp;
}

struct node * insertEnd(struct node **p,int data,int id)
{
  	struct node *ptr=*p;
  	if(!ptr)
   	{
   		*p=newNode(data,id);
   		(*p)->next=NULL;
   	}
  	else
  	{
    		while(ptr->next)
     			ptr=ptr->next;
      		ptr->next=newNode(data,id);
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

int search(struct node* p, int x)	//search_imm_right
{
    	struct node* ptr = p;  
   	while (ptr)
    	{
		if (!ptr->removed && ptr->data == x)
     	       	return ptr->id;
     	   	ptr = ptr->next;
   	}
    	return 0;
}

int search_imm_left(struct node* p, struct node *end,int x)
{
    	struct node* ptr = p;  
    	int max=0;
   	while (ptr && !ptr->removed && end!=ptr)
    	{
    		if (ptr->data == x) 
         		max=ptr->id;
        	ptr = ptr->next;
   	}
    	return max;
}

void rmv(struct node *p,int x)
{
  	struct node *ptr=p;
  	while(ptr)
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
