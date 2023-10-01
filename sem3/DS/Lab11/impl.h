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
void ls(struct num* N,int x)
{
	for(int i=0;i<N->n;i++)
	{
		if(x==N->A[i])
		{
			printf("\n%d is found at pos: %d\n",x,i+1);
			break;
		}	
	}
}
int ls2(struct num* N,int x)
{
	int count=0;
	for(int i=0;i<N->n;i++)
	{
		if(x==N->A[i])
		{
			//printf("\n%d is found at pos: %d\n",x,i+1);
			//break;
			count++;
		}	
	}
	return count;
}
int ls3(struct num* N,int x)
{
	for(int i=0;i<N->n;i++)
	{
		if(x==N->A[i])
		{
			//printf("\n%d is found at pos: %d\n",x,i+1);
			//break;
			return 1;
		}	
	}
	return 0;
}
int bs(struct num* N,int x)
{
	int low=0,high=N->n-1;
 	while (low <= high)
	{
    		int mid = low + (high - low) / 2;

	        if (N->A[mid] == x)
	      		return mid;

	    	if (N->A[mid] < x)
	      		low = mid + 1;

	    	else
	     		high = mid - 1;
	}

  return -1;
	
}
void disp(struct num* N)
{
	for(int i=0;i<N->n;i++)
	{
		printf("%d ",N->A[i]);
	}	
}
