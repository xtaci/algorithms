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

#define UNDEFINED -1

namespace alg 
{
	/**
	 * the dijkstra algorithm workspace
	 */
	class Dijkstra {
	private:
		Heap<uint32_t> * Q;		// a binary heap
		HashTable<uint32_t> * dist; 	// distance hash table
		HashTable<int32_t> * previous; 	// previous vertex hash table
		const Graph * graph; 
	private:
		/**
		 * reorder operation i.e. heap decrease key operation.
	 	*/
		inline void reorder(uint32_t id, uint32_t new_weight) {	
			int index;
			int key = new_weight;
			if ((index=Q->find_value(id))!=-1) {
				Q->decrease_key(index, key);
			}
		};

	public:
		/**
		 * init dijkstra workspace
		 */
		Dijkstra(const struct Graph * g, uint32_t src_id) {
			// binary heap init
			Q = new Heap<uint32_t>(g->num_vertex);
			dist = new HashTable<uint32_t>(g->num_vertex);
			previous = new HashTable<int32_t>(g->num_vertex);
			graph = g;

			// source 
			struct Adjacent * source = graph_lookup(g, src_id);
			Q->insert(0, source->v.id);	// weight->id binary heap
			(*dist)[source->v.id] = 0;
			(*previous)[source->v.id] = UNDEFINED;

			// other vertices
			struct Adjacent * a;
			list_for_each_entry(a, &g->a_head, a_node){
				if (a->v.id != source->v.id) {
					Q->insert(INT_MAX, a->v.id);
					// set inital distance to INT_MAX
					(*dist)[a->v.id] = INT_MAX;
					// set initial value to UNDEFINED
					(*previous)[a->v.id] =  UNDEFINED;
				}
			}
		};
	
		/**
		 * Destructor
		 */	
		~Dijkstra() {
			delete Q;
			delete dist;
			delete previous;
		};

		// run dijkstra algorithm, and return the previous table
		const HashTable<int32_t> & run() {
			while(!Q->is_empty()) {    // The main loop
				struct Adjacent * u = graph_lookup(graph, Q->min_value());
				int dist_u = Q->min_key();
				Q->delete_min();

				printf("min value %d\n", Q->min_value());
				if (dist_u == INT_MAX) {
					break;	
				}
			
				struct Vertex * v;
				list_for_each_entry(v, &u->v_head, v_node){
					printf("id %d\n", v->id);
					uint32_t alt = dist_u + v->weight;
					uint32_t dist_v = (*dist)[v->id];
					if (alt < dist_v) {
						(*dist)[v->id] = alt;
						reorder(v->id, alt);
						(*previous)[v->id] = u->v.id;
					}
				}
			}
	
			return *previous;
		};
	};
}

#endif //
