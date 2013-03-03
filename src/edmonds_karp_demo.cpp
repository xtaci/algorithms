#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "edmonds_karp.h"
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

int main(void)
{
	using namespace alg;
	srand(time(NULL));
	int NVERTEX = 6;
	DirectedGraph * g = randgraph(NVERTEX);
	g->print();

	printf("finding Maximal Flow from 0 to 5: \n");	
	EdmondsKarp ek(*g);
	uint32_t maxflow = ek.run(0,5);

	printf("Max Flow is %d\n", maxflow);
	printf("the residual network\n");
	printf("\t");
	for(uint32_t i=0;i<g->vertex_count();i++) {
		printf("%d\t", ek.rmap()[i]);
	}
	printf("\n");

	for(uint32_t i=0;i<g->vertex_count();i++) {
		printf("%d\t",ek.rmap()[i]);
		for(uint32_t j=0;j<g->vertex_count();j++) {
			printf("%d\t", ek.residual()(i,j));
		}
		printf("\n");
	}

	delete g;

	return 0;
}
