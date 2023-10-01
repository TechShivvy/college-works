#include "adt.h"
void init(struct PQ *P,int s)
{
	P->size=s;
	P->ctptr=0;
	P->ele[0]=-10;
}
void display(struct PQ *P)
{
	printf("PQ:\n  ");
	for(int i=0;i<=P->ctptr;i++)
	{
		printf("%d  ",P->ele[i]);
	}
	printf("\n");
}
void insert(struct PQ *P,int x)
{
	P->ctptr++;
	P->ele[P->ctptr]=x;
	for(int i=P->ctptr;P->ele[i/2]>x;i=i/2)
	{
		P->ele[i]=P->ele[i/2];
		P->ele[i/2]=x;
	}
}
int del(struct PQ *P)
{
	int min,tmp,child,i;
	min=P->ele[1];
	P->ele[1]=P->ele[P->ctptr--];
	for(int i=1;2*i<=P->ctptr;i=child)
   {         
    child=2*i;
    if(child+1<=P->ctptr&&P->ele[child]>P->ele[child+1])
        child=child+1;
    if(P->ele[child]<P->ele[i])
      {
        tmp=P->ele[i];
        P->ele[i]=P->ele[child];
        P->ele[child]=tmp;
      }
  } 
	return min;
}
