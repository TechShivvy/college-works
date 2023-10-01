#include "adt.h"
void create(struct graph *G,int v,int e,int d)
{
	G->vtx=v;
	G->edge=e;
	//init(&G->Q,20);
	for(int i=0;i<v;i++)
	{
		for(int j=0;j<v;j++)
		{
			G->dist[i][j]=0;
			G->pred[i][j]=0;
		}
	}
	//vQ(G);
	char edge[2];
	//if(d)
	for(int i=0;i<e;i++)
	{
		printf("Enter the edge: ");
		scanf("%s",edge);
		int data;
		printf("Enter the Dist: ");
		scanf("%d",&dist);
		G->dist[edge[0]-'1'][edge[1]-'1']=dist;
		if(!d)
			G->dist[edge[1]-'1'][edge[0]-'1']=dist;
	}
}
