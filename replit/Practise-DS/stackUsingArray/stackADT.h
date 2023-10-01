struct stack
{
  int max;
  int top;
  int data[100];
};
void init(struct stack *,int);
int isFull(struct stack *);
int isEmpty(struct stack *);
void push(struct stack *,int);
void pop(struct stack *);
void disp(struct stack );
int top(struct stack ); 