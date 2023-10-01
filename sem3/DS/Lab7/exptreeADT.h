#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct tree
{
	char c;
	struct tree *left,*right;
};
struct tree* construct(char s[]);
void inorder(struct tree *t);
void preorder(struct tree *t);
void postorder(struct tree *t);
