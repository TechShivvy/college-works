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
	
		
	struct emp E,E2;//=(struct emp *)malloc(sizeof(struct emp));
	/*printf("Heap:\n");
	E.sal=15000;
	E.id='A';
   	insert(p,E);
   	E.sal=12000;
	E.id='K';
   	insert(p,E);
   	E.sal=4000;
	E.id='R';
   	insert(p,E);
   	E.sal=3500;
	E.id='T';
   	insert(p,E);
   	E.sal=4600;
	E.id='L';
   	insert(p,E);
   	E.sal=6000;
	E.id='P';
   	insert(p,E);
   	E.sal=8600;
	E.id='Y';
   	insert(p,E);*/
   	
   	printf("\nEnter the number of Employees: ");
	int n;
	char id;
	int sal;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		printf("Enter the emp id: ");
		scanf(" %c",&id);
		printf("Enter the salary: ");
		scanf(" %d",&sal);
		E.sal=sal;
		E.id=id;
		insert(p,E);
	}
   	
   	
	display(p);
	printf("Deletion order:\n");
	printf("\n");
	//E2=del(p);
	//int *B=del(p);
	//display(p);
	//printf("%c\t%d\n",E2->id,E2->sal);
	for(int i=0;i<7;i++)
	{
		E2=del(p);	
		printf("%c\t%d\n",E2.id,E2.sal);
	}
	return 0;
}
