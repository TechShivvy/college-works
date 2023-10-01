#include "stackimpl.h"
struct tree* construct(char s[])
{
  struct stack *sta=(struct stack*)malloc(sizeof(struct stack));
  initstack(sta,30);
  struct tree *tmp=(struct tree*)malloc(sizeof(struct tree));
  tmp->right=NULL;
  tmp->left=NULL;
  for(int i=0;i<strlen(s);i++)
  {
    //tmp=(struct tree*)malloc(sizeof(struct tree));
    tmp->c=s[i];
   	 if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/')
    {
       tmp->right=pop(sta);
       tmp->left=pop(sta);
    }
    sta=push(sta,tmp);
  }
  return pop(sta);
}
void inorder(struct tree *T)
{
  if(T==NULL)
   {
     printf("\nEmpty!!!");
     return;
   }
  if(T->left!=NULL)
     inorder(T->left);
   printf(" %c",T->c);
  if(T->right!=NULL)
     inorder(T->right);
}
void preorder(struct tree *T)
{
  if(T==NULL)
   {
     printf("\nEmpty!!!");
     return;
   }
  printf(" %c",T->c); 
  if(T->left!=NULL)
     preorder(T->left);
  if(T->right!=NULL)
     preorder(T->right);
}
void postorder(struct tree *T)
{
  if(T==NULL)
   {
     printf("\nEmpty!!!");
     return;
   } 
  if(T->left!=NULL)
     postorder(T->left);
  if(T->right!=NULL)
     postorder(T->right);
  printf(" %c",T->c);   
}
