#include<stdio.h>
#include<stdlib.h>
struct PQ
{
	int ele[100];
	int size;
	int ctptr;
};
void init(struct PQ *,int);
void display(struct PQ *);
void insert(struct PQ *,int);
int del(struct PQ *);

