#include "impl.h"
#include<stdlib.h>
int main()
{
	 struct graph *G=(struct graph *)malloc(sizeof(struct graph));
	 int ch;
	 printf("\nMenu:\n1.Create a graph\n2.Display the graph matrices\n3.Apply Floyd Warshall\n4.Display Path\n5.Exit\n");
	 do
	 {
	 	printf("\nChoice: ");
	 	scanf("%d",&ch);
	 	switch(ch)
	 	{
	 		case 1:  
	 			printf("Enter the number of verties and edges: ");
	 			int v,e;
				scanf("%d%d",&v,&e);
				create(G,v,e,1);
	 			break;
	 		case 2:
	 			disp(G);
	 			break;
	 		case 3:
	 			floyd(G);
	 			break;
	 		case 4:
	 			printf("Enter source and destination: ");
	 			int s,d;
	 			scanf("%d%d",&s,&d);
	 			printf("\nPath from %d to %d: %d",s,d,s);
	path(G,s-1,d-1);
	printf("\nShoretst dist: %d\n",G->dist[s-1][d-1]);
	 			break;
	 		case 5:printf("\nExiting...\n");
	 			break;
	 		default:printf("\nInavlid Input!\n");
	 	}
	 }while(ch!=5);
	//create(G,3,5,1);
	//int s=4,d=1;
	
}
