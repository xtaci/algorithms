#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include "graph_search.h"
#include "directed_graph.h"

/**
 * randomly generate a graph, for test purpose
 */
struct Graph * directed_graph_rand(int nvertex) 
{
	struct Graph * g = directed_graph_create();
	int i;	
	
	for(i=0;i<nvertex;i++) {
		directed_graph_add_vertex(g, i);
	}

	// random connect
	for(i=0;i<nvertex;i++) {
		int j;
		for(j=i+1;j<nvertex;j++) {
			int dice = rand()%5;
			if (dice == 0) {  // chance 20%
				int w = rand()%100;
				directed_graph_add_edge(g, i, j, w);
			}
		}
	}

	
	return g;
}

int main()
{
	srand(time(NULL));
	int NVERTEX = 100;
	struct Graph * g = directed_graph_rand(NVERTEX);
	directed_graph_print(g);

	printf("breadth first search: \n");
	breadth_first_search(g, 0);
	printf("depth first search: \n");
	depth_first_search(g, 0);

	exit(0);
}
