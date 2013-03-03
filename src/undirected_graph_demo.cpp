#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include "undirected_graph.h"

using namespace alg;
/**
 * randomly generate a graph, for test purpose
 */
UndirectedGraph * randgraph(int nvertex) 
{
	UndirectedGraph * g = new UndirectedGraph;
	int i;	
	
	for(i=0;i<nvertex;i++) {
		g->add_vertex(i);
	}

	// random connect
	for(i=0;i<nvertex;i++) {
		int j;
		for(j=i+1;j<nvertex;j++) {
			int dice = rand()%5;
			if (dice == 0) {  // chance 20%
				int w = rand()%100;
				g->add_edge(i, j, w);
			}
		}
	}

	
	return g;
}

int main()
{
	srand(time(NULL));
	int NVERTEX = 20;
	UndirectedGraph * g = randgraph(NVERTEX);
	g->print();

	printf("Random Delete Vertex:\n");
	// random delete vertex 
	int i;
	for(i=0;i<NVERTEX;i++) {
		int n = rand()%NVERTEX;	
		printf("delete: %d\n", n);
		g->delete_vertex(n);
	}

	g->print();
	printf("Delete All Edges: \n");
	
	for(i=0;i<NVERTEX;i++) {
		int j;
		for(j=i+1;j<NVERTEX;j++) {
			g->delete_edge(i, j);
		}
	}

	g->print();
	return 0;
}
