#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "undirected_graph.h"
#include "kruskal_mst.h"

using namespace alg;
int main(void)
{
	using namespace alg;
	srand(time(NULL));
	int NVERTEX = 10;
	UndirectedGraph * g = UndirectedGraph::randgraph(NVERTEX);
	g->printdot();
	printf("Generating Kruskal's Graph: \n");
	Kruskal pg(*g);
	pg.print();


	printf("Generating Minimal spanning tree: \n");
	Graph * mst = pg.run();
	mst->printdot();
	delete mst;
	delete g;
	return 0;
}

