#include "adt.h"
void init(struct num* N,int n)
{
	N->n=n;
}
void ins(struct num* N, int x[])
{
	for(int i=0;i<N->n;i++)
	{
		N->A[i]=x[i];
	}
}
void disp(struct num* N)
{
	for(int i=0;i<N->n;i++)
	{
		printf("%d ",N->A[i]);
	}	
}
void selSort(struct num *N)
{
	int temp,min_i;
	for(int i=0;i<N->n-1;i++)
	{
		min_i=i;
		for(int j=i;j<N->n;j++)
		{
			if(N->A[j]<N->A[min_i])
				min_i=j;
		}
		temp=N->A[i];
		N->A[i]=N->A[min_i];
		N->A[min_i]=temp;
	}
}
void shellSort(struct num *N)
{
	for(int gap=N->n/2;gap>0;gap/=2)
	{
		for(int i=gap;i<N->n;i++)
		{
			for(int j=i-gap;j>=0;j-=gap)
			{
				if(N->A[j+gap]>N->A[j])
					break;
				else
				{
					int temp=N->A[j+gap];
					N->A[j+gap]=N->A[j];
					N->A[j]=temp;
				}
			}
		}
	}
}
