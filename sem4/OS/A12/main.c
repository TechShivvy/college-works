#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct files
{ 
	char name[25];
}File;

typedef struct directory
{
	char name[25];
	File f[100];
	int fcnt;	
}Dir;

typedef struct master_dir
{
	int dcnt;
	Dir d[100];
}DIR;

void create(DIR *D,char *dname,int f);
void display(DIR D);
void search(DIR D,char *fname);
void single_level();
void two_level();

int main()
{
	int ch;
	do
	{
		printf("\n-----------------File Organization techniques-----------------\n");
		printf("1.Single Level Directory\n2.Two Level Directory\n3.Exit\n");
		printf("\nEnter you choice: ");
		scanf("%d",&ch);
		getchar();
		switch(ch)
		{
			case 1:
				single_level();
				break;
			case 2:
				two_level();
				break;
			case 3:
				printf("\nExiting...\n");
				return 0;
			default:
				printf("\nInvalid Option!\n");
		}
	}while(ch!=3);
	return 0;
}

void single_level()
{
	int ch,size;
	DIR D;
	D.dcnt=0;
	char dname[25],fname[25];
	printf("\n-----------------SINGLE LEVEL-----------------\n");
	//printf("\nEnter name of the directory: ");
	//scanf("%[^\n]s",dname);
	strcpy(dname,"home");
	strcpy(D.d[0].name,dname);
	D.dcnt++;
	do
	{
		printf("\n1.Create a File\n2.List Files\n3.Go Back\n4.Exit\n");
		printf("\nEnter you choice: ");
		scanf("%d",&ch);
		getchar();
		switch(ch)
		{
			case 1:
				create(&D,dname,1);
				break;
			case 2:
				display(D);
				break;
			case 3:
				return;
				break;
			case 4:
				printf("\nExiting...\n");
				exit(0);
				break;	
			default:
				printf("\nInvalid Option!\n");	
		}
	}while(ch!=3&&ch!=4);
}

void two_level()
{
	int ch;
	DIR D;
	D.dcnt=0;
	char dname[25],fname[25];
	printf("\n-----------------TWO LEVEL-----------------\n");
	do
	{
		printf("\n1.Create a Dir\n2.Create a File\n3.Search a file\n4.List Files\n5.Go Back\n6.Exit\n");
		printf("\nEnter you choice: ");
		scanf("%d",&ch);
		getchar();
		switch(ch)
		{
			case 1:
				printf("\nEnter name of the directory: ");
				scanf("%[^\n]s",dname);
				getchar();
				create(&D,dname,0);
				break;
			case 2:
				printf("\nEnter name of the directory: ");
				scanf("%[^\n]s",dname);
				getchar();
				create(&D,dname,1);
				break;
			case 3:
				printf("\nEnter file name: ");
				scanf("%[^\n]s",fname);
				getchar();
				search(D,fname);
				break;
			case 4:
				display(D);
				break;
			case 5:
				return;
				break;
			case 6:
				printf("\nExiting...\n");
				exit(0);
				break;	
			default:
				printf("\nInvalid Option!\n");	
		}
	}while(ch>=1&&ch<=4);
}

void create(DIR *D,char *dname,int f)
{
	char fname[30];
	int d_flag=0,f_flag=0;
	for(int i=0;i<D->dcnt;i++)
	{
		if(strcmp(D->d[i].name,dname)==0)
		{
			d_flag=1;
			if(!f)
				break;
			printf("\nEnter file name: ");
			scanf("%[^\n]s",fname);
			f_flag=0;
			for(int j=0;j<D->d[i].fcnt;j++)
			{
				if(strcmp(D->d[i].f[j].name,fname)==0)
				{
					printf("\nFile Already Existing!\n");
					f_flag=1;
					break;
				}
			}
			if(!f_flag)
			{
				strcpy(D->d[i].f[D->d[i].fcnt++].name,fname);
				printf("\nFile Created!\n");
				break;
			}		
		}
	}
	if(!d_flag && f)
		printf("\nDirectory Not There!\n");
	if(d_flag && !f)
		printf("\nDirectory Already there!\n");	
	if(!d_flag && !f)
		strcpy(D->d[D->dcnt++].name,dname);
}

void display(DIR D)
{
	int j,tot=0;
	printf("\n -----CONTENTS OF DIRECTORIES----- \n");
	printf("\n File Names\t\tPath \n\n");
	for(int i=0;i<D.dcnt;i++)
	{
		//printf("\n%s:\n",D.d[i].name);
		for(int j=0;j<D.d[i].fcnt;j++)
			printf(" %-10s\t\t/%s/%s\n",D.d[i].f[j].name,D.d[i].name,D.d[i].f[j].name);
		tot+=D.d[i].fcnt;
		printf("\n");
	}
	printf(" Total Dirs: %d, Total Files: %d \n",D.dcnt,tot);
	printf(" ---------------------------------\n");
}

void search(DIR D,char *fname)
{
	int flag=0;
	for(int i=0;i<D.dcnt && !flag;i++)
	{
		for(int j=0;j<D.d[i].fcnt;j++)
		{
			if(strcmp(D.d[i].f[j].name,fname)==0)
			{
				flag=1;
				printf("\nFile \"%s\" found in Dir: %s\n",fname,D.d[i].name);
				break;
			}
		}
	}
	if(!flag)
		printf("\nFile Not there!\n");	
}
