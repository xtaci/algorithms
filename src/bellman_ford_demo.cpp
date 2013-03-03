#include <stdio.h>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include "directed_graph.h"
#include "bellman_ford.h"

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
	for(i=3;i<nvertex;i++) {
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

int main(void)
{
	srand(time(NULL));
	int NVERTEX = 50;
	DirectedGraph * g = randgraph(NVERTEX);

	printf("finding bellman-ford shortest path starting from 3: \n");	
	BellmanFord bf(*g, 3);

	g->print();
	const HashTable<int32_t> & previous = bf.run();	
	Graph::Adjacent * a;
	list_for_each_entry(a, &g->list(), a_node) {
		printf("previous of %u is ", a->v.id);
		if (previous[a->v.id]==UNDEFINED) { printf("UNDEFINED\n"); }
		else printf("%u\n", previous[a->v.id]);
	}
	printf("\nwe %s have negative weighted cycle.\n", bf.has_negative_cycle()?"DO":"DON'T");

	printf("\nconstructing a negative cycle and run again\n");	

	// construct a negative cycle;
	g->add_edge(0,1, -1);
	g->add_edge(1,2, -1);
	g->add_edge(2,0, -1);

	BellmanFord bf2(*g, 0);
	bf2.run();

	printf("\nwe %s have negative weighted cycle.\n", bf2.has_negative_cycle()?"DO":"DON'T");

	delete g;
	return 0;	
}
