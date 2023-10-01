#include "qimpl.h"
int main()
{
	struct queue Q;
	int i,ch,size;  
	printf("\nEnter size of Q: ");  
	scanf("%d",&size);  
	init(&Q,size); 
	printf("\nMenu:\n\n1.Insert an element\n2.Delete an element\n3.Display the queue\n4.Exit\n");
	do  
	{      
		//printf("\n=================================================================\n");  
		//printf("\nMenu:\n\n1.Insert an element\n2.Delete an element\n3.Display the queue\n4.Exit\n\nEnter your choice:");  
		printf("\nEnter your choice:");  
		scanf("%d",&ch);  
		switch(ch)  
		{  
			case 1: printf("Enter the value: ");
				int val;  
				scanf("%d",&val);
				enQ(&Q,val);
				display(Q);  
				break;  
			case 2: printf("\nElement is dequeued! Dequeued element: %d\n",deQ(&Q));
				//display(Q); 
				break;  
			case 3: display(Q);  
				break;  
			case 4: printf("\nExiting...\n"); 
				break;
			default:printf("\nInvalid Input!\n");  
		}  
	}while(ch!=4);
	return 0; 
}
