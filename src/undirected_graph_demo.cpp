#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include "undirected_graph.h"

using namespace alg;
int main()
{
	srand(time(NULL));
	int NVERTEX = 20;
	UndirectedGraph * g = UndirectedGraph::randgraph(NVERTEX);
	g->printdot();

	printf("Random Delete Vertex:\n");
	// random delete vertex 
	int i;
	for(i=0;i<NVERTEX;i++) {
		int n = rand()%NVERTEX;	
		printf("delete: %d\n", n);
		g->delete_vertex(n);
	}

	g->printdot();
	printf("Delete All Edges: \n");
	
	for(i=0;i<NVERTEX;i++) {
		int j;
		for(j=i+1;j<NVERTEX;j++) {
			g->delete_edge(i, j);
		}
	}

	g->printdot();
	return 0;
}
