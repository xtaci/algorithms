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
#include "perfect_hash.h"

#define undefined (uintptr_t)-1

struct DijkWorkspace {
	struct Heap * Q;
	struct PerfHT * dist; 
	struct PerfHT * previous; 
	uint32_t num_vertex;	
	uint32_t vertex_ids[1];
};

static inline void __dijkstra_reorder(struct Heap * heap, uint32_t id, uint32_t new_weight)
{	
	int index;
	int key = new_weight;
	if ((index=heap_find_value(heap, (uintptr_t)id))!=-1) {
		heap_decrease_key(heap, index, key);
	}
}

static inline void dijkstra_init(const struct Graph * g, const struct Adjacent * source, struct DijkWorkspace * dr)
{

	// binary heap init
	struct Heap * Q = heap_init(g->num_vertex);
	struct Adjacent * a;
	heap_insert(Q, 0, (uintptr_t)source->v.id);	// weight->id binary heap

	int i=1;
	list_for_each_entry(a, &g->a_head, a_node){
		if (source->v.id != a->v.id) {
			dr->vertex_ids[i++] = a->v.id;
			heap_insert(Q, INT_MAX, (uintptr_t)a->v.id);
		}
	}

	dr->num_vertex = g->num_vertex;
	dr->vertex_ids[0] = source->v.id;

	// hash table for id->dist , set inital distance to INT_MAX
	struct PerfHT * dist = perfect_hash_init(dr->vertex_ids, g->num_vertex);

	perfect_hash_set(dist, dr->vertex_ids[0], 0);
	for(i=1;i<dr->num_vertex;i++) {
		perfect_hash_set(dist, dr->vertex_ids[i], (uintptr_t)INT_MAX);
	}

	// hash table for node -> previous node, for trackback
	struct PerfHT * previous = perfect_hash_init(dr->vertex_ids, g->num_vertex);
	// set initial value to undefined
	for(i=0;i<dr->num_vertex;i++) {
		perfect_hash_set(previous, dr->vertex_ids[i], undefined);
	}

	dr->Q = Q;
	dr->dist = dist;
	dr->previous = previous;
}

/**
 * do the real work
 * Pseudo code from wikipedia:
	function Dijkstra(Graph, source):
		for each vertex v in Graph:                                // Initializations
			dist[v] := infinity ;                                  // Unknown distance function from 
																   // source to v
			previous[v] := undefined ;                             // Previous node in optimal path
		end for                                                    // from source
		
		dist[source] := 0 ;                                        // Distance from source to source
		Q := the set of all nodes in Graph ;                       // All nodes in the graph are
																   // unoptimized - thus are in Q
		while Q is not empty:                                      // The main loop
			u := vertex in Q with smallest distance in dist[] ;    // Start node in first case
			remove u from Q ;
			if dist[u] = infinity:
				break ;                                            // all remaining vertices are
			end if                                                 // inaccessible from source
			
			for each neighbor v of u:                              // where v has not yet been 
																   // removed from Q.
				alt := dist[u] + dist_between(u, v) ;
				if alt < dist[v]:                                  // Relax (u,v,a)
					dist[v] := alt ;
					previous[v] := u ;
					decrease-key v in Q;                           // Reorder v in the Queue
				end if
			end for
		end while
	return dist;
 */
static inline struct DijkWorkspace * dijkstra_run(const struct Graph * g, const struct Adjacent * source)
{
	struct DijkWorkspace * dr =
		 (struct DijkWorkspace *)malloc(sizeof(struct DijkWorkspace) + sizeof(uint32_t) * g->num_vertex);

	dijkstra_init(g, source, dr);
	struct Heap * Q = dr->Q;
	struct PerfHT * dist = dr->dist;
	struct PerfHT * previous = dr->previous;

	while(!heap_is_empty(Q)) {    // The main loop
		struct Adjacent * u = graph_lookup(g, (uint32_t)HEAP_MIN_VALUE(Q));
		int dist_u = HEAP_MIN_KEY(Q);
		heap_delete_min(Q);

		if (dist_u == INT_MAX){
			break;	
		}
	
		struct Vertex * v;
		list_for_each_entry(v, &u->v_head, v_node){
			uint32_t alt = dist_u + v->weight;
			uint32_t dist_v = (uint32_t)perfect_hash_get(dist, v->id);
			if (alt < dist_v) {
				perfect_hash_set(dist, v->id, (uintptr_t)alt);
				__dijkstra_reorder(Q, v->id, alt);
				perfect_hash_set(previous, v->id, (uintptr_t)u->v.id);
			}
		}
	}

	return dr;
}

#endif //
