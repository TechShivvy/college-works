#include "impl.h"
#include<ctype.h>
int main()
{
	struct AVL *T = NULL;
	struct wM dict[10];
	printf("\nEnter the number of word-meaning pairs: ");
	int n;
	char s1[20],s2[20];
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		printf("Enter the word: ");
		scanf("%s",s1);
		printf("Enter the meaning: ");
		scanf(" %[^\n]%*c", s2);
		strcpy(dict[i].word,s1);
		strcpy(dict[i].mean,s2);
		T=insert(T,dict[i]);
	}
	/*strcpy(dict[0].word,"bisk");
	strcpy(dict[0].mean,"soup");
	strcpy(dict[1].word,"cite");
	strcpy(dict[1].mean,"refer");
	strcpy(dict[2].word,"boom");
	strcpy(dict[2].mean,"sound");
	strcpy(dict[3].word,"able");
	strcpy(dict[3].mean,"opportunity");
	strcpy(dict[4].word,"aged");
	strcpy(dict[4].mean,"old");
	strcpy(dict[5].word,"crew");
	strcpy(dict[5].mean,"group of poeple");*/
	/*T = insert(T, 23);
	T = insert(T, 12);
	T = insert(T, 13);
	T = insert(T, 4);
	T = insert(T, 45);
	T = insert(T, 54);*/
	/*for(int i=0;i<n;i++)
	{
		T=insert(T,dict[i]);
	}*/
	//printf("%d",height(T));
	printf("\nInorder traversal of the constructed AVL"
			" tree is \n");
	//preOrder(T);
	//printf("\n");
	inorder(T);
	/*printf("\n\nLevel Order Traversal:\n");
	printLvlOrd(T);
	printf("AVL TREE:\n");
	print2D(T);
	printf("\n");*/
	char word[30];
	printf("\nEnter word to search for meaning: ");
	scanf("%s",word);
	struct AVL *temp=find(T,word);
	if(temp==NULL)
		printf("\n%s - Word is not in our dict!\n",word);
	else
		printf("%s: %s\n",temp->dict.word,temp->dict.mean);
	return 0;
}
