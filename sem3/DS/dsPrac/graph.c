#include<stdio.h>
#include<stdlib.h>
struct stack 
{
	int data[10];
	int top,size;
};
struct Q
{
	int data[100];
	int f,r,size;
};
void sInit(struct stack *s,int size)
{
	s->top=-1;
	s->size=size;
} 
void qInit(struct Q *q,int size)
{
	q->f=q->r=-1;
	q->size=size;
} 
int sIsFull(struct stack *s)
{
	return s->top==s->size-1;
}
int sIsEmpty(struct stack *s)
{
	return s->top==-1;
}
void push(struct stack *s,int x)
{
	if(sIsFull(s))
		return;
	s->data[++s->top]=x;
}
int pop(struct stack *s)
{
	if(sIsEmpty(s))
		return -1;
	return s->data[s->top--];
}

int qIsFull(struct Q *q)
{
	return (q->r+1)%q->size==q->f;
}
int qIsEmpty(struct Q *q)
{
	return q->f==-1&&q->r==-1;
}
void enQ(struct Q *q,int x)
{
	if(qIsFull(q))
		return;
	else if(qIsEmpty(q))
		q->f=q->r=0;
	else
		q->r=(q->r+1)%q->size;
	q->data[q->r]=x;
}
int deQ(struct Q *q)
{
	int ele=q->data[q->f];
	if(qIsEmpty(q))
		return -1;
	else if(q->f==q->r)
		q->f=q->r=-1;
	else
		q->f=(q->f+1)%q->size;
	return ele;
}
int peek(struct stack *s)
{
	if(sIsEmpty(s))
		return -1;
	return s->data[s->top];
}
struct graph
{
	int adj[10][10];
	int v,e;
	int vis[10];
	struct Q q;
	struct stack s;
};
void vqs(struct graph *g)
{
	for(int i=0;i<10;i++)
	{
		g->vis[i]=0;
	}
	while(!qIsEmpty(&g->q))
	{
		deQ(&g->q);
	}
	while(!sIsEmpty(&g->s))
	{
		pop(&g->s);
	}
}
void create(struct graph *g,int v,int e)
{
	g->v=v;
	g->e=e;
	for(int i=0;i<v;i++)
	{
		for(int j=0;j<v;j++)
		{
			g->adj[i][j]=0;
		}
	}
	char edge[2];
	for(int i=0;i<e;i++)
	{
		printf("Enter edge: ");
		scanf("%s",edge);
		g->adj[edge[0]-'1'][edge[1]-'1']=1;
	
	}
	sInit(&g->s,10);
	qInit(&g->q,10);
	vqs(g);
}
void BFS(struct graph *g,int V)
{
	g->vis[V]=1;
	enQ(&g->q,V);
	while(!qIsEmpty(&g->q))
	{
		int cur_vtx=deQ(&g->q);
		printf("%d", cur_vtx);
		for(int i=0;i<g->v;i++)
		{
			if(g->adj[cur_vtx][i])
			{
				if(g->vis[i]==0)
				{
					enQ(&g->q,i);
					g->vis[i]=1;
				}
			}
		}
	}
}
void DFS(struct graph *g,int V)
{
	int i=0;
	g->vis[V]=1;
	push(&g->s,V);
	printf("%d", V);
	while(!sIsEmpty(&g->s))
	{
		int cur_vtx=peek(&g->s);
		for(i=0;i<g->v;i++)
		{
			if(g->adj[cur_vtx][i])
			{
				if(g->vis[i]==0)
				{
					push(&g->s,i);
					g->vis[i]=1;
					printf("%d", i);
					break;
				}
			}
		}
		if(i==g->v)
			pop(&g->s);
	}
}
int main()
{
	struct graph *G=(struct graph*)malloc(sizeof(struct graph));
	int v,e;
	printf("Enter the number of verties and edges: ");
	scanf("%d%d",&v,&e);
	create(G,v,e);
	printf("\nBFS:\n");
	
	for(int i=0;i<G->v;i++)
	{
		if(G->vis[i]==0)
			BFS(G,i);
	}
	printf("\n");
	vqs(G);
	printf("\nDFS:\n");
	
	for(int i=0;i<G->v;i++)
	{
		if(G->vis[i]==0)
			DFS(G,i);
	}
	
	printf("\n");
	return 0;
}
