#include "studADT.h"
#include<string.h>
void init(struct studADT *S,int n)
{
	S->max=n;
}
void insert(struct studADT *S)
{	
	//for i<S->max
	//int i=0;
	printf("\nEnter Student details: \n");
	for(int i=0;i<S->max;i++)
	{
		printf("\nEnter Roll No: ");
		scanf("%d",&S->s[i].rno);
		printf("Enter Name:");
		scanf("%s",S->s[i].name);
		printf("Enter mark 1,2 and 3: ");
		scanf("%d%d%d",&(S->s[i].m1),&S->s[i].m2,&S->s[i].m3);	
	}
}
void display(struct studADT S)
{
	printf("\nRecords: \n");
	for(int i=0;i<S.max;i++)
	{
		printf("\nName: %s",S.s[i].name);
		printf("\nRno: %d",S.s[i].rno);
		printf("\nMark 1: %d\nMark 2: %d\nMark 3: %d",S.s[i].m1,S.s[i].m2,S.s[i].m3);
		printf("\nTotal : %d",S.s[i].total);
		printf("\nResult: %c\n",S.s[i].result);
	}
}
void insDet(struct stud *s)
{
	printf("\nNew Student Details: \n");
	printf("Enter Roll No: ");
	scanf("%d",&s->rno);
	printf("Enter Name:");
	scanf("%s",s->name);
	printf("Enter mark 1,2 and 3: ");
	scanf("%d%d%d",&s->m1,&s->m2,&s->m3);
}
void insertFront(struct studADT *S,struct stud *a)
{
	for(int i=S->max;i>=0;i--)
	{
		S->s[i+1]=S->s[i];
	}
	S->s[0]=*a;
	S->max++;
}
void insertEnd(struct studADT *S,struct stud *a)
{
	S->s[S->max]=*a;
	S->max++;
}
void insertRegNo(struct studADT *S,struct stud *a, int regNum)
{	
	int i;
	for(i=0;i<S->max;i++)
	{
		if(S->s[i].rno==regNum)
		{
			//struct stud *temp=NULL;
			S->max++;
			for(int j=S->max;j>i+1;j--)
			{
				S->s[j]=S->s[j-1];
			}
			S->s[i+1]=*a;
			break;
		}
	}
	//S->max++;	
}
struct studADT searchName(struct studADT S,char name[])
{
	struct studADT ptr;
	int count=0;
	ptr.max=1;
	strcpy(ptr.s[0].name,"N/A");
	ptr.s[0].rno=0;
	ptr.s[0].m1=ptr.s[0].m2=ptr.s[0].m3=ptr.s[0].total=0,ptr.s[0].result='X';	
	for(int i=0;i<S.max;i++)
	{
		if(strcmp(S.s[i].name,name)==0)
		{
			ptr.s[ptr.max-1]=S.s[i];
			ptr.max++;
			count=1;
		}
	}
	ptr.max-=count?1:0;
	return ptr;
}
void del(struct studADT *S,int regNum)
{
	for(int i=0;i<S->max;i++)
	{
		if(S->s[i].rno==regNum)
		{
			for(int j=i;j<S->max-1;j++)
			{
				S->s[j]=S->s[j+1];
			}
			S->max--;
			break;
		}
	}
}
void computeResult(struct studADT *S)
{
	for(int i=0;i<S->max;i++)
	{	
		S->s[i].total=S->s[i].m1+S->s[i].m2+S->s[i].m3;
		S->s[i].result=S->s[i].m1>50 && S->s[i].m2>50 && S->s[i].m3>50?'P':'F';
	}	
}
struct studADT listResult(struct studADT S)
{
  struct studADT s;
  s.max=0;
  //rintf("\nmax: %d\n",S.max);
  for(int i=0;i<S.max;i++)
  {
   if(S.s[i].result=='P')
   {
     insertEnd(&s,&S.s[i]);
   }
  }
  return s; 
}
int listClass(struct studADT S)
{
  int count=0;
  for(int i=0;i<S.max;i++)
  {
    if(S.s[i].total>90)
      count++;
  }
  return count;
}
