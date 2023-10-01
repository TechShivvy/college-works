struct queue
{
  int max;
  int f,r;
  int data[100];
};
void init(struct queue *,int);
int isF(struct queue *);
int isE(struct queue *);
void enQ(struct queue *,int);
int deQ(struct queue *);
void disp(struct queue);
