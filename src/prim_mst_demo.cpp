#include <stdio.h>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include "undirected_graph.h"
#include "prim_mst.h"

int main(void)
{
	using namespace alg;
	srand(time(NULL));
	int NVERTEX = 10;
	alg::UndirectedGraph * g = alg::UndirectedGraph::randgraph(NVERTEX);
	g->printdot();
	printf("Generating Prim's Graph: \n");	
	Graph * prim = alg::Prim::run(*g, 1);
	prim->printdot();
	delete prim;
	delete g;
	return 0;	
}
