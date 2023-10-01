#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int max(int a,int b)
{
	return a>b?a:b;
}
struct tree
{
	struct tree *left,*right;
	int data;
};
struct tree *insert(struct tree *T,int x)
{
	if(!T)
	{
		T=(struct tree *)malloc(sizeof(struct tree));
		T->data=x;
		T->left=NULL;
		T->right=NULL;	
		return T;
	}
	else if(T->data<x)
		T->right=insert(T->right,x);
	else if(T->data>x)
		T->left=insert(T->left,x);
	return T;	
}
void inorder(struct tree *T)
{
	if(T)
	{
		inorder(T->left);
		printf("%d ",T->data);
		inorder(T->right);
	}
}
void preorder(struct tree *T)
{
	if(T)
	{
		printf("%d ",T->data);
		inorder(T->left);
		inorder(T->right);
	}
}
int height(struct tree *T)
{
	if(!T)
		return -1;
	return max(height(T->left),height(T->right))+1;
}
void print2D(struct tree *T,int space)
{
	if(!T)
		return;
	space+=5;
	print2D(T->right,space);
	printf("\n");
	for(int i=5;i<space;i++)
		printf(" ");
	printf("%d\n",T->data);
	print2D(T->left,space);
}
void printCurLvl(struct tree* T,int lvl)
{
	if(!T)
		return;
	if(lvl==1)
		printf("%d ",T->data);
	printCurLvl(T->left,lvl-1);
	printCurLvl(T->right,lvl-1);
}
void printLvlOrd(struct tree *T)
{
	int ht=height(T)+1;
	for(int i=1;i<=ht;i++)
	{
		printCurLvl(T,i);
		printf("\n");
	}
}
struct tree * findMin(struct tree *T)
{
	if(!T)
		return T;
	while(T->left)
	{
		return findMin(T->left);
	}
	return T;
}
struct tree * del(struct tree *T,int x)
{
	struct tree *temp;
	if(!T)
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
		else if(!T->right)
			T=T->right;
		free(temp);
	}
	return T;
}
int countnodes(struct tree *T)
{
	if(!T)
		return 0;
	return 1+countnodes(T->left)+countnodes(T->right);
}
int comp(struct tree *T,int i,int n)
{
	if(!T)
		return 1;
	if(i>=n)
		return 0;
	return (comp(T->left,2*i+1,n)&&comp(T->right,2*i+2,n));
}
int main()
{
	struct tree *T=NULL;
	T=insert(T,10);
	T=insert(T,69);
	T=insert(T,1);
	//T=insert(T,-1);
	//T=insert(T,2);
	//T=insert(T,9);
	//T=insert(T,6);
	T=insert(T,100);
	T=insert(T,50);
	inorder(T);
	printf("\n");
	preorder(T);
	printf("\n");
	int ht=height(T);
	printf("%d\n",ht);
	printLvlOrd(T);
	printf("\n");
	print2D(T,0);
	printf("\n");
	//del(T,69);
	printf("\n");
	print2D(T,0);
	inorder(T);
	printf("\n%d\n",countnodes(T));
	if(comp(T,0,countnodes(T)))
		printf("yes");
	else
		printf("no");
	return 0;
}
