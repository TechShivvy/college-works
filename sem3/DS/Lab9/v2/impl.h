#include "adt.h"
void init(struct PQ *P,int s)
{
	P->size=s;
	P->ctptr=0;
	P->E[0].sal=-10;
	P->E[0].id='\0';
}
void display(struct PQ *P)
{
	printf("\nID\tSalary\n");
	for(int i=1;i<=P->ctptr;i++)
	{
		printf("%c\t%d\n",P->E[i].id,P->E[i].sal);
	}
	printf("\n");
}
void insert(struct PQ *P,struct emp E)
{
	P->ctptr++;
	P->E[P->ctptr]=E;
	//P->E[P->ctptr].id=E.id;
	for(int i=P->ctptr;P->E[i/2].sal>E.sal;i=i/2)
	{
		P->E[i]=P->E[i/2];
		P->E[i/2]=E;
		//P->E[i]=P->E[i/2];
		//P->E[i/2].id=E.id;
	}
}
struct emp  del(struct PQ *P)
{
	/*int child,i,t;
	char t2;
	struct emp *E=(struct emp*)malloc(sizeof(struct emp));
	E->sal=P->E[1].sal;
	E->id=P->E[1].id;
	P->E[1].sal=P->E[P->ctptr].sal;
	P->E[1].id=P->E[P->ctptr--].id;
	for(i=i;2*i<=P->ctptr;i=child)
	{
		child=2*i;
		if(P->E[child].sal<P->E[i].sal || P->E[child+1].sal<P->E[i].sal)
		{
			if(P->E[child+1].sal<P->E[child].sal)
				child++;
		}
		if(P->E[i].sal>P->E[child].sal)
		{
			t=P->E[i].sal;
			t2=P->E[i].id;
			P->E[i].sal=P->E[child].sal;
			P->E[i].id=P->E[child].id;
			P->E[child].sal=t;
			P->E[child].id=t2;
		}
	}
	//printf("\nhere\n");
	return E;*/
	
	 int child;
  struct emp tmp,ele=P->E[1];
  P->E[1]=P->E[P->ctptr--];
  for(int i=1;2*i<=P->ctptr;i*=2)
   {         
    child=2*i;
    if(P->E[2*i].sal>P->E[2*i+1].sal)
        child=2*i+1;
    if(P->E[child].sal<P->E[i].sal)
      {
        tmp=P->E[i];
        P->E[i]=P->E[child];
        P->E[child]=tmp;
      }
  } 
  return ele;
}
