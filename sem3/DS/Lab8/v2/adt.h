#include<stdio.h>
#include<stdlib.h>
struct wM
{
	char word[30];
	char mean[30];
};
struct AVL
{
	struct wM dict;
	struct AVL *left;
	struct AVL *right;
	int ht;
};
int max(int a, int b);
int height(struct AVL *N);
struct AVL *rightRotate(struct AVL *y);
struct AVL *leftRotate(struct AVL *x);
int getBalance(struct AVL *N);
struct AVL* insert(struct AVL*, struct wM);
