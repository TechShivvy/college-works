struct stack
{
  int data;
  struct stack *next;
};
struct stack * pop(struct stack *);
struct stack * push(struct stack *,int);
void disp(struct stack*);