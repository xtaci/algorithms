#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include "undirected_graph.h"

/**
 * randomly generate a graph, for test purpose
 */
struct Graph * undirected_graph_rand(int nvertex) 
{
	struct Graph * g = undirected_graph_create();
	int i;	
	
	for(i=0;i<nvertex;i++) {
		undirected_graph_add_vertex(g, i);
	}

	// random connect
	for(i=0;i<nvertex;i++) {
		int j;
		for(j=i+1;j<nvertex;j++) {
			int dice = rand()%5;
			if (dice == 0) {  // chance 20%
				int w = rand()%100;
				undirected_graph_add_edge(g, i, j, w);
			}
		}
	}

	
	return g;
}

int main()
{
	srand(time(NULL));
	int NVERTEX = 100;
	struct Graph * g = undirected_graph_rand(NVERTEX);
	undirected_graph_print(g);

	printf("Random Delete Vertex:\n");
	// random delete vertex 
	int i;
	for(i=0;i<NVERTEX;i++) {
		int n = rand()%NVERTEX;	
		printf("delete: %d\n", n);
		undirected_graph_del_vertex(g,n);
	}

	undirected_graph_print(g);
	printf("Delete All Edges: \n");
	
	for(i=0;i<NVERTEX;i++) {
		int j;
		for(j=i+1;j<NVERTEX;j++) {
			undirected_graph_del_edge(g, i, j);
		}
	}

	undirected_graph_print(g);
	graph_free(g);
	return 0;
}
