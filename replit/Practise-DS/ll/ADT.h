struct node
{
  int data;
  struct node *next;
}
struct node * pop(struct node *);
struct node * insertFront(struct node *,int);
struct node * insertEnd(struct node *,int);
void disp(struct node*);