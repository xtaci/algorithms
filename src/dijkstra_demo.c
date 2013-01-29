#include <stdio.h>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include "directed_graph.h"
#include "dijkstra.h"

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


int main(void)
{
	srand(time(NULL));
	int NVERTEX = 50;
	struct Graph * g = directed_graph_rand(NVERTEX);
	directed_graph_print(g);

	printf("finding Dijkstra shortest path starting from 0: \n");	
	struct DijkWorkspace * dr = dijkstra_run(g, graph_lookup(g,0));
	int i;
	for(i=0;i < dr->num_vertex;i++) {
		printf("previous of %u is ", dr->vertex_ids[i]);
		uintptr_t pre = perfect_hash_get(dr->previous, dr->vertex_ids[i]);
		if (pre ==undefined) { printf("undefined\n"); }
		else printf("%u\n", (uint32_t)pre);
	}

	exit(0);	
}
