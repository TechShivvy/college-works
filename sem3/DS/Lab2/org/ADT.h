#include<stdio.h>
struct poly
{
  int coeff;
  int exp;
  struct poly *next;
};
struct poly * insertEnd(struct poly *p,int c,int e);
void disp(struct poly *p);
struct poly *mul(struct poly *p1,struct poly *p2);
struct poly *add(struct poly *p1,struct poly *p2);
struct poly * simp(struct poly *p);
void polyDegree(struct poly *p);
int polyEvaluate(struct poly  *p,int x);
