#include <stdio.h>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <memory>

#include "directed_graph.h"
#include "bellman_ford.h"

using namespace alg;
int main(void)
{
	srand(time(NULL));
	int NVERTEX = 10;
	DirectedGraph * g = DirectedGraph::randgraph(NVERTEX);
	g->printdot();

	BellmanFord bf(*g);

	printf("finding bellman-ford shortest path starting from 3: \n");	
	std::auto_ptr<HashTable<int32_t, int32_t> > previous(bf.run(3));	

	Graph::Adjacent * a;
	list_for_each_entry(a, &g->list(), a_node) {
		printf("previous of %u is ", a->v.id);
		if ((*previous)[a->v.id]==UNDEFINED) { printf("UNDEFINED\n"); }
		else printf("%u\n", (*previous)[a->v.id]);
	}
	printf("\nwe %s have negative weighted cycle.\n", bf.has_negative_cycle()?"DO":"DON'T");

	printf("\nconstructing a negative cycle and run again\n");	

	// construct a negative cycle;
	g->add_vertex(100);
	g->add_vertex(101);
	g->add_vertex(102);
	g->add_edge(100,101, -1);
	g->add_edge(101,102, -1);
	g->add_edge(102,100, -1);

	BellmanFord bf2(*g);
	std::auto_ptr<HashTable<int32_t, int32_t> > previous2(bf2.run(0));

	g->printdot();
	printf("\nwe %s have negative weighted cycle.\n", bf2.has_negative_cycle()?"DO":"DON'T");

	delete g;
	return 0;	
}
