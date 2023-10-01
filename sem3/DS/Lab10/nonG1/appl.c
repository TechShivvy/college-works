#include<stdlib.h>
#include "impl.h"
int BFS2(struct graph *G,int V,int S);
int main()
{
	struct graph *G=(struct graph*)malloc(sizeof(struct graph));
	int v,e;
	printf("Enter the number of verties and edges: ");
	scanf("%d%d",&v,&e);
	create(G,v,e,1);
	dispMat(G);
	printf("\nBFS:\n");
	BFS(G);
	printf("\n");
	vQ(G);
	printf("\nDFS:\n");
	DFS(G);
	printf("\n");
	vQ(G);
	printf("\nD to F: ");
	int ans=BFS2(G,'D','F');
	if(ans)	
		printf("Yes!\n");
	else
		printf("No!\n");
	vQ(G);
	printf("\nF to B: ");
	ans=BFS2(G,'F','B');
	if(ans)	
		printf("Yes!\n");
	else
		printf("No!\n");
	printf("\n");
	struct graph *G1=(struct graph*)malloc(sizeof(struct graph));
	//int v1,e1;
	int v1=5,e1=3;//ENTER AB,BC,DE
	/*printf("Enter the number of verties and edges: ");
	scanf("%d%d",&v1,&e1);*/
	create(G1,v1,e1,0);
	dispMat(G1);
	printf("\nConnected Comps:\n");
	DFS(G1);
	printf("\n");
	return 0;
}

int BFS2(struct graph *G,int V,int S)
{
	V-=65;
	G->vis[V]=1;
	enQ(&G->Q,V);
	while(!isE(&G->Q))
	{
		int cur_vtx=deQ(&G->Q);
		for(int i=0;i<G->vtx;i++)
		{
			if(G->adj[cur_vtx][i])
			{
				int adj_vtx=i;
				if(adj_vtx+65==S)
					return 1;
				if(G->vis[adj_vtx]==0)
				{
					G->vis[adj_vtx]=1;
					enQ(&G->Q,adj_vtx);
				}
				//i++;
			}
		}
	}
	return 0;
}
