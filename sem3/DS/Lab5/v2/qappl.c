#include "qimpl.h"
int main()
{
	struct queue Q,Q1,Q2;
	int i,ch,size;  
	printf("\nEnter size of Q: ");  
	scanf("%d",&size);  
	init(&Q,size); 
	printf("\nMenu:\n\n1.Insert an element\n2.Delete an element\n3.Display the queue\n4.Schedule jobs\n5.Exit\n");
	do  
	{      
		//printf("\n=================================================================\n");  
		//printf("\nMenu:\n\n1.Insert an element\n2.Delete an element\n3.Display the queue\n4.CPU Burst time Q\n5.Exit\n\nEnter your choice:");  
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
			case 4: init(&Q1,20);
				init(&Q2,20);
				int a[]={2,4,8,5,2,7,4,3,6,6},n=10;
				int sum1=0,sum2=0;
				for(i=0;i<n;i++)
				{
					if(isEmpty(&Q1))
					{
						enQ2(&Q1,i+1,a[i]);
						sum1+=a[i];
					}
					else if(isEmpty(&Q2))
					{
						enQ2(&Q2,i+1,a[i]);
						sum2+=a[i];
					}
					else
					{
						if(sum1/(rear(Q1)+1)>sum2/(rear(Q2)+1))
						{
							enQ2(&Q2,i+1,a[i]);
							sum2+=a[i];
						}
						else
						{
							enQ2(&Q1,i+1,a[i]);
							sum1+=a[i];
						}
					}	
				}
				printf("\nScheduling jobs: \n");
				display2(Q1);
				display2(Q2);
				break;
			case 5: printf("\nExiting...\n"); 
				break;
			default:printf("\nInvalid Input!\n");  
		}  
	}while(ch!=5);	
	return 0; 
}
