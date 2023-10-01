#include<stdlib.h>
#include "impl.h"
int BFS2(struct graph *G,int V,int S);//,struct queue Q,int vis[]);
void BFS3(struct graph *G,int V);//,struct queue *Q,int *vis);
int main()
{
	//init(&Q,20);
	struct graph *G=(struct graph*)malloc(sizeof(struct graph));
	int v,e;
	//int v=6,e=7;
	printf("\nMenu:\n1.BFS and DFS for a graph\n2.Check whether a path exists btw 2 vertices\n3.Find the connected components in a graph\n4.Exit\n");
	int ch;
	
	do{
	printf("\nChoice: ");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:
			printf("Enter the number of verties and edges: ");
	scanf("%d%d",&v,&e);
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
		if(G->vis[i]==0)
			BFS(G,i+65);//,Q,vis);
	}
	
	
	//BFS(G,'A',Q,vis);
	printf("\n");
	vQ(G);
	//int vis[G->vtx];
	/*for(int i=0;i<G->vtx;i++)
	{
		vis[i]=0;
	}*/
	printf("\nDFS:\n");
	
	for(int i=0;i<G->vtx;i++)
	{
		if(G->vis[i]==0)
			DFS(G,i+65);//,vis);
	}
	//DFS(G,'A',vis);
	printf("\n");
	vQ(G);
	/*for(int i=0;i<100;i++)
	{
		vis[i]=0;
	}*/
	
			break;
		case 2: 
			printf("\nEnter source: ");
			char s,d;
			scanf(" %c",&s);
			printf("Enter destination: ");
			scanf(" %c",&d);
			printf("\n%c to %c: ",s,d);
	int ans=BFS2(G,s,d);//Q,vis,'F');
	if(ans)	
		printf("Path exists!\n");
	else
		printf("Path doesn't exist!\n");
	/*for(int i=0;i<100;i++)
	{
		vis[i]=0;
	}*/
	vQ(G);
	/*printf("\nF to B: ");
	ans=BFS2(G,'F','B');//Q,vis,);
	if(ans)	
		printf("Yes!\n");
	else
		printf("No!\n");
	printf("\n");*/
			break;
		case 3:printf("\n");
			struct graph *G1=(struct graph*)malloc(sizeof(struct graph));
	//int v1,e1;
	int v1=5,e1=3;//ENTER AB,BC,DE
	printf("Enter the number of verties and edges: ");
	scanf("%d%d",&v1,&e1);
	create(G1,v1,e1,0);
	dispMat(G1);
	/*for(int i=0;i<100;i++)
	{
		vis[i]=0;
	}
	struct queue Q1;
	init(&Q1,20);*/
	printf("\nConnected Comps:\n");
	int count=0;
	
	for(int i=0;i<G1->vtx;i++)
	{
		
		if(G1->vis[i]==0)
		{
			count++;
			BFS(G1,i+65);//,Q,vis);
			printf("\n");
		}
	}
	
	//BFS3(G1,'A');//,Q1,vis);
	printf("\n%d Connected components!\n",count);
			break;
		case 4:printf("\nExiting...\n");
			break;
		default:printf("\nInvalid input!\n");
	}
	
	}while(ch!=4);
	
	
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
	G->vis[V]=1;
	/*struct queue Q;
	init(&Q,20);*/
	enQ(&G->Q,V);
	while(!isE(&G->Q))
	{
		//printf("\nHEllo\n");
		//disp(Q);
		int cur_vtx=deQ(&G->Q);
		//printf("%c", cur_vtx+65);
		/*for(int i=0;i<G->vtx;i++)
		{
			while(G->adj[cur_vtx][i])
			{
				int adj_vtx=i;
				if(adj_vtx+65==S)
					return 1;
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
void BFS3(struct graph *G,int V)//,struct queue Q,int vis[])
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
		{
			printf("\n");
			BFS3(G,i+65,Q,vis);
		}
	}*/
}
