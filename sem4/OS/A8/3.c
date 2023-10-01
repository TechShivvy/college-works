#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
struct node
{
  int start;
  int end;
  int size;
  int hole;
  char status[3];
  struct node *next;
};

struct node * insertEnd(struct node *,struct node *);
void disp(struct node *p);
void sortedInsert(struct node** head, struct node* newNode);
void insertSort(struct node** head);
struct node* Clone(struct node* list);
struct node* merge(struct node* h1, struct node* h2);

void combine(struct node **p)
{
	struct node *ptr=*p,*temp;
	while(ptr)
	{
		temp=ptr;
		while(temp->next && temp->hole && temp->next->hole && temp->end==temp->next->start)
			temp=temp->next;
		ptr->next=temp->next;
		ptr->end=temp->end;
		ptr=ptr->next;
	}
}
struct node * find_delete(struct node **p,char *pid)
{
	struct node *ptr=*p,*prev;
	if (ptr && strcmp(ptr->status,pid)==0) {
        *p = ptr->next; // Changed head
        strcpy(ptr->status,"H");
        ptr->hole=1;
        return ptr;
    }
	while(ptr && strcmp(ptr->status,pid))
	{
		prev=ptr;	
		ptr=ptr->next;
	}
	if(!ptr)
		return NULL;
	strcpy(ptr->status,"H");
        ptr->hole=1;
	prev->next=ptr->next;
}	
void table(struct node *p,char str[])				
{
	struct node *ptr=p;
  	if(!ptr)
  	{
  		printf("NULL\n\n");
  		return;
  	}
	for(int i=0;i<strlen(str);i++)			// top line
		printf("%c",str[i]=='|'?'+':str[i]=='-'?' ':'-');
	
	printf("\n%s\n",str);					// chart
	
	for(int i=0;i<strlen(str);i++)
		printf("%c",str[i]=='|'?'+':str[i]=='-'?' ':'-');		// bottom line
	printf("\n");
	//printf("\n%d",ptr->start);
	int end,s;
	end=ptr->end;
	s=strlen(ptr->status);
	//ptr=ptr->next;
	while(ptr)						// mem add 
	{
		if(!ptr->next||ptr->end==ptr->next->start)
			printf("%-*d",9+strlen(ptr->status),ptr->start);
		else
			printf("%-*d%-*d",9+strlen(ptr->status),ptr->start,9,ptr->end);
		end=ptr->end;
		s=strlen(ptr->status);
		ptr=ptr->next;
	}
	printf("%d",end);
	printf("\n\n\n");
}

void disp1(struct node *p)
{
	char buf[100],mem[1000];
	
	struct node *ptr=p;
	strcpy(mem,"|");
	while(ptr)
	{
		if(!ptr->next||ptr->end==ptr->next->start)
    			sprintf(buf,"    %s    |",ptr->status);
    		else if(ptr->end!=ptr->next->start)
    			sprintf(buf,"    %s    |---------|",ptr->status);
	    	strcat(mem,buf);
	    	ptr=ptr->next;
	}
	table(p,mem);
}
void display(struct node *p,struct node *q)
{
	printf("\nAlloc>\n\n");
	disp1(p);
	printf("Free>\n\n");
	disp1(q);
	/*char buf[100],mem[1000];
	
	struct node *ptr=p;
	strcpy(mem,"|");
	printf("\nAlloc>\n\n");
	while(ptr)
	{
		if(!ptr->next||ptr->end==ptr->next->start)
    			sprintf(buf,"    %s    |",ptr->status);
    		else if(ptr->end!=ptr->next->start)
    			sprintf(buf,"    %s    |---------|",ptr->status);
	    	strcat(mem,buf);
	    	ptr=ptr->next;
	}
	table(p,mem);
	
	ptr=q;
	strcpy(mem,"|");
	printf("Free>\n\n");
	while(ptr)
	{
    		if(!ptr->next||ptr->end==ptr->next->start)
    			sprintf(buf,"    %s    |",ptr->status);
    		else if(ptr->end!=ptr->next->start)
    			sprintf(buf,"    %s    |---------|",ptr->status);
	    	strcat(mem,buf);
	    	ptr=ptr->next;
	}
	table(q,mem);*/
	
	//struct node* r=Clone(p);
    	struct node *r=merge(Clone(p),Clone(q));
    	//ptr=r;
	//strcpy(mem,"|");
    	printf("Phy>\n\n");
    	disp1(r);
	/*while(ptr)
	{
    		sprintf(buf,"    %s    |",ptr->status);
    		//else if(ptr->end!=ptr->next->start)
    		//	sprintf(buf,"    %s    |---------|",ptr->status);
	    	strcat(mem,buf);
	    	ptr=ptr->next;
	}
    	table(r,mem);*/
}

struct node* newNode(int start,int end)
{
	struct node *temp=(struct node *)malloc(sizeof(struct node));
	strcpy(temp->status,"H");
	temp->hole=1;
	temp->end=end;
	temp->start=start;
	temp->size=temp->end-temp->start;
	temp->next=NULL;
	return temp;
}

int firstfit(struct node *f,int size)
{
	struct node *ptr=f;
	while(ptr && !(ptr->size>=size))
	{
		ptr=ptr->next;
	}
 	if(!ptr)
 		return -1;
 	return ptr->size;
}

int worst(struct node *f,int size)
{
    	struct node *ptr=f;;
    	int max = INT_MIN;

    while (ptr) {
        if (ptr->size-size>0 && max < ptr->size-size)
            max = ptr->size-size;
  
        ptr = ptr->next;
        
    }
    if(max=INT_MIN)
    	return -1;
    return max+size;
}

int bestfit(struct node *f,int size)
{
    	struct node *ptr=f;;
    	int min = INT_MAX;

    while (ptr) {
        if (ptr->size-size>0 && min > ptr->size-size)
            min = ptr->size-size;
  
        ptr = ptr->next;
        
    }
    if(min==INT_MAX)
    	return -1;
    return min+size;	
}
struct node *bw(struct node **f,char *pid,int size)
{
	
}
struct node* delete(struct node **f,char *pid,int size,int ptrsize)
{
	if(ptrsize-size<0)
		return NULL;
	struct node *ptr=*f,*prev;
	
	if(ptr->size==ptrsize)
	{
	if (ptr != NULL && ptr->size >= size && ptr->hole)
	{
		if(ptr->size == size)
		{
			*f = ptr->next; // Changed head
			strcpy(ptr->status,pid);
			ptr->hole=0;
			//free(temp); // free old head
			return ptr;
		}
		else
		{
			struct node *temp1=newNode(ptr->start,ptr->start+size);
			struct node *temp2=newNode(ptr->start+size,ptr->end);
			temp1->hole=0;
			*f=temp2;
			temp2->next=ptr->next;
			strcpy(temp1->status,pid);
			free(ptr);
			return temp1;
		}
    	}
    }
    
	while(ptr && !(ptr->size==ptrsize))
	{
		prev = ptr;
		ptr=ptr->next;
	}
	if(ptr==NULL)
		return NULL;
	if(ptr->size==size)
	{
		prev->next = ptr->next;
		strcpy(ptr->status,pid);
		ptr->hole=0;
		return ptr;
	}
	else
	{
		struct node *temp1=newNode(ptr->start,ptr->start+size);
		struct node *temp2=newNode(ptr->start+size,ptr->end);
		temp1->hole=0;
		prev->next=temp2;
		temp2->next=ptr->next;
		strcpy(temp1->status,pid);
		free(ptr);
		return temp1;
	}
	
}
void insert(struct node *temp, struct node **alloc)
{
	if(!temp)
		return;
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
	int n;
	int start,end;
	printf("\nEnter the Memory Representation:");
	printf("\nEnter the no.of partitions in memory: ");
	scanf("%d",&n);
	struct node *fpool= NULL,*alloc=NULL,*temp=NULL;
	for(int i=0;i<n;i++)
	{
		printf("Enter Starting and ending address of partition %d: ",i+1);
		scanf("%d%d",&start,&end);
		if(start>=end||i && temp->end!=start)
		{
			i--;
			printf("Invalid entry,enter again\n");
		}
		else
		{
			temp=newNode(start,end);
			fpool=insertEnd(fpool,temp);
		}
	}
	
	insertSort(&fpool);
	
	struct node *ptr=fpool;
	/*while(ptr->next)
	{
		if(ptr->end>ptr->next->start)
		{
			printf("\nMemory partitions arent mapped crctly\n");
			return 0;
		}
		ptr=ptr->next;	
	}*/
	display(alloc,fpool);
	/*printf("Alloc> ");
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
    	table(copy,mem);*/
	int ch,size;
	char pid[3];
	do{
	printf("1. Entry / Allocate\n2. Exit / Deallocate \n3. Display \n4. Coalescing of Holes \n5. Back to Algorithm \nEnter your choice: ");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:
			printf("Enter process id : ");
			scanf("%s",pid);
			printf("Enter size needed : ");
			scanf("%d",&size);
			//insert(delete(&fpool,pid,size,firstfit(fpool,size)),&alloc);
			insert(delete(&fpool,pid,size,bestfit(fpool,size)),&alloc);
			/*printf("Alloc> ");
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
    	table(copy,mem);*/display(alloc,fpool);
			break;
		case 2:
			printf("Enter process id : ");
			scanf("%s",pid);
			insert(find_delete(&alloc,pid),&fpool);
			display(alloc,fpool);	
			break;
		case 3:
			
			break;
		case 4:
			combine(&fpool);
			display(alloc,fpool);
			break;
		case 5:
			return 0;
			break;
		default: printf("\nInavlid Input\n");
	}
	}while(ch!=5);
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
