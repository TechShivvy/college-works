#include<stdio.h>
#include "exptreeimpl.h"
int main()
{
  struct tree *T=(struct tree*)malloc(sizeof(struct tree));
  T=construct("45*6+");
  inorder(T);
  /*printf("\n");
  preorder(T);
  printf("\n");
  postorder(T);*/
}
