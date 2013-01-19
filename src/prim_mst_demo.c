#include <stdio.h>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include "undirected_graph.h"
#include "prim_mst.h"

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


int main(void)
{
	srand(time(NULL));
	int NVERTEX = 10;
	struct Graph * g = undirected_graph_rand(NVERTEX);
	undirected_graph_print(g);

	printf("Generating Prim's Graph: \n");	
	struct PrimGraph * pg = prim_mst_init(g);
	prim_mst_print(pg);

	printf("Generating Minimal spanning tree: \n");	
	struct Graph * mst = prim_mst_run(pg);
	undirected_graph_print(mst);

	exit(0);	
}
