#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "edmonds_karp.h"
#include "push_relabel.h"
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
		for(j=0;j<nvertex;j++) {
			if (i == j)
				continue;
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
	int NVERTEX = 500;

	clock_t ek_start, ek_end, pr_start, pr_end;

	DirectedGraph * g = randgraph(NVERTEX);
//	g->print();

	printf("finding Maximal Flow from 0 to nvertex-1: \n");	

	ek_start = clock();
	EdmondsKarp ek2(*g);
	uint32_t maxflow = ek2.run(0, NVERTEX-1);
	ek_end = clock();

	printf("Max Flow calculated by edmonds-karp algorithm is %d\n", maxflow);
//	printf("the residual network\n");
//	printf("\t");
//	for(uint32_t i=0;i<g->vertex_count();i++) {
//		printf("%d\t", ek2.rmap()[i]);
//	}
//	printf("\n");

//	for(uint32_t i=0;i<g->vertex_count();i++) {
//		printf("%d\t",ek2.rmap()[i]);
//		for(uint32_t j=0;j<g->vertex_count();j++) {
//			printf("%d\t", ek2.residual()(i,j));
//		}
//		printf("\n");
//	}
	
	pr_start = clock();
	PushRelabel pr2(*g);
	uint32_t maxflow_pr = pr2.run(0, NVERTEX-1);
	pr_end = clock();

	printf("Max Flow calculated by push-relabel is %d\n", maxflow_pr);
//	printf("the residual and preflow network\n");
//	printf("\t");
//	for(uint32_t i=0; i<g->vertex_count(); i++) {
//		 printf("%d\t", pr2.rmap()[i]);
//	}
//	printf("\n");

//	for (uint32_t i=0; i<g->vertex_count(); i++){
//		printf("%d\t", pr2.rmap()[i]);
//		for (uint32_t j=0; j<g->vertex_count(); j++){
//			printf("%d\t", pr2.residual()(i,j));
//		}
//		printf("\n");
//	}
//	printf("\n");

//	printf("the excess flow\n\t");
//	for (uint32_t i=0; i<g->vertex_count(); i++){
//		printf("%d\t", pr2.excess()[i]);
//	}
//	printf("\n");

//	printf("the height\n\t");
//	for (uint32_t i=0; i<g->vertex_count(); i++){
//		printf("%d\t", pr2.height()[i]);
//	}
//	printf("\n");

	long ek_time = ek_end - ek_start;
	long pr_time = pr_end - pr_start;
	
	printf("The number of clock tick consumed by edmonds-karp is %ld\n", ek_time);
	printf("--------------------------------- by push-relabel is %ld\n", pr_time);
	
	delete g;

	return 0;
}
