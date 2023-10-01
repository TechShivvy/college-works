#include<stdio.h>
#include "dlimpl.h"
int main()
{
  struct node *L=NULL;
  int ch;
	char c;
	printf("\n\nMenu:\n1.Insert At Front\n2.Insert At End\n3.Insert in Middle\n4.Display List\n5.Delete first occurance\n6.Count the occurances\n7.Check whether palindrome\n8.Seperate into Consonants and Vowels\n9.Swap kth Node\n10.Exit");
	do
	{
		//printf("\n\nMenu:\n1.Insert At Front\n2.Insert At End\n3.Insert in Middle\n4.Display List\n5.Delete first occurance\n6.Count the occurances\n7.Check whether palindrome\n8.Seperate into Consonants and Vowels\n9.Swap kth Node\n10.Exit\nEnter your choice: ");
		printf("\n\nEnter your choice: ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: printf("\nEnter a char: ");
				      scanf(" %c",&c);
				      L=insertFront(L,c);
             			 displayItems(L);
				      break;
			case 2: printf("\nEnter a char: ");
              scanf(" %c",&c);
              L=insertEnd(L,c);
              displayItems(L);
              break;
			case 3: printf("\nEnter the char after which it needs to be inserted: ");
              char d;
              scanf(" %c",&d);
              printf("Enter a char: ");
              scanf(" %c",&c);
              L=insertMiddle(L,d,c);
              displayItems(L);
              break;
			case 4: displayItems(L);
				      break;
			case 5: printf("\nEnter a char to delete: ");
              scanf(" %c",&c);
              L=deleteItem(L,c);
              displayItems(L);
              break;
			case 6: printf("\nEnter a char:");
              scanf(" %c",&c);
              int count=searchItem(L,c);
              displayItems(L); 
  	          printf("\nCount of %c: %d\n",c,count);
              break;
			case 7: ;
              int isP=palindrome(L);
              displayItems(L);
	            if(isP==1)
		            printf("\nIt is a Palindrome!\n");
	            else if(isP==0)
		            printf("\nIt is not a Palindrome!\n");
              break;
			case 8: ;struct node *C=NULL,*V=NULL;
  	          seperation(L,&C,&V);
              displayItems(L);
              printf("\n\nConst:\n");
              displayItems(C);
              printf("\n\nVowels:\n");
              displayItems(V);
              break;  
			case 9: printf("\nEnter value of k: ");
              int k;
              scanf("%d",&k);
              int n=total(L);
              if(k==1||k==n)
                L=swapfl(L);
              else
                swapk(L,k,n);
              displayItems(L);
              break;
			case 10:break;
			default:printf("\nInvalid Input!\n");
		}
	}while(ch!=10);
	/*displayItems(L);
  	L=insertMiddle(L,'a','e');
displayItems(L);
  	L=insertEnd(L,'5');
displayItems(L);
  	L=insertFront(L,'a');
displayItems(L);
  	//printf("%c",L->c);
  	L=insertFront(L,'z');
displayItems(L);
  	L=insertEnd(L,'x');
displayItems(L);
  	L=insertMiddle(L,'5','E');
displayItems(L);
  	L=insertMiddle(L,'5','e');
displayItems(L);
  	L=insertMiddle(L,'Z','e');
displayItems(L);
  	L=insertMiddle(L,'Z','W');
displayItems(L);
  	//printf("%c",L->c);
  	//displayItems(L);
  	L=insertFront(L,'U');
displayItems(L);
  	L=insertEnd(L,'C');
displayItems(L);
  	L=insertFront(L,'g');
displayItems(L);
  	L=deleteItem(L,'z');
displayItems(L);
  	L=deleteItem(L,'5');
displayItems(L);
  	L=deleteItem(L,'W');
displayItems(L);
  	displayItems(L);
  	struct node *C=NULL,*V=NULL;
  	seperation(L,&C,&V);
  	printf("\n\nConst:\n");
  	displayItems(C);
  	printf("\n\nVowels:\n");
  	displayItems(V);
  	int count=searchItem(L,'p');
  	printf("\nCount of %c: %d\n",'p',count);
	L=insertFront(L,'m');
	L=insertFront(L,'A');
	L=insertFront(L,'m');
displayItems(L);
	int isP=palindrome(L);
	if(isP==1)
		printf("\nIt is a Palindrome!\n");
	else if(isP==0)
		printf("\nIt is not a Palindrome!\n");*/
  	return 0;
}
