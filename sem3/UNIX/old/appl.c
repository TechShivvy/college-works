#include "impl.h"

int main()
{
	
	printf("Enter the maximum number of elements in each Queue : ");
  int n;
	scanf(" %d",&n);
	printf("%dhellloooooo",n);
  struct CQ q1;
	struct CQ q2;	init(&q1,n);
	init(&q2,n);
	

  
	printf("start of enqueing");
	enqueue(&q1,&q2,"J1",2);
	printf("after first enque");
    enqueue(&q1,&q2,"J2",4);
    enqueue(&q1,&q2,"J3",8);
    enqueue(&q1,&q2,"J4",5);
    enqueue(&q1,&q2,"J5",2);
    enqueue(&q1,&q2,"J6",7);
    enqueue(&q1,&q2,"J7",4);
    enqueue(&q1,&q2,"J8",3);
    enqueue(&q1,&q2,"J9",6);
    enqueue(&q1,&q2,"J10",6);
    
    display(&q1);
    printf("\n");
    display(&q2);
	
    return 0;	
}
