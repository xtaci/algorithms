#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "edmonds_karp.h"
#include "relabel_to_front.h"
using namespace alg;

int main(void)
{
	using namespace alg;
	srand(time(NULL));
	int NVERTEX = 300;

	clock_t ek_start, ek_end, pr_start, pr_end;

	DirectedGraph * g = DirectedGraph::randgraph(NVERTEX);
//	g->printdot();

	printf("finding Maximal Flow from 0 to %d: \n", NVERTEX-1);
	printf("The graph containing %d edges.\n", g->edge_count());

	ek_start = clock();
	EdmondsKarp ek(*g);
	uint32_t maxflow = ek.run(0, NVERTEX-1);
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
	RelabelToFront pr2(*g);
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

	long ek_time = ek_end - ek_start;
	long pr_time = pr_end - pr_start;
	
	printf("The number of clock tick consumed by edmonds-karp is %ld\n", ek_time);
	printf("--------------------------------- by push-relabel is %ld\n", pr_time);
	
	delete g;

	return 0;
}
