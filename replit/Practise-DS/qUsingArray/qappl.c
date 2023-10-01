#include "qimpl.h"
int main()
{
  struct queue Q;
  init(&Q,10);
int choice;   
    while(choice != 4)   
    {     
        printf("\n*************************Main Menu*****************************\n");  
        printf("\n=================================================================\n");  
        printf("\n1.insert an element\n2.Delete an element\n3.Display the queue\n4.Exit\n");  
        printf("\nEnter your choice ?");  
        scanf("%d",&choice);  
        switch(choice)  
        {  
            case 1: 
             printf("Enter the value");
                int val;  
        scanf("%d",&val); 
            inQ(&Q,val);  
            break;  
            case 2:  
            deQ(&Q);  
            break;  
            case 3:  
            display(Q);  
            break;  
            case 4:  
            return 0;  
            break;  
            default:   
            printf("\nEnter valid choice??\n");  
        }  
    }  
}  