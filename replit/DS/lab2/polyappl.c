#include<stdio.h>
#include "polyimpl.h"
int main()
{
  struct poly *p= NULL,*q=NULL;
  struct poly *r=NULL;
  int c,e,n1,n2,ch,x,k=0,ca=0;
  char X;
  do
  {
    if(k)
    {
      printf("\n--------------------------------------\np(x): ");
      disp(p);
      printf("q(x): ");
      disp(q);
      if(ca!=0)
      { 
        printf("r(x): ");
        disp(r);
      }
      printf("\nMenu:\n1.Add 2 polynomials\n2.Multiply 2 polynomials\n3.Evaluate polynomial\n4.Exit%s\n\nEnter your choice: ",k!=0?"\n5.Create 2 new poly":"");
      scanf("%d",&ch);
    }
    else
      ch=5;
    switch(ch)
    {
      case 1: r=add(p,q);
              printf("\nAddition:\nResultant r(x): ");
              disp(r);
              ca=1;
              break;
      case 2: r=mul(p,q);
              printf("\nMultiplication:\nResultant r(x): ");
              disp(r);
              r=simp(r);
              printf("\nSimplified Resultant r(x): ");
              disp(r);
              ca=1;
              break;
      case 3: printf("\nEvaluate polynomial:");
              printf("\nChoose which poly to evaluate(p,q%s): ",ca!=0?",r":"");
              scanf(" %c",&X);
              printf("\nEnter value for x: ");
              scanf("%d",&x);
              int value;
              if(X=='p')
                value=polyEvaluate(p,x);
              else if(X=='q')
                value=polyEvaluate(q,x);
              else if(X=='r')
                value=polyEvaluate(r,x);
              else
              {
                printf("\nInvalid Input!\n");
                break;
              }
              printf("\n%c(%d): %d\n",X,x,value);
              break;
      case 4: return 0;
      case 5: printf("\nHow many terms in poly 1: ");
              scanf("%d",&n1);
              p=NULL;q=NULL;
              for(int i=0;i<n1;i++)
              {
                printf("Enter coeff and exp: ");
                scanf("%d%d",&c,&e);
                p=insertEnd(p,c,e);
              }
              printf("\nEntered p(x): ");
              disp(p);
              printf("\nSimplified p(x): ");
              p=simp(p);
              disp(p);
              printf("\nHow many terms in poly 2: ");
              scanf("%d",&n2);
              for(int i=0;i<n2;i++)
              {
                printf("Enter coeff and exp: ");
                scanf("%d%d",&c,&e);
                q=insertEnd(q,c,e);
              }
              printf("\nEntered q(x): ");
              disp(q);
              printf("\nSimplified q(x): ");
              q=simp(q);
              disp(q);
              ca=0;
              break;
      default: printf("\nInvalid Input!\n");
    }
    k++;
  }while(ch!=4);
  return 0;
}