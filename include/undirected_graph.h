/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * UNDIRECTED GRAPH
 *
 * Features:
 * 1. Adjacency List Implementation
 *
 * http://en.wikipedia.org/wiki/Undirected_graph
 *
 ******************************************************************************/

#ifndef ALGO_UNDIRECTED_GRAPH_H__
#define ALGO_UNDIRECTED_GRAPH_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include "graph_defs.h"
#include "double_linked_list.h"

namespace alg {
	class UndirectedGraph:public Graph {
		private:
			/**
			 * delete a vertex from adjacent lists
			 */
			void delete_me(Adjacent * a) {
				Vertex * v,* vn;

				// for each connected-vertex
				list_for_each_entry_safe(v, vn, &a->v_head, v_node){
					Adjacent * neigh = (*this)[v->id];
					neigh->delete_vertex(a->v.id);
					num_edges--;
				}
			}
		public:
			/**
			 * create a new vertex and add to the graph, with specified id.
			 */
			inline bool add_vertex(uint32_t id) {
				if ((*this)[id]!=NULL) return false;

				// new empty adjacent list
				Adjacent * a = new Adjacent(id);
				INIT_LIST_HEAD(&a->v_head);
				list_add_tail(&a->a_node, &a_head);
				num_vertex++;

				return true;
			}

			/**
			 * delete a vertex with specified id 
			 */
			void delete_vertex(uint32_t id) {
				Adjacent * a = (*this)[id];
				if (a==NULL) return;
				delete_me(a);	

				// delete adjacent list itself.
				num_vertex--;
				list_del(&a->a_node);
				delete a;
			}

			/**
			 * add an edge for x<->y
			 */
			bool add_edge(uint32_t x, uint32_t y, int32_t weight) {
				struct Adjacent * a1 = (*this)[x];
				struct Adjacent * a2 = (*this)[y];

				if (a1==NULL || a2==NULL) return false;
				if (is_adjacent(a1, a2)) return false;

				// create new vertex & add to adjacent list
				Vertex * n = new Vertex(y);
				n->weight = weight;
				list_add_tail(&n->v_node, &a1->v_head);

				n = new Vertex(x);
				n->weight = weight;
				list_add_tail(&n->v_node, &a2->v_head);

				num_edges++;
				a1->num_neigh++;
				a2->num_neigh++;

				return true;
			}

			/**
			 * delete an edge for x<->y
			 */
			void delete_edge(uint32_t x, uint32_t y) {
				Adjacent * a1 = (*this)[x];
				Adjacent * a2 = (*this)[y];
				if (a1==NULL || a2==NULL) return ;
				if (!is_adjacent(a1, a2)) return ;

				Vertex * v, *n;
				// find x->.....y...	
				list_for_each_entry_safe(v, n, &a1->v_head, v_node){
					if (v->id == y) {
						list_del(&v->v_node);
						delete(v);
						num_edges--;
						a1->num_neigh--;
					}
				}

				// find y->.....x...	
				list_for_each_entry_safe(v, n, &a2->v_head, v_node){
					if (v->id == x) {
						list_del(&v->v_node);
						delete(v);
						a2->num_neigh--;
					}
				}
			}
			/**
			 * randomly generate a graph, for test purpose
			 * start from 1
			 */
			static UndirectedGraph * randgraph(int nvertex) {
				UndirectedGraph * g = new UndirectedGraph;
				int i;	

				for(i=1;i<=nvertex;i++) {
					g->add_vertex(i);
				}

				// random connect
				for(i=1;i<=nvertex;i++) {
					int j;
					for(j=i+1;j<nvertex;j++) {
						int dice = rand()%5;
						if (dice == 0) {  // chance 20%
							int w = rand()%100+1;
							g->add_edge(i, j, w);
						}
					}
				}


				return g;
			}
	};
}

#endif //
