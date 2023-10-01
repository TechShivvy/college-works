struct jobs
{
	char *jobnum;
	int time;
};

struct CQ
{
	struct jobs job[100];
	int f,r,size,iter;
};

void init(struct CQ *q, int s);
void enqueue(struct CQ *q1, struct CQ *q2, char *jnum, int t);
int isFull(struct CQ *Q);
int isEmpty(struct CQ *q);
void dequeue(struct CQ *q);
void display(struct CQ *q);
