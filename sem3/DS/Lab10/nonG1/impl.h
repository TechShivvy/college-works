#include "adt.h"
void vQ(struct graph *G)
{
	for(int i=0;i<100;i++)
	{
		G->vis[i]=0;
	}
	while(!isE(&G->Q))
	{
		deQ(&G->Q);
	}
}
void create(struct graph *G,int v,int e,int d)
{
	G->vtx=v;
	G->edge=e;
	init(&G->Q,20);
	for(int i=0;i<v;i++)
	{
		for(int j=0;j<v;j++)
		{
			G->adj[i][j]=0;
		}
	}
	vQ(G);
	char edge[2];
	//if(d)
	{
	for(int i=0;i<e;i++)
	{
		printf("Enter the edge: ");
		scanf("%s",edge);
		G->adj[edge[0]-'A'][edge[1]-'A']=1;
		if(!d)
			G->adj[edge[1]-'A'][edge[0]-'A']=1;
	}
	/*G->adj[0][1]=1;
	G->adj[1][2]=1;
	G->adj[1][3]=1;
	G->adj[2][0]=1;
	G->adj[2][5]=1;
	G->adj[3][4]=1;
	G->adj[4][5]=1;*/
	/*G->adj[0][4]=1;
	G->adj[1][2]=1;
	G->adj[1][3]=1;
	G->adj[1][4]=1;
	G->adj[2][3]=1;
	G->adj[3][4]=1;*/
	/*G->adj[1][3]=1;
	G->adj[2][3]=1;
	G->adj[0][4]=1;
	G->adj[4][5]=1;
	G->adj[5][6]=1;*/
	return;
	
	}
	//return;
	for(int i=0;i<e;i++)
	{
		printf("Enter the edge: ");
		scanf("%s",edge);
		G->adj[edge[0]-'A'][edge[1]-'A']=1;
		G->adj[edge[1]-'A'][edge[0]-'A']=1;
	}
}
void dispMat(struct graph *G)
{
	for(int i=0;i<G->vtx;i++)
	{
		for(int j=0;j<G->vtx;j++)
		{
			printf("%d ",G->adj[i][j]);
		}
		printf("\n");
	}
}
void BFS(struct graph *G)
{
	for(int i=0;i<G->vtx;i++)
	{
		if(G->vis[i]==0)
			BFSprint(G,i+65);
	}
}
void BFS1(struct graph *G)
{
	for(int i=0;i<G->vtx;i++)
	{
		if(G->vis[i]==0)
		{
			BFSprint(G,i+65);
			printf("\n");
		}
	}
}
void BFSprint(struct graph *G,int V)
{
	V-=65;
	G->vis[V]=1;
	enQ(&G->Q,V);
	while(!isE(&G->Q))
	{
		int cur_vtx=deQ(&G->Q);
		printf("%c", cur_vtx+65);
		for(int i=0;i<G->vtx;i++)
		{
			if(G->adj[cur_vtx][i])
			{
				int adj_vtx=i;
				if(G->vis[adj_vtx]==0)
				{
					G->vis[adj_vtx]=1;
					enQ(&G->Q,adj_vtx);
				}
			}
		}
	}
}
void DFS(struct graph *G)
{
	for(int i=0;i<G->vtx;i++)
	{
		if(G->vis[i]==0)
			DFSprint(G,i+65);
	}
}
void DFSprint(struct graph *G,int V) //recursive
{
	V-=65;
	G->vis[V]=1;
	printf("%c",V+65);
	for(int i=0;i<G->vtx;i++)
		{
			if(G->adj[V][i])
			{
				int adj_vtx=i;
				if(G->vis[adj_vtx]==0)
				{
					DFS(G,adj_vtx+65);
				}
				
			}
		}
}
/*void DFSprint(struct graph *g,int V) //using actual stack
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
}*/
