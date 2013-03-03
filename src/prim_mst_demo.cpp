#include <stdio.h>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include "undirected_graph.h"
#include "prim_mst.h"
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

int main(void)
{
	using namespace alg;
	srand(time(NULL));
	int NVERTEX = 10;
	UndirectedGraph * g = randgraph(NVERTEX);
	g->print();
	printf("Generating Prim's Graph: \n");	
	Prim pg(*g);
	pg.print();

	printf("Generating Minimal spanning tree: \n");	
	Graph * mst = pg.run();
	mst->print();
	delete mst;
	delete g;
	return 0;	
}
