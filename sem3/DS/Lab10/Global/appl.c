#include<stdlib.h>
#include "impl.h"
int BFS2(struct graph *G,int V,int S);//,struct queue Q,int vis[]);
void BFS3(struct graph *G,int V);//,struct queue *Q,int *vis);
int main()
{
	init(&Q,20);
	struct graph *G=(struct graph*)malloc(sizeof(struct graph));
	int v=6,e=7;
	//printf("Enter the number of verties and edges: ");
	//scanf("%d%d",&v,&e);
	//int v=5,e=6;
	//int v=7,e=5;
	create(G,v,e,1);
	dispMat(G);
	/*struct queue Q;
	init(&Q,20);
	int vis[100];
	for(int i=0;i<100;i++)
	{
		vis[i]=0;
	}*/
	printf("\nBFS:\n");
	
	for(int i=0;i<G->vtx;i++)
	{
		if(vis[i]==0)
			BFS(G,i+65);//,Q,vis);
	}
	
	
	//BFS(G,'A',Q,vis);
	printf("\n");
	vQ();
	//int vis[G->vtx];
	/*for(int i=0;i<G->vtx;i++)
	{
		vis[i]=0;
	}*/
	printf("\nDFS:\n");
	
	for(int i=0;i<G->vtx;i++)
	{
		if(vis[i]==0)
			DFS(G,i+65);//,vis);
	}
	
	
	//DFS(G,'A',vis);
	printf("\n");
	vQ();
	/*for(int i=0;i<100;i++)
	{
		vis[i]=0;
	}*/
	printf("\nD to F: ");
	int ans=BFS2(G,'D','F');//Q,vis,'F');
	if(ans)	
		printf("Yes!\n");
	else
		printf("No!\n");
	/*for(int i=0;i<100;i++)
	{
		vis[i]=0;
	}*/
	vQ();
	printf("\nF to B: ");
	ans=BFS2(G,'F','B');//Q,vis,);
	if(ans)	
		printf("Yes!\n");
	else
		printf("No!\n");
	printf("\n");
	struct graph *G1=(struct graph*)malloc(sizeof(struct graph));
	int v1=5,e1=3;
	create(G1,v1,e1,0);
	dispMat(G1);
	/*for(int i=0;i<100;i++)
	{
		vis[i]=0;
	}
	struct queue Q1;
	init(&Q1,20);*/
	printf("\nConnected Comps:\n");
	
	
	for(int i=0;i<G1->vtx;i++)
	{
		
		if(vis[i]==0)
		{
			BFS3(G1,i+65);//,Q,vis);
			printf("\n");
		}
	}
	
	//BFS3(G1,'A');//,Q1,vis);
	printf("\n");
	return 0;
}

int BFS2(struct graph *G,int V,int S)//,struct queue Q,int vis[],)
{
	V-=65;
	/*int vis[G->vtx];
	for(int i=0;i<G->vtx;i++)
	{
		vis[i]=0;
	}*/
	vis[V]=1;
	/*struct queue Q;
	init(&Q,20);*/
	enQ(&Q,V);
	while(!isE(&Q))
	{
		//printf("\nHEllo\n");
		//disp(Q);
		int cur_vtx=deQ(&Q);
		//printf("%c", cur_vtx+65);
		for(int i=0;i<G->vtx;i++)
		{
			while(G->adj[cur_vtx][i])
			{
				int adj_vtx=i;
				if(adj_vtx+65==S)
					return 1;
				if(vis[adj_vtx]==0)
				{
					vis[adj_vtx]=1;
					enQ(&Q,adj_vtx);
				}
				i++;
			}
		}
	}
	return 0;
}
void BFS3(struct graph *G,int V)//,struct queue Q,int vis[])
{
	V-=65;
	/*int vis[G->vtx];
	for(int i=0;i<G->vtx;i++)
	{
		vis[i]=0;
	}*/
	vis[V]=1;
	/*struct queue Q;
	init(&Q,20);*/
	enQ(&Q,V);
	while(!isE(&Q))
	{
		//printf("\nHEllo\n");
		//disp(Q);
		int cur_vtx=deQ(&Q);
		printf("%c", cur_vtx+65);
		for(int i=0;i<G->vtx;i++)
		{
			while(G->adj[cur_vtx][i])
			{
				int adj_vtx=i;
				if(vis[adj_vtx]==0)
				{
					vis[adj_vtx]=1;
					enQ(&Q,adj_vtx);
				}
				i++;
			}
		}
	}
	/*for(int i=0;i<G->vtx;i++)
	{
		
		if(vis[i]==0)
		{
			printf("\n");
			BFS3(G,i+65,Q,vis);
		}
	}*/
}
