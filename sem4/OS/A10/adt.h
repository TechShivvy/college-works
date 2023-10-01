#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	int removed;
	struct node* next;
};

struct node* newNode(int key)
{
	struct node *temp=(struct node *)malloc(sizeof(struct node));
	temp->data=key;
	temp->next=NULL;
	return temp;
}
struct node * insertEnd(struct node **p,int data)
{
  	struct node *ptr=*p;
  	if(!ptr)
   	{
   		*p=newNode(data);
   		(*p)->next=NULL;
   	}
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
	free(ptr);
}
int search(struct node* p, int x)
{
    	struct node* ptr = p;  // Initialize current
    	int count=1;
   	while (ptr)
    	{
     	   if (ptr->data == x)
     	       return count;
     	   ptr = ptr->next;
     	   count++;
   	}
    	return 0;
}

int search2(struct node* p, struct node *pivot,int x)
{
    	struct node* ptr = p;  // Initialize current
    	int count=1;
   	while (ptr && ptr->next!=pivot)
    	{
     	   if (ptr->data == x)
     	       return count;
     	   ptr = ptr->next;
     	   count++;
   	}
    	return 0;
}
/*struct node* reverse(struct node* node)
{
	if (!node||!node->next)
            return node;
        struct node* node1 = reverse(node->next);
        node1->next = node;
        node->next = NULL;
        return node;
}*/
