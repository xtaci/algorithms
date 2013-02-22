/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 # BELLMAN-FORD ALGORITHM
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
#include "perfect_hash.h"

// define undefined previous vertex.
#define undefined (uintptr_t)-1

/**
 * workspace for bellman ford algorithm.
 */
struct BFWorkspace {
	struct PerfHT * dist; 	// hash table for distance.
	struct PerfHT * previous; 	// hash table for previous vertex
	bool has_neg_cycle;		// negative weighted cycle mark.
	uint32_t num_vertex;	// total num of vertex
	uint32_t vertex_ids[1];	// the vertex ids array.
};

/**
 * internal workspace init procedure. hash table and vertex_ids is initialized.
 */
static inline void __bellman_ford_init(const struct Graph * g, const struct Adjacent * source, struct BFWorkspace * bfw)
{
	// gather vertex ids, the source vertex id is in vertex_ids[0].
	struct Adjacent * a;

	int i=1;
	list_for_each_entry(a, &g->a_head, a_node){
		if (source->v.id != a->v.id) {
			bfw->vertex_ids[i++] = a->v.id;
		}
	}

	bfw->num_vertex = g->num_vertex;
	bfw->vertex_ids[0] = source->v.id;

	// create hash table for vertex->distance, and set the initial
	// distance to this vertex of 'INT_MAX'
	struct PerfHT * dist = perfect_hash_init(bfw->vertex_ids, g->num_vertex);

	perfect_hash_set(dist, bfw->vertex_ids[0], 0);
	for(i=1;i<bfw->num_vertex;i++) {
		perfect_hash_set(dist, bfw->vertex_ids[i], (uintptr_t)INT_MAX);
	}

	// create hash table for 'vertex' -> 'previous vertex', for trackback.
	struct PerfHT * previous = perfect_hash_init(bfw->vertex_ids, g->num_vertex);
	// set 'previous' value of each vertex to 'undefined'.
	for(i=0;i<bfw->num_vertex;i++) {
		perfect_hash_set(previous, bfw->vertex_ids[i], (uintptr_t)undefined);
	}

	bfw->dist = dist;
	bfw->previous = previous;
	bfw->has_neg_cycle = false;	// negative cycle mark set to 'false'.
}

/**
 * do the real work
 */
static inline struct BFWorkspace * bellman_ford_run(const struct Graph * g, const struct Adjacent * source)
{
	// init the workspace.
	struct BFWorkspace * bfw =
		 (struct BFWorkspace *)malloc(sizeof(struct BFWorkspace) + sizeof(uint32_t) * g->num_vertex);

	__bellman_ford_init(g, source, bfw);

	struct PerfHT * dist = bfw->dist;
	struct PerfHT * previous = bfw->previous;

	//  relax edges repeatedly	
	int i;
	for (i=0;i<bfw->num_vertex-1;i++) {    // loop |V| -1 times
		int j;

		for (j=0; j<bfw->num_vertex;j++) { // for each eage in the whole graph
			struct Adjacent * u = graph_lookup(g, bfw->vertex_ids[j]);
			struct Vertex * v;
			int32_t dist_u = (int32_t)perfect_hash_get(dist, bfw->vertex_ids[j]);

			list_for_each_entry(v, &u->v_head, v_node){ 
				int32_t dist_v = (int32_t)perfect_hash_get(dist, v->id);

				if (dist_u + v->weight < dist_v) {
					perfect_hash_set(dist, v->id, (uintptr_t)(dist_u + v->weight));
					perfect_hash_set(previous, v->id, (uintptr_t)u->v.id);
				}
			}
		}
	}

	//  check for negative-weight cycles
    for (i=0;i<bfw->num_vertex;i++) {  // for each eage in the whole graph 
		struct Adjacent * u = graph_lookup(g, bfw->vertex_ids[i]);
        struct Vertex * v;
		int32_t dist_u = (int32_t)perfect_hash_get(dist, bfw->vertex_ids[i]);

        list_for_each_entry(v, &u->v_head, v_node){
            int32_t dist_v = (int32_t)perfect_hash_get(dist, v->id);

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
