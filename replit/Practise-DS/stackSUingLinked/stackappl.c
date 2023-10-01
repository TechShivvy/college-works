#include "stackimpl.h"

int main ()  
{  
    int choice=0;     
    printf("\n*********Stack operations using linked list*********\n");  
    printf("\n----------------------------------------------\n");
    struct stack *s=NULL;  
    while(choice != 4)  
    {  
        printf("\n\nChose one from the below options...\n");  
        printf("\n1.Push\n2.Pop\n3.Show\n4.Exit");  
        printf("\n Enter your choice \n");        
        scanf("%d",&choice);  
        switch(choice)  
        {  
            case 1:  
            {  
                printf("Enter the value");
                int val;  
        scanf("%d",&val);  
                s=push(s,val);  
                break;  
            }  
            case 2:  
            {  
                s=pop(s);  
                break;  
            }  
            case 3:  
            {  
                display(s);  
                break;  
            }  
            case 4:   
            {  
                printf("Exiting....");  
                break;   
            }  
            default:  
            {  
                printf("Please Enter valid choice ");  
            }   
    };  
}  
} 