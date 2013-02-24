#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "edmonds_karp.h"
/**
 * randomly generate a graph, for test purpose
 */
struct Graph * directed_graph_rand(int nvertex) 
{
	struct Graph * g = directed_graph_create();
	int i;	
	
	for(i=0;i<nvertex;i++) {
		directed_graph_add_vertex(g, i);
	}

	// random connect
	for(i=0;i<nvertex;i++) {
		int j;
		for(j=i+1;j<nvertex;j++) {
			int dice = rand()%2;
			if (dice == 0) {  
				int w = rand()%100;
				directed_graph_add_edge(g, i, j, w);
			}
		}
	}
	
	return g;
}


int main(void)
{
	srand(time(NULL));
	int NVERTEX = 6;
	struct Graph * g = directed_graph_rand(NVERTEX);
	directed_graph_print(g);

	printf("finding Maximal Flow from 0 to 5: \n");	
	struct EKResult * result =  edmonds_karp(g, 0, 5);

	printf("Max Flow is %d\n", result->maxflow);
	printf("the residual network\n");
	int i,j;
	printf("\t");
	for(i=0;i<result->num_vertex;i++) {
		printf("%d\t", (int)hash_table_get(result->rmap, i));
	}
	printf("\n");

	for(i=0;i<result->num_vertex;i++) {
		printf("%d\t", (int)hash_table_get(result->rmap, i));
		for(j=0;j<result->num_vertex;j++) {
			printf("%d\t", result->residual[i][j]);
		}
		printf("\n");
	}

	edmonds_karp_free(result);

	exit(0);
}
