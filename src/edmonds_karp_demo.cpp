#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "edmonds_karp.h"
using namespace alg;
int main(void)
{
	using namespace alg;
	srand(time(NULL));
	int NVERTEX = 6;
	DirectedGraph * g = DirectedGraph::randgraph(NVERTEX);
	g->printdot();

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
