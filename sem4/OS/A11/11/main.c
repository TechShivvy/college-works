#include "adt.h"
#include<time.h>

typedef struct fileTable
{
	char name[25];
	int size;
	int start;
	int end;
	int length;
	int index;
}File;

void init_file(File *f);
void shuffle(int *arr, size_t n);	
void contiguous(File *f, int no_of_files, int blk_size, int no_of_blks);
void linked(File *const f,const int no_of_files,const int blk_size,const int no_of_blks);
void indexed(File *const f,const int no_of_files,const int blk_size,const int no_of_blks);

int main()
{
	File f[100];
	int mem_size,blk_size,no_of_blks,no_of_files;
	printf("Enter Main Memory size(in KB): ");
	scanf("%d",&mem_size);
	printf("Size of each block in the disk(in KB): ");
	scanf("%d",&blk_size);
	no_of_blks=mem_size/blk_size;
	
	printf("Enter the no. of files to be allocated: ");
	scanf("%d",&no_of_files);
	getchar();
	for(int i=0;i<no_of_files;i++)
	{
		init_file(&f[i]);
		printf("Name of File%d: ",i+1);
		scanf("%[^\n]s",f[i].name);
		printf("Size of File%d: ",i+1);
		scanf("%d",&f[i].size);
		getchar();
	}
	int ch;
	printf("\n----------------FILE ALLOCATION TECHNIQUES----------------\n");
	printf("\n1. Contiguous\n2. Linked\n3. Indexed\n4. Exit");
	do
	{
		printf("\n\nEnter your choice: ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				printf("\n------CONTIGUOUS ALLOCATION------\n\n");
				contiguous(f,no_of_files,blk_size,no_of_blks);
				break;
			case 2:
				printf("\n------LINKED ALLOCATION------\n\n");
				linked(f,no_of_files,blk_size,no_of_blks);
				break;
			case 3:
				printf("\n------INDEXED ALLOCATION------\n\n");
				indexed(f,no_of_files,blk_size,no_of_blks);
				break;
			case 4:
				printf("\nExiting...\n");
				return 0;
			default:
				printf("\nInvalid Choice!\n");
		}
	}while(ch!=4);
	return 0;
}

void init_file(File *f)
{
	f->start=-1;
	f->end=-1;
	f->size=-1;
	f->length=-1;
	f->index=-1;
}

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

void contiguous(File *f, int no_of_files, int blk_size, int no_of_blks)
{
	srand(time(NULL));
	Block* list=NULL;
	Block *ptr,*temp;
	int arr[no_of_blks];
	for(int i=0;i<no_of_blks;i++)
	{
		insertEnd(&list,i);
		arr[i]=i;
	}
	shuffle(arr, no_of_blks);
	int id,k,flag,blk_req,count,start;
	for(int i=0;i<no_of_files;i++)
	{
		flag=0;
		k=0;
		blk_req=f[i].size/blk_size;
		if(f[i].size%blk_size)
			blk_req++;
		while(k<no_of_blks && !flag)
		{
			id=arr[k++];
			ptr=search(list,id);
			if(!ptr->status)
				continue;
			count=0;
			start=id;
			temp=ptr;
			while(temp)
			{
				if(temp->status)
				{
					count++;
					if(count==blk_req)
					{
						flag=1;
						break;
					}
				}
				else
					break;
				temp=temp->nextMem;
			}
			if(flag)
			{
				f[i].start=start;
				f[i].length=blk_req;
				temp=ptr;
				for(int j=0;j<blk_req;j++)
				{
					temp->status=0;
					temp=temp->nextMem;
				}
			}
		}
		if(!flag)
			printf("Unable to allocate file %s\n",f[i].name);
	}
	printf("\n            DIRECTORY STRUCTURE\n");
    	printf(" +----------------------+-------+--------+\n");
    	printf(" |      File Name       | Start | Length |\n");
    	printf(" +----------------------+-------+--------+\n");

   	for (int i = 0; i < no_of_files; i++)
        {
        	if (f[i].length > 0)
			printf(" | %-20s | %-5d | %-6d |\n", f[i].name, f[i].start, f[i].length);
    	}
    	printf(" +----------------------+-------+--------+\n");		
}

void linked(File *const f,const int no_of_files,const int blk_size,const int no_of_blks)
{
	srand(time(NULL));
	Block* list=NULL;
	Block *ptr,*curr,*next;
	int arr[no_of_blks];
	for(int i=0;i<no_of_blks;i++)
	{
		insertEnd(&list,i);
		arr[i]=i;
	}
	shuffle(arr, no_of_blks);
	int id,k,flag,blk_req,count,start;
	for(int i=0;i<no_of_files;i++)
	{
		flag=0;
		k=0;
		count=0;
		blk_req=f[i].size/blk_size;
		if(f[i].size%blk_size)
			blk_req++;
		int *allocted=(int *)calloc(blk_req,sizeof(int));
		while(k<no_of_blks && !flag)
		{
			id=arr[k++];
			ptr=search(list,id);
			if(!ptr->status)
				continue;
			ptr->status=0;
			allocted[count++]=id;
			if(count==blk_req)
				flag=1;
		}
		if(!flag)
		{
			printf("Unable to allocate file %s\n",f[i].name);
			for(int j=0;j<count;j++)
			{
				ptr=search(list,allocted[j]);
				ptr->status=1;
			}
		}
		else
		{
			f[i].start=allocted[0];
			f[i].end=allocted[blk_req-1];
			f[i].length=blk_req;
			for(int j=0;j<blk_req-1;j++)
			{
				curr=search(list,allocted[j]);
				next=search(list,allocted[j+1]);
				curr->nextFile=next;
			}
		}
		free(allocted);
	}
	printf("\n\t\tDIRECTORY STRUCTURE\n");
    	printf(" +----------------------+-------------+-----------+\n");
    	printf(" |      File Name       | Start Block | End Block |\n");
    	printf(" +----------------------+-------------+-----------+\n");
    	for (int i=0;i<no_of_files;i++)
        {
        	if (f[i].end>=0)
            		printf(" | %-20s |     %-2d      |    %-2d     |\n",f[i].name, f[i].start, f[i].end);
    	}
    	printf(" +----------------------+-------------+-----------+\n");

    	printf("\nIndividual File listing:");
   	for (int i=0;i<no_of_files;i++)
	{
		if (f[i].end>=0)
		{
			printf("\n\n File Name: %-20s",f[i].name);
		    	ptr = search(list, f[i].start);
		    	while (ptr)
		   	{
		        	printf(" %d ->", ptr->id);
		        	ptr = ptr->nextFile;
		    	}
		    	printf("\b\b  \b\b");
		}
        }
}

void indexed(File *const f,const int no_of_files,const int blk_size,const int no_of_blks)
{
	srand(time(NULL));
	Block* list=NULL;
	Block *ptr,*temp;
	int arr[no_of_blks];
	for(int i=0;i<no_of_blks;i++)
	{
		insertEnd(&list,i);
		arr[i]=i;
	}
	shuffle(arr, no_of_blks);
	int id,k,flag,blk_req,count,start;
	for(int i=0;i<no_of_files;i++)
	{
		flag=0;
		k=0;
		count=0;
		blk_req=f[i].size/blk_size;
		if(f[i].size%blk_size)
			blk_req++;
		f[i].length=blk_req;
		while(k<no_of_blks)
		{
			id=arr[k++];
			ptr=search(list,id);
			if(!ptr->status)
				continue;
			ptr->status=0;
			f[i].index=id;
			break;
		}
		if(k!=no_of_blks)
		{
			temp=ptr;
			temp->indices=(int *)calloc(blk_req,sizeof(int));
			k=0;
			while(k<no_of_blks && !flag)
			{
				id=arr[k++];
				ptr=search(list,id);
				if(!ptr->status)
					continue;
				ptr->status=0;
				temp->indices[count++]=id;
				if(count==blk_req)
					flag=1;
			}
		}
		if (!flag)
        	{
            		printf(" Unable to allocate memory for file: %s\n", f[i].name);
            		temp->status=1;
            		f[i].index=-1;
            		for(int j=0;j<count;j++)
			{
				ptr=search(list,temp->indices[j]);
				ptr->status=1;
			}
            		free(temp->indices);
            		temp->indices = NULL;
        	}
	}
	printf("\n\t\tDIRECTORY STRUCTURE\n");
    	printf(" +----------------------+-------------+\n");
    	printf(" |      File Name       | Index Block |\n");
    	printf(" +----------------------+-------------+\n");
    	for (int i = 0; i < no_of_files; i++)
        {
        	if (f[i].index!=-1)
            		printf(" | %-20s |     %-2d      |\n", f[i].name, f[i].index);
	}    
    	printf(" +----------------------+-------------+\n");

    	printf("\n\n");
   	printf(" +----------------------+----------------+\n");
    	printf(" |      File Name       | Blocks Indexed |\n");
    	printf(" +----------------------+----------------+\n");
    	for (int i = 0; i < no_of_files; i++)
    	{
        	if (f[i].index!=-1)
        	{
        		ptr=search(list,f[i].index);
            		for (int j = 0; j < f[i].length; j++)
                		printf(" | %-20s |       %-2d       |\n", ((j > 0) ? "" : f[i].name), ptr->indices[j]);
        	}
        	printf(" |                      |                |\n");
        }
        printf(" +----------------------+----------------+\n");
}
