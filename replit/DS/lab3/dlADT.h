struct node
{
  char c;
  struct node *next;
  struct node *prev;
};
struct node * insertFront(struct node *L, char c);
struct node * insertEnd(struct node *L, char c);
struct node * insertMiddle(struct node *L, char c, char d);
void displayItems(struct node *L);
struct node * deleteItem(struct node *L, char c);
void seperation(struct node *,struct node **C,struct node **V);
int searchItem(struct node*, char c);
int palindrome(struct node *header);
struct node * swapfl(struct node *header);
void swapk(struct node *header,int k,int count);