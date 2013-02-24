/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * BELLMAN-FORD ALGORITHM
 *
 *   The Bellman–Ford algorithm computes single-source shortest paths in a
 * weighted digraph. For graphs with only non-negative edge weights, the faster
 * Dijkstra's algorithm also solves the problem. Thus, Bellman–Ford is used
 * primarily for graphs with negative edge weights. The algorithm is named after
 * its developers, Richard Bellman and Lester Ford, Jr.
 *
 * procedure BellmanFord(list vertices, list edges, vertex source)
 *   // This implementation takes in a graph, represented as lists of vertices
 *   // and edges, and modifies the vertices so that their distance and
 *   // predecessor attributes store the shortest paths.
 *
 *   // Step 1: initialize graph
 *   for each vertex v in vertices:
 *       if v is source then v.distance := 0
 *       else v.distance := infinity
 *       v.predecessor := null
 *
 *   // Step 2: relax edges repeatedly
 *   for i from 1 to size(vertices)-1:
 *       for each edge uv in edges: // uv is the edge from u to v
 *           u := uv.source
 *           v := uv.destination
 *           if u.distance + uv.weight < v.distance:
 *               v.distance := u.distance + uv.weight
 *               v.predecessor := u
 *
 *   // Step 3: check for negative-weight cycles
 *   for each edge uv in edges:
 *       u := uv.source
 *       v := uv.destination
 *       if u.distance + uv.weight < v.distance:
 *           error "Graph contains a negative-weight cycle"
 * 
 * http://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm
 * 
 ******************************************************************************/

#ifndef __BELLMAN_FORD_H__
#define __BELLMAN_FORD_H__

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

#include "heap.h"
#include "directed_graph.h"
#include "hash_table.h"

// define undefined previous vertex.
#define undefined (uintptr_t)-1

/**
 * workspace for bellman ford algorithm.
 */
struct BFResult {
	struct HashTable * dist; 	// hash table for distance.
	struct HashTable * previous; 	// hash table for previous vertex
	bool has_neg_cycle;		// negative weighted cycle mark.
};

/**
 * internal workspace init procedure. hash table and vertex_ids is initialized.
 */
static void 
__bellman_ford_init(const struct Graph * g, const struct Adjacent * source, struct BFResult * bfw)
{
	struct HashTable * dist = hash_table_create(g->num_vertex);
	struct HashTable * previous = hash_table_create(g->num_vertex);
	struct Adjacent * a;

	// source vertex
	hash_table_set(dist, source->v.id, 0);

	// other vertices
	list_for_each_entry(a, &g->a_head, a_node){
		if (source->v.id != a->v.id) {
			hash_table_set(dist, a->v.id, (uintptr_t)INT_MAX);
		}
		hash_table_set(previous, a->v.id, (uintptr_t)undefined);
	}

	bfw->dist = dist;
	bfw->previous = previous;
	bfw->has_neg_cycle = false;	// negative cycle mark set to 'false'.
}

/**
 * do the real work
 */
static struct BFResult * 
bellman_ford_run(const struct Graph * g, const struct Adjacent * source)
{
	// init the workspace.
	struct BFResult * bfw =
		 (struct BFResult *)malloc(sizeof(struct BFResult));

	__bellman_ford_init(g, source, bfw);

	struct HashTable * dist = bfw->dist;
	struct HashTable * previous = bfw->previous;

	//  relax edges repeatedly	
	int i;
	for (i=0;i<g->num_vertex-1;i++) {    // loop |V| -1 times
		struct Adjacent * u;
		list_for_each_entry(u, &g->a_head, a_node){ // for each eage(u,v) in edges
			int32_t dist_u = (int32_t)hash_table_get(dist, u->v.id);

			struct Vertex * v;
			list_for_each_entry(v, &u->v_head, v_node){ 
				int32_t dist_v = (int32_t)hash_table_get(dist, v->id);

				if (dist_u + v->weight < dist_v) {
					hash_table_set(dist, v->id, (uintptr_t)(dist_u + v->weight));
					hash_table_set(previous, v->id, (uintptr_t)u->v.id);
				}
			}
		}
	}

	//  check for negative-weight cycles
	struct Adjacent * u;
	list_for_each_entry(u, &g->a_head, a_node) {
		int32_t dist_u = (int32_t)hash_table_get(dist, u->v.id);

		struct Vertex * v;
		list_for_each_entry(v, &u->v_head, v_node){
			int32_t dist_v = (int32_t)hash_table_get(dist, v->id);

			if (dist_u + v->weight < dist_v) {
				bfw->has_neg_cycle = true;	// graph contains a negative-weight cycle
				goto neg_cycle_found;
			}
		}	
	}

neg_cycle_found:

	return bfw;
}

#endif //
