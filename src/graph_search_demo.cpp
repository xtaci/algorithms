#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include "graph_search.h"
#include "directed_graph.h"

using namespace alg;

int main()
{
	using namespace alg;
	srand(time(NULL));
	int NVERTEX = 10;
	Graph * g = DirectedGraph::randgraph(NVERTEX);
	g->printdot();

	printf("breadth first search: \n");
	BFS(*g, 0);
	printf("depth first search: \n");
	DFS(*g);

	delete g;
	return 0;
}
