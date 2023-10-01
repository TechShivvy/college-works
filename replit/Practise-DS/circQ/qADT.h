struct queue
{
  int max;
  int f,r;
  int data[100];
};
void init(struct queue *,int);
int isFull(struct queue *);
int isEmpty(struct queue *);
void inQ(struct queue *,int);
int deQ(struct queue *);
void display(struct queue);