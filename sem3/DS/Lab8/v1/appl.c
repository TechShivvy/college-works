#include "impl.h"
int main()
{
	struct AVL *T = NULL;
	printf("\nEnter the number of elements: ");
	int n,ele;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		printf("Enter the element: ");
		scanf("%d",&ele);
		T=insert(T,ele);
	}
	/*T = insert(T, 23);
	T = insert(T, 12);
	T = insert(T, 13);
	T = insert(T, 4);
	T = insert(T, 45);
	T = insert(T, 54);*/
	//printf("%d",height(T));
	printf("\nInorder traversal of the constructed AVL"
			" tree is \n");
	//preOrder(T);
	//printf("\n");
	inorder(T);
	printf("\n\nLevel Order Traversal:\n");
	printLvlOrd(T);
	printf("AVL TREE:\n");
	print2D(T);
	printf("\n");
	return 0;
}
