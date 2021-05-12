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

#ifndef ALGO_BELLMAN_FORD_H__
#define ALGO_BELLMAN_FORD_H__

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

#include "directed_graph.h"
#include "hash_table.h"

// define UNDEFINED previous vertex.
#define UNDEFINED -1

namespace alg {
	class BellmanFord {
		private:		
			HashTable<int32_t, int32_t> dist; 		// hash table for distance.
			bool has_neg_cycle;				// negative weighted cycle mark.
			const Graph & g;	
		public:
			BellmanFord(const Graph & graph):
				dist(graph.vertex_count()),g(graph) { }

			/**
			 * Bellman-Ford algorithm
			 */
			HashTable<int32_t, int32_t> * run(uint32_t source) {
				// hash table for previous vertex
				HashTable<int32_t, int32_t> *  previous = new HashTable<int32_t, int32_t>(g.vertex_count()); 
				// source vertex
				dist[source] = 0;

				// other vertices
				Graph::Adjacent * a;
				list_for_each_entry(a, &g.list(), a_node){
					if (source != a->v.id) {
						dist[a->v.id] = INT_MAX;
					}
					(*previous)[a->v.id] = UNDEFINED;
				}

				has_neg_cycle = false;	// negative cycle mark set to 'false'.

				//  relax edges repeatedly	
				Graph::Adjacent * u;
				for (uint32_t i=0;i<g.vertex_count()-1;i++) {    // loop |V| -1 times
					list_for_each_entry(u, &g.list(), a_node){ // for each eage(u,v) in edges
						int32_t dist_u = dist[u->v.id];

						Graph::Vertex * v;
						list_for_each_entry(v, &u->v_head, v_node){ 
							int32_t dist_v = dist[v->id];

							if (dist_u + v->weight < dist_v) {
								dist[v->id] = dist_u + v->weight;
								(*previous)[v->id] = u->v.id;
							}
						}
					}
				}

				//  check for negative-weight cycles
				list_for_each_entry(u, &g.list(), a_node) {
					int32_t dist_u = dist[u->v.id];

					Graph::Vertex * v;
					list_for_each_entry(v, &u->v_head, v_node){
						int32_t dist_v = dist[v->id];

						if (dist_u + v->weight < dist_v) {
							has_neg_cycle = true;	// graph contains a negative-weight cycle
							return previous;
						}
					}	
				}

				return previous;	
			}

			inline bool has_negative_cycle() { return has_neg_cycle; }
	};
}

#endif //
