#include<stdio.h>
#include<stdlib.h>
struct AVL
{
	int key;
	struct AVL *left;
	struct AVL *right;
	int ht;
};
int max(int a, int b);
int height(struct AVL *N);
struct AVL *rightRotate(struct AVL *y);
struct AVL *leftRotate(struct AVL *x);
int getBalance(struct AVL *N);
struct AVL* insert(struct AVL*, int key);
