#include<stdio.h>
#include "impl.h"
int main()
{
  struct node *root=(struct node*)malloc(sizeof(struct node));
  char s[20];
  printf("\nEnter the postorder expression: ");
  scanf("%[^\n]%*c", s);
  
  root=construct(s);
  printf("\nInorder: ");
  inorder(root);
  printf("\nPreorder");
  preorder(root);
  printf("\nPostorder:");
  postorder(root);
  int x=eval(root);
  printf("\nEvaluation: %d\n",x);
}
