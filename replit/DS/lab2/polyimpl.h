#include "polyADT.h"
#include<stdlib.h>
#include<math.h>
#include<limits.h>
struct poly * insertEnd(struct poly *p,int c,int e)
{
  struct poly *ptr=p;
  struct poly *temp=(struct poly *)malloc(sizeof(struct poly));
  temp->exp=e,temp->coeff=c,temp->next=NULL;
  if(ptr==NULL)
  {
    p=temp;
  }
  else
  {
    while(ptr->next!=NULL)
    {
      ptr=ptr->next;
    }
    ptr->next=temp;
    temp->next=NULL;
  }
  return p;
}
void disp(struct poly *p)
{
  struct poly *ptr;
  ptr=(struct poly *)malloc(sizeof(struct poly));
  ptr=p;
  while(ptr!=NULL)
  {
    ptr->coeff?printf("%dx^%d + ",ptr->coeff,ptr->exp):printf("0 + ");
    ptr=ptr->next;
  }
  printf("\b\b \b");
  polyDegree(p);
}
struct poly *mul(struct poly *p1,struct poly *p2)
{
  struct poly *ptr1=p1,*ptr2=p2;
  struct poly *p3=NULL;
  while(ptr1!=NULL)
  {
    while(ptr2!=NULL)
    {
      p3=insertEnd(p3,ptr1->coeff*ptr2->coeff,ptr1->exp+ptr2->exp);
      ptr2=ptr2->next;
    }
    ptr2=p2;
    ptr1=ptr1->next;
  }
  return p3;
}
struct poly *add(struct poly *p1,struct poly *p2)
{
  struct poly *ptr1=p1,*ptr2=p2;
  struct poly *R=NULL;
  while(ptr1 && ptr2)
  {
    if(ptr1->exp>ptr2->exp)
    {
      R=insertEnd(R,ptr1->coeff,ptr1->exp);
      ptr1=ptr1->next;
    }
    else if(ptr1->exp<ptr2->exp)
    {
      R=insertEnd(R,ptr2->coeff,ptr2->exp);
      ptr2=ptr2->next;
    }
    else
    {
      R=insertEnd(R,ptr1->coeff+ptr2->coeff,ptr2->exp);
      ptr1=ptr1->next;
      ptr2=ptr2->next;
    }
  }
  while(ptr1||ptr2)
  {
    if(ptr1)
    {
      R=insertEnd(R,ptr1->coeff,ptr1->exp);
      ptr1=ptr1->next;
    }
    if(ptr2)
    {
      R=insertEnd(R,ptr2->coeff,ptr2->exp);
      ptr2=ptr2->next;
    }
  }
  return R;
}
struct poly * simp(struct poly *p)
{
  struct poly *ptr1=p,*ptr2=NULL,*temp=NULL;
  while (ptr1 && ptr1->next)
  {
    ptr2=ptr1;
    while(ptr2->next)
    {
      if (ptr1->exp == ptr2->next->exp) 
      {
        ptr1->coeff=ptr1->coeff+ptr2->next->coeff;
        temp= ptr2->next;
        ptr2->next = ptr2->next->next;
        free(temp);
      }
      else
        ptr2=ptr2->next;
    }
    ptr1=ptr1->next;
  }
  return p;
}
void polyDegree(struct poly *p)
{
  int max=INT_MIN;
  struct poly *ptr=p;
  while(ptr)
  {
    if(max<ptr->exp && ptr->coeff!=0)
    {
      max=ptr->exp;
    }
    ptr=ptr->next;
  }
  if(max!=INT_MIN)
    printf(" , Degree: %d\n",max);
  else
    printf(" , Degree: Undefined\n");
}
int polyEvaluate(struct poly  *p,int x)
{
  int total=0;
  struct poly *ptr=p;
  while(ptr)
  {
    total+=(ptr->coeff*pow(x,ptr->exp));
    ptr=ptr->next;
  }
  return total;
}