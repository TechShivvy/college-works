#include "impl.h"
int main()
{
	struct PQ *p=(struct PQ *)malloc(sizeof(struct PQ));
	init(p,20);
	/*insert(P,20);
	insert(P,1);
	insert(P,10);
	insert(P,15);
	insert(P,19);*/
	/*insert(p,14);    
insert(p,16);
insert(p,22);    
insert(p,11);
insert(p,9);      
insert(p,18);
insert(p,10);    
insert(p,7);
insert(p,4);    
insert(p,1);*/

printf("\nEnter the number of elements: ");
	int n,ele;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		printf("Enter the element: ");
		scanf("%d",&ele);
		insert(p,ele);
	}

/*insert(p,'A');
insert(p,'K');    
insert(p,'R');
insert(p,'T');      
insert(p,'L');
insert(p,'P');    
insert(p,'Y');*/

/*insert(p,15000);
insert(p,12000);    
insert(p,4000);
insert(p,3500);      
insert(p,4600);
insert(p,6000);    
insert(p,8600);*/
	display(p);
	printf("\nDeletion:");
	/*int a=del(p);
	int b=del(p);
	display(p);
	printf("a= %d,b= %d\n",a,b);*/
	
	int b;
	for(int i=0;i<2;i++)
	{
		b=del(p);
		display(p);
	printf("%d\n",b);
	}
	return 0;
}
