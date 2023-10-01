#include<stdio.h>
struct graph
{
	int dist[10][10],pred[10][10],adj[10][10];
	int vtx;
	int edge;
};
void create(struct graph *G,int v,int e,int d);
void disp(struct graph *G);
void floyd(struct graph *G);
void path(struct graph *G,int i,int j);
