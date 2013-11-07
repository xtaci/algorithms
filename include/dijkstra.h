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

namespace alg {
	/**
	 * the dijkstra algorithm workspace
	 */
	class Dijkstra {
		private:
			const Graph & g; 
			Heap<uint32_t> Q;		// a binary heap
			HashTable<int32_t, int32_t> dist; 	// distance hash table
		public:
			static const int UNDEFINED = -1;
			/**
			 * init dijkstra workspace
			 */
			Dijkstra(const struct Graph & graph):g(graph),
			Q(g.vertex_count()),
			dist(g.vertex_count()) {}

			// run dijkstra algorithm, and return the previous table
			HashTable<int32_t, int32_t> * run(uint32_t src_id) {
				// previous vertex hash table
				HashTable<int32_t, int32_t> * previous = new HashTable<int32_t,int32_t>(g.vertex_count()); 	

				Q.clear();
				dist.clear();

				// source 
				Graph::Adjacent * source = g[src_id];
				Q.insert(0, source->v.id);	// weight->id binary heap
				dist[source->v.id] = 0;

				// other vertices
				Graph::Adjacent * a;
				list_for_each_entry(a, &g.list(), a_node){
					if (a->v.id != source->v.id) {
						Q.insert(INT_MAX, a->v.id);
						// set inital distance to INT_MAX
						dist[a->v.id] = INT_MAX;
						// set initial value to UNDEFINED
					}
					(*previous)[a->v.id] =  UNDEFINED;
				}

				while(!Q.is_empty()) {    // The main loop
					Graph::Adjacent * u = g[Q.min_value()];
					int dist_u = Q.min_key();
					Q.delete_min();

					if (dist_u == INT_MAX) {
						break;	
					}

					Graph::Vertex * v;
					list_for_each_entry(v, &u->v_head, v_node){
						uint32_t alt = dist_u + v->weight;
						uint32_t dist_v = dist[v->id];
						if (alt < dist_v) {
							dist[v->id] = alt;
							Q.decrease_key(v->id, alt);
							(*previous)[v->id] = u->v.id;
						}
					}
				}

				return previous;
			};
	};
}

#endif //
