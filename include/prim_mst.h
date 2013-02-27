/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * PRIM'S ALGORITHM -- MINIMUM SPANNING TREE
 *
 * Features:
 *
 *   Prim's algorithm is a greedy algorithm that finds a minimum spanning tree
 * for a connected weighted undirected graph. This means it finds a subset of 
 * the edges that forms a tree that includes every vertex, where the total 
 * weight of all the edges in the tree is minimized. The algorithm was 
 * developed in 1930 by Czech mathematician Vojtěch Jarník and later 
 * independently by computer scientist Robert C. Prim in 1957 and rediscovered
 * by Edsger Dijkstra in 1959. Therefore it is also sometimes called the DJP
 * algorithm, the Jarník algorithm, or the Prim–Jarník algorithm.
 *
 * http://en.wikipedia.org/wiki/Prim%27s_algorithm
 *
 ******************************************************************************/

#ifndef __PRIM_MST_H__
#define __PRIM_MST_H__

#include <stdio.h>
#include <stdlib.h>
#include "undirected_graph.h"
#include "double_linked_list.h"
#include "heap.h"

namespace alg {
	/**
	 * Adjacent Lists optimized for Prim's Algorithm
	 */
	struct PrimAdjacent {
		Heap<struct Vertex*> * heap; 		// binary heap representation of weight->node
							// the top of the heap is always the minimal element
		struct Vertex * v;
		struct list_head pa_node; 
	};

	/**
	 * Prim's Graph
	 */
	struct PrimGraph {
		struct list_head pa_head;
	};

	/**
	 * add an adjacent list to prim's graph
	 */
	static inline void 
	__prim_mst_add_adjacent(struct PrimGraph * pg, struct Adjacent * a)
	{
		struct PrimAdjacent * pa = (struct PrimAdjacent *)malloc(sizeof(struct PrimAdjacent));		
		list_add_tail(&pa->pa_node, &pg->pa_head);

		pa->v = &a->v;	
		pa->heap = new Heap<struct Vertex *>(a->num_neigh);

		struct Vertex * v;
		list_for_each_entry(v, &a->v_head, v_node){
			pa->heap->insert(v->weight, v);  // weight->vertex
		}
	}

	/**
	 * init prim's graph using undirected graph.
	 */
	static inline struct PrimGraph * 
	prim_mst_init(const struct Graph * g)
	{
		struct PrimGraph * pg = (struct PrimGraph*)malloc(sizeof(struct PrimGraph));
		INIT_LIST_HEAD(&pg->pa_head);

		struct Adjacent * a;
		list_for_each_entry(a, &g->a_head, a_node){
			__prim_mst_add_adjacent(pg, a);
		}

		return pg;
	}

	/**
	 * lookup up a given id
	 * the related adjacent list is returned.
	 */ 
	static inline struct PrimAdjacent * 
	__prim_mst_lookup(struct PrimGraph * pg, uint32_t id)
	{
		struct PrimAdjacent * pa;
		list_for_each_entry(pa, &pg->pa_head, pa_node){
			if (pa->v->id == id) { return pa;}
		}
		
		return NULL;
	}

	/**
	 * Prim's Algorithm. 
	 *
	 * Input: A non-empty connected weighted graph with vertices V and edges E 
	 *        (the weights can be negative).
	 *
	 * Initialize: Vnew = {x}, where x is an arbitrary node (starting point) from V, Enew = {}
	 *
	 * Repeat until Vnew = V:
	 *   1. Choose an edge {u, v} with minimal weight such that u is in Vnew and v
	 *      is not (if there are multiple edges with the same weight, any of them may be picked)
	 *   2. Add v to Vnew, and {u, v} to Enew
	 *
	 * Output: Vnew and Enew describe a minimal spanning tree
	 */
	static struct Graph * 
	prim_mst_run(struct PrimGraph * pg)
	{
		struct Graph * mst = undirected_graph_create(); // empty set == Vnew
		
		// choose the first vertex as the starting point
		struct PrimAdjacent * pa;
		list_for_each_entry(pa, &pg->pa_head, pa_node){ break; }
		struct Vertex * v = pa->v;
		undirected_graph_add_vertex(mst, v->id);

		// Prim's Algorithm
		while(true) {
			int weight = INT_MAX;			// loop tmp variables
			uint32_t best_to;
			struct PrimAdjacent * best_from;

			// for each Vnew, find a new vertex in V that has minimal weight.
			struct Adjacent * a; 
			list_for_each_entry(a, &mst->a_head, a_node){
				pa = __prim_mst_lookup(pg, a->v.id);
				while (!pa->heap->is_empty()) { 	// find one neighbour
					v = pa->heap->min_value(); 
					if (graph_lookup(mst,v->id)==NULL) {  // if new V appears 
						if (pa->heap->min_key() < weight) {
							weight = pa->heap->min_key();
							best_to = v->id;
							best_from = pa; 
						}
						break;
					} else {
						pa->heap->delete_min();
					}
				}
			}

			if (weight != INT_MAX) {
				// congrats , new V & E
				undirected_graph_add_vertex(mst, best_to);
				undirected_graph_add_edge(mst, best_from->v->id, best_to, weight);
				best_from->heap->delete_min();
			} else break;
		};

		return mst;
	}

	/**
	 * print the PrimGraph
	 */
	static inline void 
	prim_mst_print(const struct PrimGraph * pg)
	{
		struct PrimAdjacent * pa;
		printf("Prim Graph: \n");
		list_for_each_entry(pa, &pg->pa_head, pa_node){
			printf("%d->{", pa->v->id);
			for(uint32_t i=0;i<pa->heap->count();i++) {
				struct Vertex * v = (*pa->heap)[i];
				printf("id:%d->w:%d \t", v->id, v->weight);
			}
			printf("}\n");
		}
	}
}

#endif //
