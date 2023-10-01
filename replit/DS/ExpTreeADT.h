struct node 
{
  char c;
  struct node *left,*right;
};
struct stack
{
  struct node *s[30];
  int size,top;
};
