#include<stdio.h>
struct tree
{
	int data;
	struct tree *left,*right;
};
struct tree * insert(struct tree*,int);
//void inorder(struct tree *); 
int * inorder(struct tree *,int*);
//int * inorder(struct tree *,int*,int); 
int height(struct tree* T);
void printCurLvl(struct tree* T, int lvl);
void printLvlOrd(struct tree* T);
struct tree * find(struct tree *,int);
struct tree * findMin(struct tree *);
struct tree * del(struct tree *,int); 
int isComplete(struct tree *T);
