#include "adt.h"
//int vis[100];
//struct queue Q;
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
	//deQ(&Q);
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

void BFS(struct graph *G,int V)//,struct queue Q,int vis[])
{
	V-=65;
	/*int vis[G->vtx];
	for(int i=0;i<G->vtx;i++)
	{
		vis[i]=0;
	}*/
	G->vis[V]=1;
	/*struct queue Q;
	init(&Q,20);*/
	enQ(&G->Q,V);
	while(!isE(&G->Q))
	{
		//printf("\nHEllo\n");
		//disp(Q);
		int cur_vtx=deQ(&G->Q);
		printf("%c", cur_vtx+65);
		/*for(int i=0;i<G->vtx;i++)
		{
			while(G->adj[cur_vtx][i])
			{
				int adj_vtx=i;
				if(G->vis[adj_vtx]==0)
				{
					G->vis[adj_vtx]=1;
					enQ(&G->Q,adj_vtx);
				}
				i++;
			}
		}*/
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
				//i++;
			}
		}
	}
	/*for(int i=0;i<G->vtx;i++)
	{
		if(vis[i]==0)
			BFS(G,i+65,Q,vis);
	}*/
}
void DFS(struct graph *G,int V)//,int vis[])
{
	V-=65;
	/*int vis[G->vtx];
	for(int i=0;i<G->vtx;i++)
	{
		vis[i]=0;
	}*/
	G->vis[V]=1;
	printf("%c",V+65);
	/*for(int i=0;i<G->vtx;i++)
		{
			while(G->adj[V][i])
			{
				int adj_vtx=i;
				if(G->vis[adj_vtx]==0)
				{
					DFS(G,adj_vtx+65);//,vis);
				}
				i++;
			}
		}*/
	for(int i=0;i<G->vtx;i++)
		{
			if(G->adj[V][i])
			{
				int adj_vtx=i;
				if(G->vis[adj_vtx]==0)
				{
					DFS(G,adj_vtx+65);//,vis);
				}
				//i++;
			}
		}
	/*for(int i=0;i<G->vtx;i++)
	{
		if(vis[i]==0)
			DFS(G,i+65,vis);
	}*/
}
