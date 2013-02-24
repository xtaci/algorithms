/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * DIJKSTRA ALGORITHM
 * 
 * Features:
 * 
 *   Dijkstra's algorithm, conceived by Dutch computer scientist Edsger Dijkstra
 * in 1956 and published in 1959,[1][2] is a graph search algorithm that
 * solves the single-source shortest path problem for a graph with nonnegative
 * edge path costs, producing a shortest path tree. This algorithm is often
 * used in routing and as a subroutine in other graph algorithms.
 *
 * http://en.wikipedia.org/wiki/Dijkstra's_algorithm
 *
 ******************************************************************************/

#ifndef __DIJKSTRA_H__
#define __DIJKSTRA_H__

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

#include "heap.h"
#include "directed_graph.h"
#include "stack.h"
#include "hash_table.h"

#define undefined ((uintptr_t)-1)

/**
 * the dijkstra algorithm workspace
 */
struct DijkstraResult {
	struct Heap * Q;		// a binary heap
	struct HashTable * dist; 	// distance hash table
	struct HashTable * previous; 	// previous vertex hash table
};

/**
 * reorder operation i.e. heap decrease key operation.
 */
static inline void
__dijkstra_reorder(struct Heap * heap, uint32_t id, uint32_t new_weight)
{	
	int index;
	int key = new_weight;
	if ((index=heap_find_value(heap, (uintptr_t)id))!=-1) {
		heap_decrease_key(heap, index, key);
	}
}

/**
 * init dijkstra workspace
 */
static void 
__dijkstra_init(const struct Graph * g, const struct Adjacent * source, struct DijkstraResult * dr)
{
	// binary heap init
	struct Heap * Q = heap_init(g->num_vertex);
	struct Adjacent * a;
	struct HashTable * dist = hash_table_create(g->num_vertex);
	struct HashTable * previous = hash_table_create(g->num_vertex);

	// source 
	heap_insert(Q, 0, (uintptr_t)source->v.id);	// weight->id binary heap
	hash_table_set(dist, source->v.id, 0);
	hash_table_set(previous, source->v.id, undefined);

	// other vertices
	list_for_each_entry(a, &g->a_head, a_node){
		if (a->v.id != source->v.id) {
			heap_insert(Q, INT_MAX, (uintptr_t)a->v.id);
			// set inital distance to INT_MAX
			hash_table_set(dist, a->v.id, (uintptr_t)INT_MAX);
			// set initial value to undefined
			hash_table_set(previous, a->v.id, undefined);
		}
	}
	
	dr->Q = Q;
	dr->dist = dist;
	dr->previous = previous;
}

static struct DijkstraResult * 
dijkstra_run(const struct Graph * g, const struct Adjacent * source)
{
	struct DijkstraResult * dr =
		 (struct DijkstraResult *)malloc(sizeof(struct DijkstraResult));

	__dijkstra_init(g, source, dr);
	struct Heap * Q = dr->Q;
	struct HashTable * dist = dr->dist;
	struct HashTable * previous = dr->previous;

	while(!heap_is_empty(Q)) {    // The main loop
		struct Adjacent * u = graph_lookup(g, (uint32_t)HEAP_MIN_VALUE(Q));
		int dist_u = HEAP_MIN_KEY(Q);
		heap_delete_min(Q);

		if (dist_u == INT_MAX) {
			break;	
		}
	
		struct Vertex * v;
		list_for_each_entry(v, &u->v_head, v_node){
			uint32_t alt = dist_u + v->weight;
			uint32_t dist_v = (uint32_t)hash_table_get(dist, v->id);
			if (alt < dist_v) {
				hash_table_set(dist, v->id, (uintptr_t)alt);
				__dijkstra_reorder(Q, v->id, alt);
				hash_table_set(previous, v->id, (uintptr_t)u->v.id);
			}
		}
	}

	return dr;
}

static void
dijkstra_free(struct DijkstraResult * result)
{
	hash_table_destroy(result->dist);
	hash_table_destroy(result->previous);
	heap_free(result->Q);
	free(result);
}

#endif //
