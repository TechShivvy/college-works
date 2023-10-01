#include<stdio.h>
#include<stdlib.h>
struct emp
{
	char id;
	int sal;
};
struct PQ
{
	struct emp E[100];
	int size;
	int ctptr;
};
void init(struct PQ *,int);
void display(struct PQ *);
void insert(struct PQ *,struct emp);
struct emp del(struct PQ *);

