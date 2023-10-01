#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

struct process
{
	char pid[3];
	int n;
	int frames[100];
	int removed;
};

void shuffle(int *arr, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        srand(time(NULL));
        for (i = 0; i < n-1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = arr[j];
          arr[j] = arr[i];
          arr[i] = t;
        }
    }
}

int main()
{
	int phy_mem, pg_size, no_of_frames;
	printf("\nPaging Technique\n");
	printf("\nEnter the physical memory size(in KB): ");
	scanf("%d",&phy_mem);
	printf("Enter the page size(in KB) = ");
	scanf("%d",&pg_size);
	no_of_frames=(int)(phy_mem/pg_size);
	printf("Physical memory is divided into %d frames\n",no_of_frames);
	int nof;
	srand(time(0));
	while((nof=rand()%(no_of_frames+1))==0);
	printf("Number of frames: %d\n",nof);
	printf("\nAfter initialization\n");
	int i,f=0,r=nof-1;
    	int arr[1000];
    	for (i=0; i<nof; i++)
        	arr[i] = i;
    	shuffle(arr, nof);
    	printf("\nFree Frames:	"); 
    	for (i=0; i<nof; i++)
		printf("%d ", arr[i]+1);
	printf("\n");
	
	int ch,size,pages,no_of_proc=0;
	char name[3];
	struct process P[50];
	printf("\n1. Process request\n2. Deallocation\n3. Page Table display for all input process\n4. Free Frame list display\n5. Exit");
	do
	{
		printf("\nEnter the option: ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				printf("\nEnter the Process requirement(ID,size(in KB)): ");
				scanf("%s%d",name,&size);
				pages=(int)(size/pg_size);
				if(size && pages<=nof)
					printf("Process is divided into %d pages",pages);
				else
				{
					printf("Free frames not enough\n");
					break;
				}
				strcpy(P[no_of_proc].pid,name);
				P[no_of_proc].n=pages;
				P[no_of_proc].removed=0;
				i=0;
				printf("\nPage Table for %s:\n",P[no_of_proc].pid);
				while(i<pages)
				{
					P[no_of_proc].frames[i]=arr[f++];
					printf("Page %d : Frame %d\n",i,P[no_of_proc].frames[i]+1);
					i++;
				}	
				no_of_proc++;
				nof=r-f+1;
				break;
			case 2:
				printf("Enter the process ID to be de-allocated: ");
				scanf("%s",name);
				i=0;
				while(i<no_of_proc)
				{
					if(!P[i].removed && !strcmp(P[i].pid,name))
						break;
					i++;
				}
				if(i==no_of_proc)
				{
					printf("\nProcess %s is not there\n",name);
					break;
				}
				P[i].removed=1;
				for(int j=0;j<P[i].n;j++)
				{
					arr[++r]=P[i].frames[j];
				}
				nof=r-f+1;
				printf("Process %s Deallocted\n",name);
				break;
			case 3:
				i=0;
				printf("\n");
				while(i<no_of_proc)
				{
					if(!P[i].removed)
					{
						printf("\nPage Table for %s:\n",P[i].pid);
						for(int j=0;j<P[i].n;j++)
							printf("Page %d : Frame %d\n",j,P[i].frames[j]+1);
					}			
					i++;
					
				}
				printf("\n");				
				break;
			case 4:
				printf("\nFree Frames:	"); 
    				for (i=f; i<r+1; i++)
					printf("%d ", arr[i]+1);
				printf("\n");
				break;
			case 5:
				printf("\nExiting...\n");  
				return 0;
				break;
			default: printf("\nInvalid Option!\n");
		}	
	}while(ch!=5);
	return 0;
}
