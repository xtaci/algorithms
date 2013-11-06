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
	class Prim {
		private:
			/**
			 * Prim's Adjacent Lists, for Prim's Algorithm caculation
			 */
			struct PrimAdjacent {
				Heap<Graph::Vertex*> heap; 		// binary heap representation of weight->node
				// the top of the heap is always the minimal element
				const Graph::Vertex & v;

				PrimAdjacent(const Graph::Vertex & vertex, uint32_t num_neigh):heap(num_neigh),v(vertex) { }

				struct list_head pa_node; 
			};

			/**
			 * Prim's Graph, simplified to list.
			 */
			typedef struct list_head PrimGraph;
		private:
			PrimGraph m_pg;
		public:
			/**
			 * construct Prim's DataStrcuture by a given graph
			 */	
			Prim(const Graph & g) {
				INIT_LIST_HEAD(&m_pg);

				Graph::Adjacent * a;
				list_for_each_entry(a, &g.list(), a_node){
					add_adjacent(*a);
				}
			}

			~Prim() {
				PrimAdjacent * pa, *pan;
				list_for_each_entry_safe(pa, pan, &m_pg, pa_node){
					list_del(&pa->pa_node);
					delete pa;
				}
			}
		private:
			Prim(const Prim&);
			Prim& operator= (const Prim&);
		private:
			/**
			 * add an adjacent list to prim's graph
			 */
			void add_adjacent(const Graph::Adjacent & a) {
				PrimAdjacent * pa = new PrimAdjacent(a.vertex(), a.num_neigh);
				list_add_tail(&pa->pa_node, &m_pg);

				Graph::Vertex * v;
				list_for_each_entry(v, &a.v_head, v_node){
					pa->heap.insert(v->weight, v);  // weight->vertex
				}
			}

			/**
			 * lookup up a given id
			 * the related adjacent list is returned.
			 */ 
			PrimAdjacent * lookup(uint32_t id) const {
				PrimAdjacent * pa;
				list_for_each_entry(pa, &m_pg, pa_node){
					if (pa->v.id == id) { return pa;}
				}

				return NULL;
			}
		public:
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
			Graph * run() {
				UndirectedGraph * mst = new UndirectedGraph(); // empty set == Vnew

				// choose the first vertex as the starting point
				PrimAdjacent * pa;
				list_for_each_entry(pa, &m_pg, pa_node){ break; }
				const Graph::Vertex * v = &pa->v;
				mst->add_vertex(v->id);

				// Prim's Algorithm
				while(true) {
					int weight = INT_MAX;			// loop tmp variables
					uint32_t best_to;
					struct PrimAdjacent * best_from;

					// for each Vnew, find a new vertex in V that has minimal weight.
					Graph::Adjacent * a; 
					list_for_each_entry(a, &mst->list(), a_node){
						pa = lookup(a->v.id);
						while (!pa->heap.is_empty()) { 	// find one neighbour
							v = pa->heap.min_value(); 
							if ((*mst)[v->id]==NULL) {  // if new V appears 
								if (pa->heap.min_key() < weight) {
									weight = pa->heap.min_key();
									best_to = v->id;
									best_from = pa; 
								}
								break;
							} else {
								pa->heap.delete_min();
							}
						}
					}

					if (weight != INT_MAX) {
						// congrats , new V & E
						mst->add_vertex(best_to);
						mst->add_edge(best_from->v.id, best_to, weight);
						best_from->heap.delete_min();
					} else break;
				};

				return mst;
			}

			/**
			 * print the PrimGraph
			 */
			void print() {
				struct PrimAdjacent * pa;
				printf("Prim Graph: \n");
				list_for_each_entry(pa, &m_pg, pa_node){
					printf("%d->{", pa->v.id);
					for(uint32_t i=0;i<pa->heap.count();i++) {
						Graph::Vertex * v = pa->heap[i];
						printf("id:%d->w:%d \t", v->id, v->weight);
					}
					printf("}\n");
				}
			}
	};
}

#endif //
