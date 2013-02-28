#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include "graph_search.h"
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
	using namespace alg;
	srand(time(NULL));
	int NVERTEX = 10;
	Graph * g = randgraph(NVERTEX);
	g->print();

	printf("breadth first search: \n");
	breadth_first_search(*g, 0);
	printf("depth first search: \n");
	depth_first_search(*g, 0);

	delete g;
	exit(0);
}
