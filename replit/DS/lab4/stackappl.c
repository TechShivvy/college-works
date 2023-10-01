#include "stackimpl.h"
int main()
{
  struct stack s;
  initstack(&s,10);
  push(&s,4);
  push(&s,10);
  push(&s,5);
  display(s);
  pop(&s);
  display(s);
}//gcc lab4/stackappl.c