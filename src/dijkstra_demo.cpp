#include <stdio.h>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <memory>

#include "directed_graph.h"
#include "dijkstra.h"

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
	int NVERTEX = 10;
	std::auto_ptr<DirectedGraph> g(randgraph(NVERTEX));
	g->printdot();

	Graph::Adjacent * a;
	printf("finding Dijkstra shortest path starting from 0: \n");
	HashTable<int32_t,int32_t> * result = Dijkstra::run(*g, 0);

	list_for_each_entry(a, &g->list(), a_node){
		printf("previous of %u is ", a->v.id);
		int32_t pre = (*result)[a->v.id];
		if (pre == Dijkstra::UNDEFINED) { printf("UNDEFINED\n"); }
		else printf("%d\n", pre);
	}
	delete result;

	printf("finding Dijkstra shortest path starting from 1: \n");	

	result = Dijkstra::run(*g, 1);
	list_for_each_entry(a, &g->list(), a_node){
		printf("previous of %u is ", a->v.id);
		int32_t pre = (*result)[a->v.id];
		if (pre == Dijkstra::UNDEFINED) { printf("UNDEFINED\n"); }
		else printf("%d\n", pre);
	}
	delete result;

	return 0;	
}
