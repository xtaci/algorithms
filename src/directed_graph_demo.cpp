#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include "directed_graph.h"

using namespace alg;
/**
 * randomly generate a graph, for test purpose
 */
DirectedGraph * randgraph(int nvertex) 
{
	DirectedGraph * g = new DirectedGraph;
	int i;	
	
	for(i=0;i<nvertex;i++) {
		g->add_vertex(i);
	}

	// random connect
	for(i=0;i<nvertex;i++) {
		int j;
		for(j=i+1;j<nvertex;j++) {
			int dice = rand()%2;
			if (dice == 0) { 
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
	DirectedGraph * g = randgraph(NVERTEX);
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
	exit(0);
}
