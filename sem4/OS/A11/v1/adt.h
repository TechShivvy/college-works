#include<stdio.h>
#include<stdlib.h>

typedef struct block
{
	int id;
	int status;
	struct block *nextMem;
	struct block *nextFile;
}Block;

Block* newNode(int id);
void insertEnd(Block **head,int id);
Block* search(Block* head, int id);
void display(Block *list);

Block* newNode(int id)
{
	Block *temp=(Block *)malloc(sizeof(Block));
	temp->id=id;
	temp->nextMem=NULL;
	temp->nextFile=NULL;
	temp->status=1;
	return temp;
}

void insertEnd(Block **head,int id)
{
	Block *ptr=*head;
	if(!ptr)
	{
		*head=newNode(id);
		(*head)->nextMem=NULL;
		(*head)->nextFile=NULL;
	}
	else
	{
		while(ptr->nextMem)
			ptr=ptr->nextMem;
		ptr->nextMem=newNode(id);
		ptr->nextFile=NULL;
	}
}

Block* search(Block* head, int id)
{
	Block* ptr = head;
	while (ptr && ptr->id!=id)
		ptr = ptr->nextMem;
	if(!ptr)
		return NULL;
	return ptr;
}

void display(Block *list)
{
	Block* ptr=list;
	printf("\n");
	while(ptr)
	{
		printf("%d\t",ptr->id);
		ptr=ptr->nextMem;
	}
	printf("\n");
}
