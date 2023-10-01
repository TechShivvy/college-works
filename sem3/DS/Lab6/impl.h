#include "adt.h"
#include<stdlib.h>

struct tree * insert(struct tree *T,int ele)
{
	if(T==NULL)
	{
		T=(struct tree *)malloc(sizeof(struct tree *));
		T->data=ele;
		T->left=NULL;
		T->right=NULL;
	}
	else
	{
		if(T->data>ele)
			T->left=insert(T->left,ele);
		if(T->data<ele)
			T->right=insert(T->right,ele);
	}
	return T;
}
/*void inorder(struct tree *T)
{
	if(T)
	{
		inorder(T->left);
		printf("%d ",T->data);
		inorder(T->right);
	}
}*/

int * inorder(struct tree *T,int *A)
{
	//static int *A=NULL;
	if(T)
	{
		A=inorder(T->left,A);
		//printf("%d ",T->data);
		if(A==NULL)
		{
			A=(int *)malloc(sizeof(int));
		}
		*A++=T->data;
		//printf("\n%d\n",*A);
		A=inorder(T->right,A);
	}
	return A;
}	
	/*static int *A=NULL;
	static int i=1;
	if(T)
	{
		inorder(T->left);
		//printf("%d ",T->data);
		if(A==NULL)
		{
			A=(int *)malloc(sizeof(int));
			A[0]=0;
		}
		A[i]=T->data;
		A[0]=A[0]+1;
		i++;
		//printf("\n%d\n",*A);
		inorder(T->right);
	}
	return A;
}
int * inorder(struct tree *T,int *A,int i)
{
	//static int A[5],i=0;
	if(T)
	{
		inorder(T->left,A,i);
		//printf("%d ",T->data);
		A[i++]=T->data;
		//printf("\n%d\n",*A);
		inorder(T->right,A,i);
	}
	return A;
}*/
int height(struct tree* T)
{
    if(T==NULL)
        return 0;
    else 
    {
        int lheight = height(T->left);
        int rheight = height(T->right);
        if (lheight>rheight)
            return lheight+1;
        else
            return rheight+1;
    }
}
void printCurLvl(struct tree* T, int lvl)
{
    if(T==NULL)
        return;
    if(lvl==1)
        printf("%d ", T->data);
    else if(lvl>1) {
        printCurLvl(T->left,lvl-1);
        printCurLvl(T->right,lvl-1);
    }
}
void printLvlOrd(struct tree* T)
{
    int h=height(T);
    for(int i=1;i<=h;i++)
    {    printCurLvl(T,i);	
    printf("\n"); }
}
struct tree* find(struct tree *T,int x)
{
	if(!T||x==T->data)
		return T;
	else if(x<T->data)
		return find(T->left,x);
	return find(T->right,x);
}
struct tree * findMin(struct tree *T)
{
	if(!T)
		return T;
	while(T->left!=NULL)
		return findMin(T->left);
	return T;
}
struct tree * del(struct tree *T,int x) 
{
	struct tree *temp;
	if(T==NULL)
		return T;
	if(x<T->data)
		T->left=del(T->left,x);
	else if(x>T->data)
		T->right=del(T->right,x);
	else if(T->left && T->right)
	{
		temp=findMin(T->right);
		T->data=temp->data;
		T->right=del(T->right,T->data);
	}
	else
	{
		temp=T;
		if(!T->right)
			T=T->left;
		else if(!T->left)
			T=T->right;
		free(temp);
		/* if (T->left == NULL) {
            temp = T->right;
            free(T);
            return temp;
        }
        else if (T->right == NULL) {
            temp = T->left;
            free(T);
            return temp;
	}*/
	}
	return T;
}
int isComplete(struct tree *T)
{
    struct tree *ptr = T;
    if (ptr->left && ptr->right)
    {
        if (isComplete(ptr->left) == 1 && isComplete(ptr->right) == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (ptr->left == NULL && ptr->right == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


