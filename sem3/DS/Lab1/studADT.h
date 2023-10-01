#include<stdio.h>
struct stud
{
	int rno;
	char name[30];
	int m1,m2,m3;
	int total;
	char result;
};
struct studADT
{
	struct stud s[15];
	int max;
};
void init(struct studADT *S,int n);
void insert(struct studADT *S);
void display(struct studADT S);
void insDet(struct stud *s);
void insertFront(struct studADT *S,struct stud *s);
void insertEnd(struct studADT *S,struct stud *a);
void insertRegNo(struct studADT *S,struct stud *a, int regNum);
struct studADT searchName(struct studADT,char name[]);
void del(struct studADT *S,int regNum);
void computeResult(struct studADT *S);
struct studADT listResult(struct studADT S);
int listClass(struct studADT S);
