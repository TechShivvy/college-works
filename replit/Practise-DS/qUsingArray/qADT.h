struct queue
{
  int max;
  int front,rear;
  int data[100];
};
void init(struct queue *,int);
int isFull(struct queue *);
int isEmpty(struct queue *);
void inQ(struct queue *,int);
void deQ(struct queue *);
void display(struct queue);