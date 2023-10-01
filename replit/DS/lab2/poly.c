#include<stdio.h>
#include<stdlib.h>
struct poly
{
  int coeff;
  int exp;
};  
struct node
{
  struct poly P;
  struct node *next;
};
void insertFront(struct node*,struct poly);
void disp(struct node *);
struct node * addpoly(struct node *,struct node *,struct node *);
int main()
{
  struct poly p;
  p.exp=4;p.coeff=24;
  struct node llp;
  struct poly q;
  q.exp=5;q.coeff=-3;
  struct node llq;
  insertFront(&llp,p);
  insertFront(&llq,q);
  struct node R;
  addpoly(&llp,&llq,&R);
  disp(&R);
  return 0;
}
void insertFront(struct node *header,struct poly P1)
{
  struct node *temp;
  temp=(struct node *)malloc(sizeof(struct node));
  temp->P=P1;
  temp->next=header->next;
  header->next=temp;
}
struct node * addpoly(struct node *p,struct node *q,struct node *R)
{
  struct node *ptr1=p->next,*ptr2=q->next,*temp=NULL;
  while(ptr1!=NULL && ptr2!=NULL)
  {
    if(ptr1->P.exp>ptr2->P.exp)
    {
      temp->P=ptr1->P;
      temp->next=R->next;
      R->next=temp;
      ptr1=ptr1->next;
    }
    else if(ptr1->P.exp==ptr2->P.exp)
    {
      temp->P.coeff=ptr1->P.coeff+ptr2->P.coeff;
      temp->next=R->next;
      R->next=temp;
      ptr1=ptr1->next;
      ptr2=ptr2->next;
    }
    else
    {
      temp->P=ptr2->P;
      temp->next=R->next;
      R->next=temp;
      ptr2=ptr2->next;
    }
    if(ptr1==NULL)
    {
      while(ptr2!=NULL)
      {
        temp->P=ptr2->P;
        temp->next=R->next;
        R->next=temp;
        ptr2=ptr2->next;
      }
    }
    else
    {
      while(ptr1!=NULL)
      {
      temp->P=ptr1->P;
      temp->next=R->next;
      R->next=temp;
      ptr1=ptr1->next;
      }
    }
  }
  return R;
}
void disp(struct node *header)
{
  struct node *ptr;
  ptr=header->next;
  while(ptr!=NULL)
  {
    printf("%dx^%d+",ptr->P.coeff,ptr->P.exp);
    ptr=ptr->next;
  }
}