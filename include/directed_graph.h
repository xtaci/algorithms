/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * DIRECTED GRAPH 
 *
 * Features:
 * 1. Adjacency List Implementation
 *
 * http://en.wikipedia.org/wiki/Directed_graph
 *
 ******************************************************************************/

#ifndef ALGO_DIRECTED_GRAPH_H__
#define ALGO_DIRECTED_GRAPH_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#include "graph_defs.h"
#include "double_linked_list.h"

namespace alg {
	class DirectedGraph:public Graph {
		private:
			/**
			 * delete a vertex from adjacent lists
			 */
			void delete_me(uint32_t id) {
				// delete every connection, iterator through every adjacent list
				Adjacent * adj;
				list_for_each_entry(adj, &a_head, a_node){
					if (adj->v.id != id) {
						if((*adj)[id]!=NULL) {	// if connected to id
							adj->delete_vertex(id);
							num_edges--;
						}
					}
				}
			}
		public:
			/**
			 * randomly generate a graph, for test purpose
			 */
			static DirectedGraph * randgraph(int nvertex) {
				DirectedGraph * g = new DirectedGraph;
				int i;	

				for(i=0;i<nvertex;i++) {
					g->add_vertex(i);
				}

				// random connect
				for(i=0;i<nvertex;i++) {
					int j;
					for(j=i+1;j<nvertex;j++) {
						// 33% connection
						int dice = rand()%3;
						if (dice == 0) {  
							int w = rand()%100;
							g->add_edge(i, j, w);
						}
					}
				}
				return g;
			}

		public:
			/**
			 * delete a vertex with specified id 
			 */
			void delete_vertex(uint32_t id) {
				Adjacent * a = (*this)[id];
				if (a==NULL) return;
				delete_me(id);	
				// delete adjacent list itself.
				num_vertex--;
				num_edges -= a->num_neigh;
				list_del(&a->a_node);
				delete a;
			}

			/**
			 * create a new vertex and add to the graph, with specified id.
			 */
			bool add_vertex(uint32_t id) {
				if ((*this)[id]!=NULL) return false;

				// new empty adjacent list
				Adjacent * a = new Adjacent(id); 
				list_add_tail(&a->a_node, &a_head);
				num_vertex++;

				return true;
			}

			/**
			 * add an edge for x -> y
			 */
			bool add_edge(uint32_t x, uint32_t y, int32_t weight) {
				struct Adjacent * a1 = (*this)[x];
				struct Adjacent * a2 = (*this)[y];

				// make sure both vertex exists & not connected from x->y
				if (a1==NULL || a2==NULL) return false;
				if (is_adjacent(a1, a2)) return false;

				// create new vertex & add to adjacent list
				Vertex * n = new Vertex(y);
				n->weight = weight;
				list_add_tail(&n->v_node, &a1->v_head);

				num_edges++;
				a1->num_neigh++;

				return true;
			}

			/**
			 * delete an edge for x -> y
			 */
			void delete_edge(uint32_t x, uint32_t y) {
				struct Adjacent * a1 = (*this)[x];
				struct Adjacent * a2 = (*this)[y];
				if (a1==NULL || a2==NULL) return ;
				if (!is_adjacent(a1, a2)) return ;

				Vertex * v, *n;
				// find y in adjacent list of x
				list_for_each_entry_safe(v, n, &a1->v_head, v_node){
					if (v->id == y) {
						list_del(&v->v_node);
						delete v;
						num_edges--;
						a1->num_neigh--;
					}
				}
			}

			/**
			 * create the transpose of a directed-graph
			 */
			DirectedGraph * transpose() {
				DirectedGraph * trans = new DirectedGraph;
				Adjacent * a;
				list_for_each_entry(a, &a_head, a_node){
					trans->add_vertex(a->v.id);
					Vertex * v;
					list_for_each_entry(v, &a->v_head, v_node){
						trans->add_vertex(v->id);
						trans->add_edge(v->id, a->v.id, v->weight);
					}
				}	

				return trans;
			}
	};
}

#endif //
