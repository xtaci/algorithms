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
	class Dijkstra {
		public:
			static const int UNDEFINED = -1;
			// run dijkstra algorithm, and return the previous table
			static HashTable<int32_t, int32_t> * run(const struct Graph & g, uint32_t src_id) {
				// a binary heap
				Heap<uint32_t> Q(g.vertex_count() + g.edge_count());
				// distance hash table
				HashTable<int32_t, int32_t> dist(g.vertex_count());
				// previous vertex hash table
				HashTable<int32_t, int32_t> * previous = new HashTable<int32_t,int32_t>(g.vertex_count()); 
				// record whether the vertex is visited
				HashTable<int32_t, bool> visited(g.vertex_count()); 

				// all vertices
				Graph::Adjacent * a;
				list_for_each_entry(a, &g.list(), a_node){
					dist[a->v.id] = INT_MAX; // set inital distance to each vertex as INT_MAX
					(*previous)[a->v.id] =  UNDEFINED; // clear path to UNDEFINED
					visited[a->v.id] = false; // all vertices are not visited
				}

				// source vertex, the first vertex in Heap-Q
				Q.insert(0, src_id);
				dist[src_id] = 0;

				while(!Q.is_empty()) {    // for every un-visited vertex, try relaxing the path
					int32_t id = Q.min_value();
					Q.delete_min();		// remove u from Q
					if (visited[id]) {	// jump visited vertex
						continue;
					}

					Graph::Adjacent * u = g[id];	// the vertex to process
					int dist_u = dist[id];			// current known shortest distance to u
					visited[id] = true;	// mark the vertex as visited.

					Graph::Vertex * v;
					list_for_each_entry(v, &u->v_head, v_node){
						uint32_t alt = dist_u + v->weight;
						uint32_t dist_v = dist[v->id];
						if (alt < dist_v && !visited[v->id]) {
							dist[v->id] = alt;
							(*previous)[v->id] = u->v.id;
							Q.insert(alt, v->id);
						}
					}
				}

				return previous;
			};
	};
}

#endif //
