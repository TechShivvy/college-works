#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
  int start;
  int end;
  int size;
  char status[3];
  struct node *next;
};

struct node * insertEnd(struct node *,struct node *);
void disp(struct node *p);
void sortedInsert(struct node** head, struct node* newNode);
void insertSort(struct node** head);
struct node* Clone(struct node* list);
struct node* merge(struct node* h1, struct node* h2);

void table(struct node *p,char str[])				
{
	struct node *ptr=p;
  	if(!ptr)
  	{
  		printf("\nNULL\n");
  		return;
  	}
	for(int i=0;i<strlen(str);i++)			// top line
		printf("%c",str[i]=='|'?'+':'-');
	
	printf("\n%s\n",str);					// chart
	
	for(int i=0;i<strlen(str);i++)
		printf("%c",str[i]=='|'?'+':'-');		// bottom line
	
	printf("\n%d",ptr->start);
	while(ptr)						// mem add 
	{
		printf("%*d",9+strlen(ptr->status),ptr->end);
		ptr=ptr->next;
	}
	printf("\n");
}


struct node* delete(struct node **f,char *pid,int size)
{
	struct node *ptr=*f,*prev;
	
	if (ptr != NULL && ptr->size >= size) {
        *f = ptr->next; // Changed head
        ptr->size=size;
	strcpy(ptr->status,pid);
        //free(temp); // free old head
        return ptr;
    }
    
	while(ptr && !(ptr->size>=size))
	{
		prev = ptr;
		ptr=ptr->next;
	}
	if(ptr==NULL)
		return NULL;
	prev->next = ptr->next;
	
	ptr->size=size;
	strcpy(ptr->status,pid);
	return ptr;
	
}
void insert(struct node *temp, struct node **alloc)
{
	struct node *ptr=*alloc;
	if(!*alloc)
	{
		*alloc=insertEnd(*alloc,temp);
		return;
	}
	if(temp->start<ptr->start)
	{
		temp->next=*alloc;
		*alloc=temp;
		return;		
	}
	while(ptr && temp->start>ptr->next->start)
		ptr=ptr->next;
	temp->next=ptr->next;
	ptr->next=temp;
	
} 
int main()
{
	int n,start,end;
	printf("\nEnter the Memory Representation:");
	printf("\nEnter the no.of partitions in memory: ");
	scanf("%d",&n);
	struct node *fpool= NULL,*alloc=NULL,*temp=(struct node *)malloc(sizeof(struct node));
	strcpy(temp->status,"H");
	for(int i=0;i<n;i++)
	{
		printf("Enter Starting and ending address of partition %d: ",i+1);
		scanf("%d%d",&temp->start,&temp->end);
		temp->size=temp->end-temp->start;
		if(temp->start>temp->end)
		{
			i--;
			printf("Invalid entry,enter again\n");
		}
		else
			fpool=insertEnd(fpool,temp);
		disp(fpool);
	}
	
	//insertSort(&fpool);
	
	struct node *ptr=fpool;
	while(ptr->next)
	{
		if(ptr->end>ptr->next->start)
		{
			printf("\nMemory partitions arent mapped crctly\n");
			return 0;
		}
		ptr=ptr->next;	
	}
	printf("Alloc> ");
	//alloc=(struct node *)malloc(sizeof(struct node));
	//alloc->end=70,alloc->start=50,alloc->next=NULL;
	//strcpy(alloc->status,"P1");
	disp(alloc);
	printf("Free> ");
	disp(fpool);
	
	struct node* copy=Clone(fpool);
    	copy=merge(fpool,alloc);
    	printf("Phy> ");
    	disp(copy);
    	
    	char buf[100],mem[1000];
	strcpy(mem,"|");
	ptr=copy;
	while(ptr)
	{
    		sprintf(buf,"    %s    %s",ptr->status,"|");
	    	strcat(mem,buf);
	    	ptr=ptr->next;
	}
    	table(copy,mem);
	int ch,size;
	char pid[3];
	printf("1.Entry / Allocate\n2. Exit / Deallocate \n3. Display \n4. Coalescing of Holes \n5. Back to Algorithm \nEnter you choice: ");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:
			printf("Enter process id : ");
			scanf("%s",pid);
			printf("Enter size needed : ");
			scanf("%d",&size);
			insert(delete(&fpool,pid,size),&alloc);
			printf("Alloc> ");
	//alloc=(struct node *)malloc(sizeof(struct node));
	//alloc->end=70,alloc->start=50,alloc->next=NULL;
	//strcpy(alloc->status,"P1");
	disp(alloc);
	printf("Free> ");
	disp(fpool);
	
	struct node* copy=Clone(fpool);
    	copy=merge(fpool,alloc);
    	printf("Phy> ");
    	disp(copy);
    	
    	char buf[100],mem[1000];
	strcpy(mem,"|");
	ptr=copy;
	while(ptr)
	{
    		sprintf(buf,"    %s    %s",ptr->status,"|");
	    	strcat(mem,buf);
	    	ptr=ptr->next;
	}
    	table(copy,mem);
			break;
		case 2:
			
			break;
		case 3:
			
			break;
		case 4:
			
			break;
		case 5:
			return 0;
			break;
		default: printf("\nInavlid Input\n");
	}
	return 0;
}

struct node * insertEnd(struct node *p,struct node *temp)
{
  struct node *ptr=p;
  if(ptr==NULL)
   {p=temp;
   p->next=NULL;}
  else
  {
    while(ptr->next)
     {ptr=ptr->next;}
      
    ptr->next=temp;
    temp->next=NULL;
  }
  return p;
}

void disp(struct node *p)
{
  struct node *ptr=p;
  if(!ptr)
  	printf("\nNULL\n");
  while(ptr)
  {
    printf("%d-----%d-->",ptr->start,ptr->end);
    ptr=ptr->next;
  }
  printf("\b\b\b   \n");
}

void sortedInsert(struct node** head, struct node* newNode)
{
    struct node dummy;
    struct node* current = &dummy;
    dummy.next = *head;
 
    while (current->next && current->next->start < newNode->start) {
        current = current->next;
    }
 
    newNode->next = current->next;
    current->next = newNode;
    *head = dummy.next;
}

void insertSort(struct node** head)
{
    struct node* result = NULL;
    struct node* current = *head;   
    struct node* next;
 
    while (current)
    {
        next = current->next;
 
        sortedInsert(&result, current);
        current = next;
    }
 
    *head = result;
}
struct node* Clone(struct node* list)
{
    if (list == NULL) 
    	return NULL;

    struct node* result = (struct node*)malloc(sizeof(struct node));
    result->start = list->start;
    result->end = list->end;
    result->size=list->size;
    strcpy(result->status,list->status);
    result->next = Clone(list->next);
    return result;
}
struct node* merge(struct node* h1, struct node* h2)
{
    if (!h1)
        return h2;
    if (!h2)
        return h1;

    if (h1->start < h2->start) {
        h1->next = merge(h1->next, h2);
        return h1;
    }
    else {
        h2->next = merge(h1, h2->next);
        return h2;
    }
}
