#include "adt.h"
#include<string.h>
#include<limits.h>

int table[10][100];
int row[100],buf[100];
int k=0,t=0;
void dispmem(int data,struct node* mem,int n,int step)
{
	t=0;
	printf("\n%d -> ",data);
	row[t++]=data;
	struct node *ptr=mem;
	int c=0;
	while(ptr)
	{
		printf("%d ",ptr->data);
		row[t++]=ptr->data;
		ptr=ptr->next;
		c++;
	}
	n=n-c;
	while(n--)
	{
		printf("- ");
		row[t++]=-1;
	}
	if(step==-1)
	{
		printf("-> -");
		row[t++]=-1;
	}
	else
	{
		printf("-> %d",step);
		row[t++]=step;
	}
	strcat(row,"\0");
	//printf("\n%s\n",row);
	for(int i=0;i<t;i++)
	{
		table[i][k]=row[i];
	}
	k++;
	/*for(int i=0;i<n;i++)
	{
		strcat(table[i],row[i]);
	}*/
	//printf("\n%s\n",table[0]);
	memset(row, 0, sizeof(row));
	memset(buf, 0, sizeof(buf));
}
void FIFO(struct node *pages,int n)
{
	int count=0;
	struct node *ptr=pages,*mem=NULL,*ptr2=mem;
	while(ptr)
	{
		if(search(mem,ptr->data))
		{
			dispmem(ptr->data,mem,n,-1);
			ptr=ptr->next;
			continue;
		}
		if(count<n)
			insertEnd(&mem,ptr->data);
		else
		{
			if(!ptr2)
				ptr2=mem;
			ptr2->data=ptr->data;
			ptr2=ptr2->next;
		}
		count++;
		dispmem(ptr->data,mem,n,count);
		ptr=ptr->next;
	}
	printf("\n");
}

void opt(struct node* pages,int n)
{
	int count=0,max=INT_MIN,id,x;
	struct node *ptr=pages,*mem=NULL,*ptr2=mem,*temp;
	while(ptr)
	{
		if(search(mem,ptr->data))
		{
			dispmem(ptr->data,mem,n,-1);
			ptr=ptr->next;
			continue;
		}
		if(count<n)
			insertEnd(&mem,ptr->data);
		else
		{
			max=INT_MIN;
			ptr2=mem;
			x=ptr2->data;
			while(ptr2)
			{
				id=search(ptr->next,ptr2->data);
				if(id==0)
					break;
				if(id>max)
				{
					max=id;
					x=ptr2->data;
				}
				ptr2=ptr2->next;
			}
			if(ptr2)
				ptr2->data=ptr->data;
			else
			{
				ptr2=mem;
				while(ptr2->data!=x)
				{
					ptr2=ptr2->next;
				}
				ptr2->data=ptr->data;
			}
		}
		count++;
		dispmem(ptr->data,mem,n,count);
		ptr=ptr->next;
	}
	printf("\n");
}

int main()
{
	int ch,n,N,ele;
	struct node *pages=NULL;
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
				FIFO(pages,n);
				printf("\n");
				for(int i=0;i<n+2;i++)
				{
					for(int j=0;j<N;j++)
					{
						if(table[i][j]!=-1)
							printf("%-*d|",2,table[i][j]);
						else
							printf("- |");
					} 
					printf("\n");
					if(i==0||i==n||i==n+1)
					{
						for(int l=0;l<N;l++)
							printf("--+");
						printf("\n");
					}
					memset(table[i],0,sizeof(table[i]));
				}
				printf("\n");
				k=0;
				break;
			case 3:
				opt(pages,n);
				printf("\n");
				for(int i=0;i<n+2;i++)
				{
					for(int j=0;j<N;j++)
					{
						if(table[i][j]!=-1)
							printf("%-*d|",2,table[i][j]);
						else
							printf("- |");
					} 
					printf("\n");
					if(i==0||i==n||i==n+1)
					{
						for(int l=0;l<N;l++)
							printf("--+");
						printf("\n");
					}
					memset(table[i],0,sizeof(table[i]));
				}
				printf("\n");
				k=0;
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
