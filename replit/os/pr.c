#include "adt.h"

//testcases
//0 1 3 6 2 4 5 2 5 0 3 1 2 5 4 1 0 -17
//7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1 -20
//2 3 4 2 1 3 7 5 4 3 -10
//3 2 1 3 4 1 6 2 4 3 4 2 1 4 5 2 1 3 4 - 19
struct node* pages=NULL,*mem=NULL;			//pages has ref str, mem is a n-list sized
int n,N;						//n-no. of frames req by P, N-total no of free frames
int table[10][100];					//final table
int row[100];						//a row of the table
int r=0,c=0;						//c-column, r-row
int count=0;						//Total Number of Page Faults

void init();						//initialises f array and removed of pages
void disptable();					//diaplay table
void dispmem(int data,int step);			//data->ele from pages, step is next page fault or '-' which means a hit
void FIFO();
void OPT();
void LRU();
void LFU();
   
int main()
{
	int ch,ele;
	printf("\nPAGE REPLACEMENT ALGORITHMS\n1. READ_INPUT\n2. NO_OF_FRAMES\n3. FIFO\n4. OPTIMAL\n5. LRU\n6. LFU\n7. EXIT");
	do
	{
    		
		printf("\nEnter your choice: ");
		scanf("%d",&ch);
		init();
		switch(ch)
		{
			case 1:
				free(pages);
				pages=NULL;
				printf("\nEnter the number of free frames: ");
				scanf("%d",&N);
				printf("Enter the reference string: ");
				for(int i=0;i<N;i++)
				{
					scanf("%d",&ele);
					insertEnd(&pages,ele);
				}
				display(pages);		
				
			case 2:
				printf("\nEnter the number of frames required by the process: ");
				scanf("%d",&n);
				break;
			case 3:
				FIFO();
				break;
			case 4:
				OPT();
				break;
			case 5:
				LRU();
				break;
			case 6:			
				LFU();
				break;
			case 7:
				printf("\nExiting...\n");
				return 0;
				break;
		}
		if(!(ch==1||ch==2))
		{
			printf("\n");
			disptable();
			printf("\nTotal Number of Page Faults:%d\n",count);
		}
	}while(ch!=7);
	return 0;
}

void init()	
{			
	free(mem);
	mem=NULL;				
	for(int i=0;i<100;i++)
  		f[i]=0;
	
	struct node *ptr=pages;
	while(ptr)
	{
		ptr->removed=0;
		ptr=ptr->next;
	}

}

void disptable()							
{
	printf("\n");
	for(int i=0;i<n+2;i++)
	{
		for(int j=0;j<N;j++)
		{
			if(table[i][j]!=-1)
				printf(" %-*d|",2,table[i][j]);
			else
				printf(" - |");
		} 
		printf("\n");
		if(i==0||i==n||i==n+1)
		{
			for(int l=0;l<N;l++)
				printf("---+");
			printf("\n");
		}
		memset(table[i],0,sizeof(table[i]));
	}
	c=0;
	
}
void dispmem(int data,int step)
{
	r=0;
	printf("\n%d -> ",data);
	row[r++]=data;
	struct node *ptr=mem;
	int j=0;
	while(ptr)
	{
		printf("%d ",ptr->data);
		row[r++]=ptr->data;
		ptr=ptr->next;
		j++;
	}
	while(j++<n)
	{
		printf("- ");
		row[r++]=-1;
	}
	if(step==-1)
	{
		printf("-> -");
		row[r++]=-1;
	}
	else
	{
		printf("-> %d",step);
		row[r++]=step;
	}
	for(int i=0;i<r;i++)
	{
		table[i][c]=row[i];
	}
	c++;
	memset(row, 0, sizeof(row));

}

void FIFO()
{

	count=0;					//count-page faults
	struct node *ptr=pages,*ptr2=mem;
	while(ptr)
	{
		if(search(mem,ptr->data))		//if ele from pages already present in mem, skip
		{
			dispmem(ptr->data,-1);
			ptr=ptr->next;
			continue;
		}
		if(count<n)				//first n elements, directly
			insertEnd(&mem,ptr->data);
		else
		{
			if(!ptr2)			//if reached the end, again from start
				ptr2=mem;
			ptr2->data=ptr->data;
			ptr2=ptr2->next;
		}
		count++;
		dispmem(ptr->data,count);
		ptr=ptr->next;
	}
}

void OPT()
{
	count=0;
	int far=INT_MIN,id,flag;					//far-closest far
	struct node *ptr=pages,*ptr2=mem,*temp;
	while(ptr)
	{
		if(search(mem,ptr->data))
		{
			dispmem(ptr->data,-1);
			ptr=ptr->next;
			continue;
		}
		if(count<n)
			insertEnd(&mem,ptr->data);
		else
		{
			far=INT_MIN;
			ptr2=mem;
      temp=ptr2;
      flag=1;
			while(ptr2)
			{
				id=search(ptr->next,ptr2->data);	
				if(id==0)				//ele is not there
        {
          id=search(pages,ptr2->data);
          if(id<far && temp!=ptr2 || temp==ptr2)
          {
            far=id;
  					temp=ptr2;
            flag=0;
          }
        }
				if(id>far && flag)				
				{
					far=id;
					temp=ptr2;
				}
				ptr2=ptr2->next;
			}			
        rmv(pages,temp->data);
				temp->data=ptr->data;
		}
		count++;
		dispmem(ptr->data,count);
		ptr=ptr->next;
	}
}

void LRU()
{
	count=0;
	int min,id;
	struct node *ptr=pages,*ptr2=mem,*temp;
	while(ptr)
	{
		if(search(mem,ptr->data))
		{
			dispmem(ptr->data,-1);
			ptr=ptr->next;
			continue;
		}
		if(count<n)
			insertEnd(&mem,ptr->data);
		else
		{
			min=INT_MAX;
			ptr2=mem;
			while(ptr2)
      {
				id=search2(pages,ptr,ptr2->data);
				if(id<min)
				{
					min=id;
					temp=ptr2;
				}
				ptr2=ptr2->next;
			}
			temp->data=ptr->data;
		}
		count++;
		dispmem(ptr->data,count);
		ptr=ptr->next;
	}
}

void LFU()
{
	count=0;
	int min,ele;
	struct node *ptr=pages,*ptr2=mem,*temp;
	while(ptr)
	{
		if(search(mem,ptr->data))
		{
			dispmem(ptr->data,-1);
			f[ptr->data]++;
      			ptr=ptr->next;
			continue;
		}
		if(count<n)
    		{
    			insertEnd(&mem,ptr->data);
      			f[ptr->data]++;
      		}
		else
		{
			min=INT_MAX;
			ptr2=mem;
			//ELE=ptr2->data;
      temp=ptr2;
      while(ptr2)
			{
				ele=ptr2->data;
			 	if(f[ele]==min)		//other eles with same freq
			  	{

					if(search(pages,ele)<search(pages,temp->data))	//for FIFO, if new ele comes b4 prev ELE, update
					{
						temp=ptr2;
					}
			  	
			  	}
				else if(f[ele]<min)
				{
					min=f[ele];
					temp=ptr2;
				}
				ptr2=ptr2->next;
		      	}	
			rmv(pages,temp->data);
			temp->data=ptr->data;
			f[temp->data]++;	
		}
		count++;
		dispmem(ptr->data,count);
		ptr=ptr->next;
	}
}
