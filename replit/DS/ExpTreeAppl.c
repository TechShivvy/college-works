#include<stdio.h>
#include "ExpTreeImpl.h"
int main()
{
  struct node *root=NULL;
  root=construct("45*6+");
  inorder(root);
  printf("\n");
  preorder(root);
  printf("\n");
  postorder(root);
}