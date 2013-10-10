/*
 * Push-Relabel algorithm
 *
 * Features: This maxflow algorithm runs in O(V2 E) time, faster than Edmonds-Karp in theory.
 * But the funny thing is, in practice, this method is often 5 times slower than Edmonds-Karp.
 * You can test it by changing NVERTEX in push_relabel.cpp.
 *
 * http://en.wikipedia.org/wiki/Push%E2%80%93relabel_maximum_flow_algorithm
 *
 * */

#ifndef __PUSH_RELABEL_H__
#define __PUSH_RELABEL_H__

#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#include "directed_graph.h"
#include "hash_table.h"
#include "2darray.h"

namespace alg
{
	class PushRelabel	
	{
	protected:
		const Graph & g;
		DirectedGraph * possible_residual_edge;	// record possible residual edges

		Array2D<int> m_residual;

		HashTable<uint32_t> m_map;
		HashTable<uint32_t> m_rmap;

		HashTable<int> e;	//excess flow
		HashTable<int> h;	//value of height function
		
	public:
		PushRelabel(const Graph & graph):
			g(graph),
			m_residual(g.vertex_count(), g.vertex_count()),
			m_map(g.vertex_count()), m_rmap(g.vertex_count()),
					e(g.vertex_count()), h(g.vertex_count())
		{
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

		~PushRelabel()
		{
			delete possible_residual_edge;
		}

		void initialize_preflow(uint32_t src)
		{
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

		void push(uint32_t src, uint32_t dst)
		{
			//c f (u, v) = c(u, v) - preflow(u, v)
			int from = m_map[src], to = m_map[dst];

			int delta = Min(e[from], m_residual(from, to));
			m_residual(from, to) -= delta;
			m_residual(to, from) += delta;
			e[from] -= delta;
			e[to] += delta;
		}

		void relabel(uint32_t u, int height)
		{
			int from = m_map[u];
			h[from] = height + 1;
		}

		void relabel(uint32_t u)
		{
			int min_height = INT_MAX;
			int from = m_map[u];
			Graph::Adjacent * a = (* possible_residual_edge)[from];
			Graph::Vertex * v;
			
			list_for_each_entry(v, &a->v_head, v_node){
				int to = v->id;
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

		uint32_t run(uint32_t src, uint32_t sink)
		{
			initialize_preflow(src);

			bool overflow = true;
			while (overflow){
				overflow = false;
				// source point and sink point are not overflow-point by definition.
				for (uint32_t i=1; i<g.vertex_count()-1; i++)
				{
					int from = i;
					int id_from = m_rmap[from];
					if (e[from] > 0)
					{
						overflow = true;
						bool need_relabel = true, residual_edge = false;
						int min_height = INT_MAX;
					
						Graph::Adjacent * cur = (* possible_residual_edge)[from];
						Graph::Vertex * v;
						list_for_each_entry(v, &cur->v_head, v_node){
							int to = v->id;
							if (m_residual(from, to) > 0){
								residual_edge = true;
								min_height = Min(min_height, h[to]);
								if (h[from] > h[to])
								{
									need_relabel = false;
									if (h[from] == h[to] + 1){
										int id_to = m_rmap[to];
										push(id_from, id_to);
									}
								}
							}
						}
						if (need_relabel && residual_edge){
							relabel(id_from, min_height);
						}
					}
				}
			}

			int maxflow = e[g.vertex_count()-1];	// The value of maxflow is equal to e[sink].

			return maxflow;
		}

		inline const Array2D<int> & residual() const { return m_residual; }
		inline const HashTable<uint32_t> & map() const {return m_map; }
		inline const HashTable<uint32_t> & rmap() const { return m_rmap; }
		inline const HashTable<int> & excess() const { return e; }
		inline const HashTable<int> & height() const { return h; }
	};
}

#endif
