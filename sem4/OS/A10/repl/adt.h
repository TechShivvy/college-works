#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
int f[100];									//freq

struct node
{
	int data;
	int removed;
	struct node* next;
};

struct node* newNode(int key)							//new node alloc
{
	struct node *temp=(struct node *)malloc(sizeof(struct node));
	temp->data=key;
	temp->next=NULL;
  	temp->removed=0;
	return temp;
}

struct node * insertEnd(struct node **p,int data)				//insert at end
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

void display(struct node *p)							//disp of ele used to disp ref str
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

int search(struct node* p, int x)						//basic l search over ll,returns index of 1st occurance if found else 0
{
    	struct node* ptr = p;  
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

int search2(struct node* p, struct node *end,int x)			//returns the last occurance of an ele inbtw start & end
{
    	struct node* ptr = p;  
    	int max,count=1;
   	while (ptr && end!=ptr)
    	{
    		if (ptr->data == x) 
         		max=count;
        	ptr = ptr->next;
        	count++;
   	}
    	return max;
}

/*int search3(struct node* p, struct node *end,int x)			//returns x if x is available btw start and end
{
  	struct node* ptr = p;  
  	while (ptr && end!=ptr)
  	{
    		if (!ptr->removed && ptr->data==x)
      			break;
    		ptr = ptr->next;
  	}
  	free(ptr);
  	return x;
}*/

/*int rmv(struct node *p,int x,int m)						//removes and reduces the freq of ele
{
  	struct node *ptr=p;
  	while(ptr)
    	{
      		if(!ptr->removed && (ptr->data==x && !m||f[ptr->data]==x && m))
      		{ 
        		ptr->removed=1;
        		f[x]--;
        		x=ptr->data;
        		break;
      		}
      		ptr=ptr->next;
    	}
    	return x;
}*/
void rmv(struct node *p,int x)						//removes and reduces the freq of ele
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
