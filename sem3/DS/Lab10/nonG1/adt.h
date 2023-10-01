#include<stdio.h>
#include "stackimpl.h"
#include "qimpl.h"
struct graph
{
	int adj[10][10];
	int vtx;
	int edge;
	int vis[100];
	struct queue Q;
};
void create(struct graph *G,int v,int e,int d);
void dispMat(struct graph *G);
//void BFS(struct graph *G,int);
void BFS(struct graph *G);
void DFS(struct graph *G;
void BFSprint(struct graph *G,int V);//,struct queue Q,int vis[]);
void DFSprint(struct graph *G,int);//,int[]);
