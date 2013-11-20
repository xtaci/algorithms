#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include "directed_graph.h"
#include "graph_search.h"
#include "scc.h"

using namespace alg;

int main()
{
	using namespace alg;
	srand(time(NULL));
	DirectedGraph * g = new DirectedGraph;
	// construct 3 islands
	int32_t i;
	for (i=0;i<9;i++) {
		g->add_vertex(i);
	}

	g->add_edge(0,1,1);
	g->add_edge(1,2,1);
	g->add_edge(2,0,1);

	g->add_edge(3,4,1);
	g->add_edge(4,5,1);
	g->add_edge(5,3,1);

	g->add_edge(6,7,1);
	g->add_edge(7,8,1);
	g->add_edge(8,6,1);

	// connect island
	g->add_edge(0,3,1);
	g->add_edge(3,8,1);

	g->printdot();

	printf("find strongly connected component\n");
	SCC(*g);

	delete g;
	return 0;
}
