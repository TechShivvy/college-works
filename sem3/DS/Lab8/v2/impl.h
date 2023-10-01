#include "adt.h"
//#include<malloc.h>
#include<string.h>
#define COUNT 10
int height(struct AVL* N)
{
	if (N == NULL)
		return -1;
	return N->ht;
}
int max(int a, int b)
{
	return (a > b)? a : b;
}
/*struct AVL* newNode(int key)
{
	struct AVL* node = (struct Node*)malloc(sizeof(struct Node));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 0; 
	return(node);
}*/
struct AVL *rightRotate(struct AVL *y)
{
	struct AVL *x = y->left;
	struct AVL *T2 = x->right;


	x->right = y;
	y->left = T2;


	y->ht = max(height(y->left), height(y->right))+1;
	x->ht = max(height(x->left), height(x->right))+1;


	return x;
}

struct AVL *leftRotate(struct AVL *x)
{
	struct AVL *y = x->right;
	struct AVL *T2 = y->left;


	y->left = x;
	x->right = T2;

	x->ht = max(height(x->left), height(x->right))+1;
	y->ht = max(height(y->left), height(y->right))+1;


	return y;
}


int getBalance(struct AVL *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

struct AVL* insert(struct AVL* T, struct wM W)
{
	if (T== NULL)
	{	
	  T= (struct AVL*)malloc(sizeof(struct AVL));
	T->dict = W;
	T->left = NULL;
	T->right = NULL;
	T->ht = 0; 
	return(T);
	}
	if ( strcmp(W.word,T->dict.word)<0)
		T->left = insert(T->left, W);
	else if (strcmp(W.word,T->dict.word)>0)
		T->right = insert(T->right, W);
	else
		return T;

	
	T->ht = 1+ max(height(T->left),height(T->right));

	int bal = getBalance(T);



	// Left Left Case
	if (bal > 1 && strcmp(W.word,T->dict.word)<0)
		return rightRotate(T);

	// Right Right Case
	if (bal < -1 && strcmp(W.word,T->dict.word)>0)
		return leftRotate(T);

	// Left Right Case
	if (bal > 1 && strcmp(W.word,T->dict.word)>0)
	{
		T->left = leftRotate(T->left);
		return rightRotate(T);
	}

	// Right Left Case
	if (bal < -1 && strcmp(W.word,T->dict.word)<0)
	{
		T->right = rightRotate(T->right);
		return leftRotate(T);
	}
	return T;
}

struct AVL* find(struct AVL *T,char s[])
{
	if(!T||strcmp(T->dict.word,s)==0)
		return T;
	else if(strcmp(T->dict.word,s)> 0)
		return find(T->left,s);
	return find(T->right,s);
}

void preOrder(struct AVL *root)
{
	if(root != NULL)
	{
		printf("%s: %s\n",root->dict.word,root->dict.mean);
		preOrder(root->left);
		preOrder(root->right);
	}
}
void inorder(struct AVL *T)
{
	if(T)
	{
		inorder(T->left);
		printf("%s: %s\n",T->dict.word,T->dict.mean);
		inorder(T->right);
	}
}

void printCurLvl(struct AVL* T, int lvl)
{
    if(T==NULL)
        return;
    if(lvl==1)
        printf("%s: %s\n",T->dict.word,T->dict.mean);
    else if(lvl>1) {
        printCurLvl(T->left,lvl-1);
        //printf("\n");
        printCurLvl(T->right,lvl-1);
        //printf("\n");
    }
}
void printLvlOrd(struct AVL* T)
{
    int h=height(T)+1;
    for(int i=1;i<=h;i++)
   {
        printCurLvl(T,i);
   	printf("\n");
   }	
    printf("\n"); 
}

void print2DUtil(struct AVL *root, int space)
{
 
    if (root == NULL)
        return;

    space += COUNT;

    print2DUtil(root->right, space);
 
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%s: %s\n",root->dict.word,root->dict.mean);
 
    print2DUtil(root->left, space);
}
 

void print2D(struct AVL *root)
{

   print2DUtil(root, 0);
}

