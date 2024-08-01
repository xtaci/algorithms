/*
 * Relabel-To-Front algorithm
 *
 * Features: Relabel-to-front maxflow algorithm's upper bound is O(V3), faster than Edmonds-Karp in theory. Relabel-to-front algorithm is a kind of push-relabel algorithm using FIFO heuristic.
 * But the funny thing is, in practice, this method is much slower than Edmonds-Karp.
 * You can test it by running relabel_to_front.cpp.
 *
 * http://en.wikipedia.org/wiki/Push%E2%80%93relabel_maximum_flow_algorithm
 *
 * */

#ifndef ALGO_RELABEL_TO_FRONT_H__
#define ALGO_RELABEL_TO_FRONT_H__

#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#include "directed_graph.h"
#include "hash_table.h"
#include "2darray.h"

namespace alg {
	class RelabelToFront	{
	private:
		const Graph & g;
		DirectedGraph * possible_residual_edge;	// record possible residual edges

		Array2D<int> m_residual;

		HashTable<uint32_t, uint32_t> m_map;
		HashTable<uint32_t, uint32_t> m_rmap;

		HashTable<uint32_t, int> e;	//excess flow
		HashTable<uint32_t, int> h;	//value of height function
		
	public:
		RelabelToFront(const Graph & graph):
			g(graph),
			m_residual(g.vertex_count(), g.vertex_count()),
			m_map(g.vertex_count()), m_rmap(g.vertex_count()),
					e(g.vertex_count()), h(g.vertex_count()) {
			Graph::Adjacent * a;
			int id=0;
			list_for_each_entry(a, &g.list(), a_node){
				m_map[a->v.id] = id;
				m_rmap[id] = a->v.id;
				id++;
			}

			m_residual.clear(0);
			
			possible_residual_edge = new DirectedGraph;
			for (uint32_t i=0; i<g.vertex_count(); i++){
				possible_residual_edge->add_vertex(i);
			}

			list_for_each_entry(a, &g.list(), a_node){
				Graph::Vertex *v;
				list_for_each_entry(v, &a->v_head, v_node){
					int from = m_map[a->v.id];
					int to = m_map[v->id];
					m_residual(from, to) = v->weight;

					possible_residual_edge->add_edge(from, to, 0);
					possible_residual_edge->add_edge(to, from, 0);
				}
			}
		}

		~RelabelToFront() {
			delete possible_residual_edge;
		}

		void initialize_preflow(uint32_t src) {
			Graph::Adjacent * a;
			list_for_each_entry(a, &g.list(), a_node){
				h[m_map[a->v.id]] = 0;
				e[m_map[a->v.id]] = 0;
			}

			int _src = m_map[src];
			h[_src] = g.vertex_count();
		
			Graph::Vertex * v;
			a = g[src];
			list_for_each_entry(v, &a->v_head, v_node){
				int from = m_map[src];
				int to = m_map[v->id];
				m_residual(from, to) = 0;
				m_residual(to, from) += v->weight;
				e[from] -= v->weight;
				e[to] = v->weight;
			}
		}

		void push(int from, int to) {
			int delta = Min(e[from], m_residual(from, to));
			m_residual(from, to) -= delta;
			m_residual(to, from) += delta;
			e[from] -= delta;
			e[to] += delta;
		}

		void relabel(int from, int height) {
			h[from] = height + 1;
		}

		void relabel(int from) {
			int min_height = INT_MAX;
			Graph::Adjacent * a = (* possible_residual_edge)[from];
			Graph::Vertex * v;
			
			list_for_each_entry(v, &a->v_head, v_node){
				int id_to = v->id;
				int to = m_map[id_to];
				if (m_residual(from, to) > 0)
				{
					min_height = Min(min_height, h[to]);
				}
				else if (m_residual(from, to) == 0)
					;
				else
					printf("Negtive edge in residual network. Error!\n");
			}
			h[from] = min_height + 1;
		}

		void discharge(int from) {
			if (e[from] <= 0){
				return;
			}

			Graph::Adjacent * a = (* possible_residual_edge)[from];
			Graph::Vertex * current;
			bool overflow = true;

			while(overflow)
			{
				int to;
				
				list_for_each_entry(current, &a->v_head, v_node){
					to = m_map[current->id];
					if (m_residual(from, to) > 0 && h[from] == h[to] + 1){
						push(from, to);
						if (e[from] <= 0){
							overflow = false;
							break;
						}
					}
				}
				if (overflow == true){
					relabel(from);
				}
			}
		}

		int run(uint32_t src, uint32_t sink) {
			initialize_preflow(src);
			
		    DirectedGraph * VertexList = new DirectedGraph;
			Graph::Adjacent * a;

			list_for_each_entry(a, &g.list(), a_node){
				if (a->v.id != src && a->v.id != sink){
					VertexList->add_vertex(a->v.id);
				}
			}

			list_for_each_entry(a, &(*VertexList).list(), a_node){
				int from = m_map[a->v.id];
				int old_height = h[from];

				discharge(from);
				if (h[from] > old_height){
					list_move(&a->a_node, const_cast<struct list_head *>(&(*VertexList).list()));
				}
			}

			delete VertexList;
			
			int maxflow = e[g.vertex_count()-1];

			return maxflow;
		}

		/*	
		 * This function implemented push-relabel algorithm in a naive way. But it's not push-to-front.
		 */
		int run_push_relabel(uint32_t src, uint32_t sink) {
			initialize_preflow(src);

			bool overflow = true;
			while (overflow){
				overflow = false;
				// source point and sink point are not overflow-point by definition.
				for (uint32_t i=1; i<g.vertex_count()-1; i++) {
					int from = i;
					if (e[from] > 0) {
						overflow = true;
						bool need_relabel = true, residual_edge = false;
						int min_height = INT_MAX;
					
						Graph::Adjacent * cur = (* possible_residual_edge)[from];
						Graph::Vertex * v;
						list_for_each_entry(v, &cur->v_head, v_node){
							int id_to = v->id;
							int to = m_map[id_to];
							if (m_residual(from, to) > 0){
								residual_edge = true;
								min_height = Min(min_height, h[to]);
								if (h[from] > h[to])
								{
									need_relabel = false;
									if (h[from] == h[to] + 1){
										push(from, to);
									}
								}
							}
						}
						if (need_relabel && residual_edge){
							relabel(from, min_height);
						}
					}
				}
			}

			int maxflow = e[g.vertex_count()-1];	// The value of maxflow is equal to e[sink].

			return maxflow;
		}

		inline const Array2D<int> & residual() const { return m_residual; }
		inline const HashTable<uint32_t, uint32_t> & map() const {return m_map; }
		inline const HashTable<uint32_t, uint32_t> & rmap() const { return m_rmap; }
		inline const HashTable<uint32_t, int> & excess() const { return e; }
		inline const HashTable<uint32_t, int> & height() const { return h; }
	};
}

#endif
