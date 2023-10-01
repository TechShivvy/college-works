#include "adt.h"
#include<string.h>
char table[10][100];
char row[100],buf[100];
int k=0;
void dispmem(int data,struct node* mem,int n,int step)
{
	
	printf("\n%d -> ",data);
	sprintf(buf,"%d",data);
	strcat(row,buf);
	struct node *ptr=mem;
	int c=0;
	while(ptr)
	{
		printf("%d ",ptr->data);
		sprintf(buf,"%d",ptr->data);
		strcat(row,buf);
		ptr=ptr->next;
		c++;
	}
	n=n-c;
	while(n--)
	{
		printf("- ");
		strcat(row,"-");
	}
	if(step==-1)
	{
		printf("-> -");
		strcat(row,"-");
	}
	else
	{
		printf("-> %d",step);
		sprintf(buf,"%d",step);
		strcat(row,buf);
	}
	strcat(row,"\0");
	printf("\n%s\n",row);
	for(int i=0;i<strlen(row);i++)
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
				for(int i=0;i<n+2;i++)
				{
					for(int j=0;j<N;j++)
					{
						printf("%c ",table[i][j]);
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
