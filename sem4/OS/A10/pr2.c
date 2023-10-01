#include "adt.h"
int table[100][100];
int C=0;
void dispmem(int data,struct node* mem,int n,int step,int N)
{
	printf("\n%d -> ",data);
	struct node *ptr=mem;
	int c=0;
	while(ptr)
	{
		printf("%d ",ptr->data);
		ptr=ptr->next;
		c++;
	}
	/*n=n-c;
	while(n)
	{
		printf("- ");
		table[n--%4][N]=' ';
	}*/
	for(int i=c;i<n;i++)
	{
		printf("- ");
		table[i%4][N]=' ';
		C++;
	}
	if(step==-1)
		printf("-> -");
	else
		printf("-> %d",step);
}
void FIFO(struct node *pages,int n)
{
	int N=0,count=0;
	struct node *ptr=pages,*mem=NULL,*ptr2=mem;
	while(ptr)
	{
		if(search(mem,ptr->data))
		{
			//table[count%4][N]=ptr->data;
			N++;
			dispmem(ptr->data,mem,n,-1,N);
			ptr=ptr->next;
			continue;
		}
		if(count<n)
		{
			insertEnd(&mem,ptr->data);
			table[C%4][N]=ptr->data;
		}
		else
		{
			if(!ptr2)
				ptr2=mem;
			table[C%4][N]=ptr->data;
			ptr2->data=ptr->data;
			ptr2=ptr2->next;
		}
		count++;
		C++;
		dispmem(ptr->data,mem,n,count,N);
		ptr=ptr->next;
		if(C%4==0)
			N++;
	}
	
}
int main()
{
	int ch,n,N,ele;
	struct node *pages=NULL;
	struct node *mem=NULL;
	printf("\nPAGE REPLACEMENT ALGORITHMS\n1. READ_INPUT\n2. FIFO\n3. OPTIMAL\n4. LRU\n5. LFU\n6. EXIT");
	do
	{
		printf("\nEnter yout choice: ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				free(pages);
				pages=NULL;
				printf("\nEnter the number of free frames: ");
				scanf("%d",&N);
				printf("Enter the number of frames required by the process: ");
				scanf("%d",&n);
				printf("Enter the reference string: ");
				for(int i=0;i<N;i++)
				{
					scanf("%d",&ele);
					insertEnd(&pages,ele);
				}
				display(pages);		
				break;
			case 2:
				free(mem);
				mem=NULL;
				FIFO(pages,n);
				printf("\n");
				for(int i=0;i<n;i++)
				{
					for(int j=0;j<N;j++)
					{
						printf("%d ",table[i][j]);
					} 
					printf("\n");
				}
				printf("\n");
				break;
			case 3:
				
				break;
			case 4:
				
				break;
			case 5:
				
				break;
			case 6:
				printf("\nExiting...\n");
				return 0;
				break;
		}
	
	}while(ch!=6);
	return 0;
}
