#include "impl.h"
#include<stdlib.h>
int main()
{
	 int ch;
	 struct num *N=(struct num*)malloc(sizeof(struct num));
	 printf("\nMenu:\n1.Create an array\n2.Display the array\n3.Selection sort\n4.Shell Sort\n5.Exit\n");
	 do
	 {
	 	printf("\nChoice: ");
	 	scanf("%d",&ch);
	 	switch(ch)
	 	{
	 		case 1:  printf("\nEnter the number of elements: ");
	 			 int n,A[20];//={49,29,2,5,11,8,63,72,83};
				 scanf("%d",&n);
				 for(int i=0;i<n;i++)
				 {
				 	printf("Enter the element: ");
				 	scanf("%d",&A[i]);
				 }
				 init(N,n);//sizeof(A)/sizeof(A[0]));
				 ins(N,A);
	 			break;
	 		case 2:
	 			 printf("\nArray:\n");
				 disp(N);
	 			break;
	 		case 3:
	 			 printf("\n\nSelection Sort:\n");
				 selSort(N);
				 disp(N);
				 ins(N,A);
	 			break;
	 		case 4:
	 			 printf("\n\nShell Sort:\n");
				 shellSort(N);
				 disp(N);
				 ins(N,A);
	 			break;
	 		case 5:printf("\nExiting...\n");
	 			break;
	 		default:printf("\nInavlid Input!\n");
	 	}
	 }while(ch!=5);
	
	
	
	 printf("\n");
}
