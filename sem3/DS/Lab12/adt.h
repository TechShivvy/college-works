#include<stdio.h>
struct num
{
	int A[100];
	int n;
};
void disp(struct num*);
void init(struct num*,int );
void ins(struct num*,int[]);
void selSort(struct num*);
void shellSort(struct num*);
