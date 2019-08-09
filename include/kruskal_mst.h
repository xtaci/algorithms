/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _
 * /--\ | (_| (_) |  |  |_ | | | | | _>
 *         _|
 *
 * Kruskal'S ALGORITHM -- MINIMUM SPANNING TREE
 *
 * Features:
 *
 * Kruskal's algorithm is a greedy algorithm in graph theory that finds a 
 * minimum spanning tree for a connected weighted graph.
 * This means it finds a subset of the edges that forms a tree that includes 
 * every vertex, where the total weight of all the edges in the tree is minimized. 
 * If the graph is not connected, then it finds a minimum spanning forest 
 * (a minimum spanning tree for each connected component).
 *
 * This algorithm first appeared in :
 *     Proceedings of the American Mathematical Society, pp. 48–50 in 1956,
 * and was written by Joseph Kruskal.
 *
 * http://en.wikipedia.org/wiki/Kruskal's_algorithm
 *
 * By Contibutor:xmuliang
 ******************************************************************************/

#ifndef ALGO_KRUSKAL_MST_H__
#define ALGO_KRUSKAL_MST_H__

#include <stdio.h>
#include <stdlib.h>
#include "undirected_graph.h"
#include "double_linked_list.h"
#include "heap.h"

namespace alg {
	class Kruskal {
		private:
			/**
			 * Kruskal's Adjacent Lists, for Kruskal's Algorithm caculation
			 */
			struct KruskalAdjacent {
				Heap<Graph::Vertex*> heap; 		// binary heap representation of weight->node
				// the top of the heap is always the minimal element
				const Graph::Vertex & v;

				KruskalAdjacent(const Graph::Vertex & vertex, uint32_t num_neigh):heap(num_neigh),v(vertex) { }

				struct list_head pa_node;
			};

			/**
			 * Kruskal's Graph, simplified to list.
			 */
			typedef struct list_head KruskalGraph;
		private:
			KruskalGraph m_pg;
			uint32_t num_vertex;
		public:
			/**
			 * construct Kruskal's DataStrcuture by a given graph
			 */
			Kruskal(const Graph & g) {
				INIT_LIST_HEAD(&m_pg);

				Graph::Adjacent * a;
				list_for_each_entry(a, &g.list(), a_node){
					add_adjacent(*a);
				}
				this->num_vertex=g.vertex_count();
			}

			~Kruskal() {
				KruskalAdjacent * pa, *pan;
				list_for_each_entry_safe(pa, pan, &m_pg, pa_node){
					list_del(&pa->pa_node);
					delete pa;
				}
			}
		private:
			Kruskal(const Kruskal&);
			Kruskal& operator= (const Kruskal&);
		private:
			/**
			 * add an adjacent list to Kruskal's graph
			 */
			void add_adjacent(const Graph::Adjacent & a) {
				KruskalAdjacent * pa = new KruskalAdjacent(a.vertex(), a.num_neigh);
				list_add_tail(&pa->pa_node, &m_pg);

				Graph::Vertex * v;
				list_for_each_entry(v, &a.v_head, v_node){
					pa->heap.push(v->weight, v);  // weight->vertex
				}
			}

			/**
			 * lookup up a given id
			 * the related adjacent list is returned.
			 */
			KruskalAdjacent * lookup(uint32_t id) const {
				KruskalAdjacent * pa;
				list_for_each_entry(pa, &m_pg, pa_node){
					if (pa->v.id == id) { return pa;}
				}

				return NULL;
			}
		public:
			/**
			 * Kruskal's Algorithm.
			 *
			 * Input: A non-empty connected weighted graph with vertices V and edges E
			 *        (the weights can be negative).
			 *
			 * Initialize: Enew = {}
			 *
			 * Repeat until edges = V-1:
			 *   Choose an edge {u, v} with minimal weight and promise that two nodes come from different set
			 *
			 * Output: Vnew and Enew describe a minimal spanning tree
			 */
			Graph * run() {
				UndirectedGraph * mst = new UndirectedGraph(); // empty Grapph

				uint32_t mark[num_vertex];//    mark the different set
				for(uint32_t i=0;i<num_vertex;i++)
					mark[i]=i;            //    initialize the mark array with the unique value

				const Graph::Vertex * v;
				KruskalAdjacent * pa;
				uint32_t flag=0;    //record the edge to be added into the mst
				uint32_t total_nodes=num_vertex;    //nodes of the Kruskal

				while(true) {
					int weight = INT_MAX;
					uint32_t best_to;
					struct KruskalAdjacent * best_from;

					// choose the smallest edge from the original graph
					list_for_each_entry(pa, &m_pg, pa_node){
						if(!pa->heap.is_empty()&&pa->heap.min_key()<weight) {
							weight = pa->heap.min_key();
							v = pa->heap.min_value();
							best_to = v->id;
							best_from = pa;
						}
					}

					// loop until the chosen edges to total_nodes-1
					if (flag<(total_nodes-1)&&(weight != INT_MAX)) {
						// if the node not been added,construct it
						if((*mst)[best_from->v.id]==NULL) {
							mst->add_vertex(best_from->v.id);
						}

						if((*mst)[best_to]==NULL) {
							mst->add_vertex(best_to);
						}

						// two nodes must belongs to set,to keep uncircle
						if(mark[best_from->v.id]!=mark[best_to]) {
							mst->add_edge(best_from->v.id, best_to, weight);

							uint32_t tmp=mark[best_to];
							for(uint32_t i=0;i<num_vertex;i++) {
								if(mark[i]==tmp)
									mark[i]=mark[best_from->v.id];
							}
							flag++;
						}

						best_from->heap.pop();
						lookup(best_to)->heap.pop();
					} else break;
				}

				return mst;
			}

			/**
			 * print the KruskalGraph
			 */
			void print() {
				struct KruskalAdjacent * pa;
				printf("Kruskal Graph: \n");
				list_for_each_entry(pa, &m_pg, pa_node){
					printf("%d->{", pa->v.id);
					for(uint32_t i=0;i<pa->heap.count();i++) {
						Graph::Vertex * v = pa->heap.m_heap[i].data;
						printf("id:%d->w:%d \t", v->id, v->weight);
					}
					printf("}\n");
				}
			}
	};
}

#endif //

