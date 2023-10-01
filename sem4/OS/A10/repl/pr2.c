#include "adt.h"

//testcases
//0 1 3 6 2 4 5 2 5 0 3 1 2 5 4 1 0 -17
//7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1 -20
//2 3 4 2 1 3 7 5 4 3 -10


struct node* pages=NULL,*mem=NULL;					//pages has ref str, mem is a n-list sized
int n,N;								//n-no. of frames req by P, N-total no of free frames
int table[10][100];							//final table
int row[100];								//a row of the table
int r=0,c=0;								//c-column, r-row

void init()								//initialises f array and removed of pages
{
	for(int i=0;i<100;i++)
  		f[i]=0;
	
	struct node *ptr=pages;
	while(ptr)
	{
		ptr->removed=0;
		ptr=ptr->next;
	}

}

void disptable()							//diaplay table
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
void dispmem(int data,int step)					//data->ele from pages, step is next page fault or '-' which means a hit
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
/*void dispmem(int data,int step)
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
	//n=n-c;
	while(c++<n)
		printf("- ");
	if(step==-1)
		printf("-> -");
	else
		printf("-> %d",step);
}*/
void FIFO()
{

	int count=0;					//count-page faults
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
	int count=0,far=INT_MIN,id,x;			//far-closest far
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
			x=ptr2->data;
			while(ptr2)
			{
				id=search(ptr->next,ptr2->data);	
				if(id==0)				//ele is not there
					break;
				if(id>far)				
				{
					far=id;
					x=ptr2->data;
					temp=ptr2;
				}
				ptr2=ptr2->next;
			}			
			if(ptr2)					//if ele isn't there 
				ptr2->data=ptr->data;
			else
			{
				/*ptr2=mem;
				while(ptr2->data!=x)
				{
					ptr2=ptr2->next;
				}
				ptr2->data=ptr->data;*/
				temp->data=ptr->data;
			}
		}
		count++;
		dispmem(ptr->data,count);
		ptr=ptr->next;
	}
}

void LRU()
{
	int count=0,min,id,x;
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
			x=ptr2->data;
			while(ptr2)
			{
				id=search2(pages,ptr,ptr2->data);
				if(id<min)
				{
					min=id;
					x=ptr2->data;
					temp=ptr2;
				}
				ptr2=ptr2->next;
        		}
			/*ptr2=mem;
			while(ptr2->data!=x)
			{
				ptr2=ptr2->next;
			}
			ptr2->data=ptr->data;*/
			temp->data=ptr->data;
		}
		count++;
		dispmem(ptr->data,count);
		ptr=ptr->next;
	}
}

void LFU()
{
	int count=0,m,min,ele,ELE,F;
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
      			F=-1;
      			m=0;
			min=INT_MAX;
			ptr2=mem;
			ELE=ptr2->data;
			while(ptr2)
			{
				ele=ptr2->data;
			 	if(f[ele]==min)		//other eles with same freq
			  		 			//F=min;
			  	{

					if(search2(pages,ptr,ele)<search2(pages,ptr,ELE))
					{
						min=f[ele];
						ELE=ele;
						temp=ptr2;
					}
			  	
			  	}
				else if(f[ele]<min)
				{
					min=f[ele];
					ELE=ele;
					temp=ptr2;
				}
				ptr2=ptr2->next;
		      	}
		     	/*if(F==min)				//if same,FIFO of ele with freq=x
		      	{
		      		ELE=F;
		      		m=1;
		      	}
			int data=rmv(pages,ELE,m);
			{
				ptr2=mem;
				while(ptr2 && (ptr2->data!=ELE && !m||ptr2->data!=data && m))
				{
					ptr2=ptr2->next;
				}
				ptr2->data=ptr->data;
				f[ptr2->data]++;
			}*/	
			rmv(pages,ELE);
			temp->data=ptr->data;
			f[temp->data]++;	
		}
		count++;
		dispmem(ptr->data,count);
		ptr=ptr->next;
	}
}
      
int main()
{
	int ch,ele;
	printf("\nPAGE REPLACEMENT ALGORITHMS\n1. READ_INPUT\n2. NO_OF_FRAMES\n3. FIFO\n4. OPTIMAL\n5. LRU\n6. LFU\n7. EXIT");
	do
	{
    		
		printf("\nEnter your choice: ");
		scanf("%d",&ch);
		free(mem);
		mem=NULL;
		
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
				init();			
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
		}
	}while(ch!=7);
	return 0;
}

