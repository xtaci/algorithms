#include <stdio.h>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include "directed_graph.h"
#include "bellman_ford.h"

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
	for(i=3;i<nvertex;i++) {
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
	using namespace alg;
	srand(time(NULL));
	int NVERTEX = 50;
	struct Graph * g = directed_graph_rand(NVERTEX);
	directed_graph_print(g);

	printf("finding bellman-ford shortest path starting from 3: \n");	
	struct BFResult * bfw = bellman_ford_run(g, graph_lookup(g,3));
	
	struct Adjacent * a;
	list_for_each_entry(a, &g->a_head, a_node) {
		printf("previous of %u is ", a->v.id);
		if ((*bfw->previous)[a->v.id]==UNDEFINED) { printf("UNDEFINED\n"); }
		else printf("%u\n", (*bfw->previous)[a->v.id]);
	}
	printf("\nwe %s have negative weighted cycle.\n", bfw->has_neg_cycle?"DO":"DON'T");
	bellman_ford_free(bfw);

	printf("\nconstructing a negative cycle and run again\n");	
	// construct a negative cycle;
	directed_graph_add_edge(g,0,1, -1);
	directed_graph_add_edge(g,1,2, -1);
	directed_graph_add_edge(g,2,0, -1);
	bfw = bellman_ford_run(g, graph_lookup(g,3));

	printf("\nwe %s have negative weighted cycle.\n", bfw->has_neg_cycle?"DO":"DON'T");

	bellman_ford_free(bfw);
	graph_free(g);
	exit(0);	
}
