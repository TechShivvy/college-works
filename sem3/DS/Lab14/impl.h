#include "adt.h"
void init(struct hash* h,int n)
{
	h->size = n;
	for(int i=0;i<n;i++)
	{
		h->arr[i]=0;
	}
}
void insert(struct hash *h,int x)
{
	int probes=0;
	int si = x%(h->size);
	int idx=si;
	do{
		if(!h->arr[si]){
			h->arr[si]=x;
			break;
		}
		else{
			si = (si+1)%(h->size);
			probes++;
		}
	}while(idx!=si);
	//printf("probes:%d\n",probes);
	printf("probes for element %d : %d\n",x,probes);
}

void display(struct hash *h)
{
	for(int i=0;i<h->size;i++)
	{
		if(h->arr[i]!=0)
			printf("%d->%d\n",i,h->arr[i]);
		else
			printf("%d->\n",i);
	}
}
void find(struct hash *h,int x)
{
	int probes=0;
	int si = x%(h->size);
	int idx=si;
	do{
		if(h->arr[si]==x){
			printf("Element %d found at index : %d\t",x,si);
			break;
		}
		else{
			si = (si+1)%(h->size);
			probes++;
		}
	}while(idx!=si);

	printf("probes : %d\n",probes);
}
int find1(struct hash *h,int x)
{
	int probes=0;
	int si = x%(h->size);
	int idx=si;
	do{
		if(h->arr[si]==x){
			//printf("Element %d found at index:%d\n",x,si);
			return x;
			//break;
		}
		else{
			si = (si+1)%(h->size);
			probes++;
		}
	}while(idx!=si);

	//printf("probes:%d\n",probes);
	return 0;
}

