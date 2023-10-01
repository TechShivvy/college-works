#include<stdio.h>
#include<stdlib.h>
struct sll
{
	struct sll *next;
	int data;
};
void insertFront(struct sll **header,int key)
{
	struct sll *ptr=(struct sll *)malloc(sizeof(struct sll));
	ptr->data=key;
	ptr->next=*header;
	*header=ptr;
	//return header;
}
struct sll* insertEnd(struct sll *header,int key)
{
	struct sll *ptr=(struct sll *)malloc(sizeof(struct sll));
	struct sll *temp=header;
	ptr->data=key;
	if(!header)
	{	
		header=ptr;
		return header;
	}
	while(temp->next)
	{
		temp=temp->next;
	}
	temp->next=ptr;
	return header;
		
}
void display(struct sll *l)
{
	struct sll *ptr=l;
	while(ptr)
	{
		printf("%d->",ptr->data);
		ptr=ptr->next;
	}
	printf("\b\b  \b\b\n");
}
void splitAlt(struct sll *head,struct sll **odd,struct sll **even)
{
	if(head==NULL) return;
        *odd = head; *even = head->next;
        if(*even == NULL) return;
        head = head->next->next;
        struct sll* end1 = *odd;
        struct sll* end2 = *even;
        for(int t=1; head != NULL; head=head->next, t*=-1)
        {
            if(t==1)
            {
                end1->next = head;
                end1 = end1->next;
            }
            else
            {
                end2->next = head;
                end2 = end2->next;
            }
        }
        end1->next = end2->next = NULL;
}
void find(struct sll *head,struct sll **x,int key)
{
	*x=head;
	while((*x)->next->data!=key)
	{
		*x=(*x)->next;
	}
}
void prev(struct sll *head,struct sll **prev,int key)
{
	find(head,prev,key);
}
void swap(struct sll **head,int x,int y)
{
	if(x==y)
		return;
	struct sll *prevX=NULL,*prevY=NULL,*curY=*head,*curX=*head;
	prev(*head,&prevX,x);
	prev(*head,&prevY,y);
	curX=prevX->next;
	curY=prevY->next;
	if(!curX||!curY)
		return;
	if(prevX)
		prevX->next=curY;
	else
		*head=curY;
	if(prevY)
		prevY->next=curX;
	else
		*head=curX;
	struct sll *temp=curY->next;
	curY->next=curX->next;
	curX->next=temp;	
}
struct sll* reverse(struct sll *head)
{
	struct sll *prev=NULL,*next=NULL,*ptr=head;
	while(ptr)
	{
		next=ptr->next;
		ptr->next=prev;
		prev=ptr;
		ptr=next;
	}
	head=prev;
	return head;
}
int main()
{
	struct sll *head=NULL;
	head=insertEnd(head,1);
	insertFront(&head,2);
	insertFront(&head,3);
	insertEnd(head,4);
	insertEnd(head,5);
	insertEnd(head,6);
	insertFront(&head,8);
	insertFront(&head,9);
	display(head);
	head=reverse(head);
	//printf("\n%d",head->data);
	display(head);
	struct sll *odd=NULL;//=(struct sll *)malloc(sizeof(struct sll));
	struct sll *even=NULL;//=(struct sll *)malloc(sizeof(struct sll));
	//splitAlt(head,&odd,&even);
	//display(even);
	//display(odd);
	/*struct sll *temp=NULL;
	prev(head,&temp,4);
	printf("%d\n",temp->data);
	temp=temp->next;
	printf("%d\n",temp->data);*/
	swap(&head,4,8);
	display(head);
	return 0;
}
