struct queue
{
  int max;
  int f,r;
  int data[100];
  int J[100];
  int T[100];
};
void init(struct queue *,int);
int isFull(struct queue *);
int isEmpty(struct queue *);
void enQ(struct queue *,int);
void enQ2(struct queue *,int,int);
int deQ(struct queue *);
void display(struct queue);
void display2(struct queue);
