/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * EDMONS-KARP ALGORITM
 *
 * Features:
 *   In computer science and graph theory, the Edmonds–Karp algorithm is an
 * implementation of the Ford–Fulkerson method for computing the maximum flow in
 * a flow network in O(V E2) time. It is asymptotically slower than the 
 * relabel-to-front algorithm, which runs in O(V3) time, but it is often faster 
 * in practice for sparse graphs. The algorithm was first published by Yefim 
 * (Chaim) Dinic in 1970[1] and independently published by Jack Edmonds and
 * Richard Karp in 1972.[2] Dinic's algorithm includes additional techniques 
 * that reduce the running time to O(V2E). 
 * 
 * http://en.wikipedia.org/wiki/Edmonds–Karp_algorithm
 *
 ******************************************************************************/

#ifndef ALGO_EDMONDS_KARP_H__
#define ALGO_EDMONDS_KARP_H__

#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#include "directed_graph.h"
#include "hash_table.h"
#include "queue.h"
#include "2darray.h" 

namespace alg {
	/**
	 * Edmonds Karp maximal flow class 
	 */
	class EdmondsKarp {
		private:
			const Graph & g;
			Array2D<int32_t> m_residual;	// residual network , 2d array
			HashTable<int32_t, int32_t> m_pre; 				// pre node of current node 
			bool * m_visits; 			// mark whether current node is visited

			HashTable<int32_t, int32_t> m_map;		// vertex id to ordinary row/col number mapping
			HashTable<int32_t, int32_t> m_rmap;	// reverse mapping of map.

		public:
			EdmondsKarp(const Graph & graph): g(graph),
			m_residual(g.vertex_count(), g.vertex_count()), 
			m_pre(g.vertex_count()),
			m_map(g.vertex_count()), m_rmap(g.vertex_count()) {
				m_visits = new bool[g.vertex_count()];
				// map vertex ids to ordinal row/col number, and reverse mapping.
				// for residual network, using sequential order
				Graph::Adjacent * a;
				int id=0;
				list_for_each_entry(a, &g.list(), a_node){
					m_map[a->v.id] = id;
					m_rmap[id] = a->v.id;
					id++;
				}

				// init residual network
				m_residual.clear(0);

				list_for_each_entry(a, &g.list(), a_node){
					Graph::Vertex * v;
					list_for_each_entry(v, &a->v_head, v_node){
						int from = m_map[a->v.id];
						int to = m_map[v->id];
						m_residual(from, to) = v->weight;
					}
				}
			}

			~EdmondsKarp() {
				delete [] m_visits;
			}

			/**
			 * edmonds karp algorithm for maximal flow 
			 * returns the maxflow from src to sink
			 */
			uint32_t run(int32_t src, int32_t sink) {
				// find augument path repeatedly.
				int32_t _src = m_map[src];
				int32_t _sink = m_map[sink];

				uint32_t maxflow = 0;

				while(find_path(_src, _sink)) {
					int delta = INT_MAX;	

					// find minimal delta
					int i;	
					for (i=_sink;i!=_src;i= m_pre[i]) {
						delta = Min(delta, m_residual(m_pre[i],i));
					}

					// for each edge, change residual network
					for (i=_sink; i!=_src;i= m_pre[i]) {
						m_residual(m_pre[i],i) -= delta;
						m_residual(i,m_pre[i]) += delta;
					}

					maxflow += delta;
				}

				return maxflow;
			}

			inline const Array2D<int> & residual() const { return m_residual;}
			inline const HashTable<int32_t, int32_t> & map() const { return m_map;}
			inline const HashTable<int32_t, int32_t> & rmap() const { return m_rmap;}

		private:
			/**
			 * find a augument path. using breadth first search
			 */
			bool find_path(int32_t _src, int32_t _sink) {
				Queue<int32_t> Q(g.vertex_count()); 

				// clear visit flag & path
				memset(m_visits, false, sizeof(bool) * g.vertex_count());

				// src setting
				m_pre[_src] = _src;	
				m_visits[_src] = true;
				Q.enqueue(_src);

				while(!Q.is_empty()) {
					int p = Q.front();
					Q.dequeue();

					for (uint32_t i=0;i< g.vertex_count();i++) {
						if (m_residual(p,i) >0 && !m_visits[i]) {
							m_pre[i] = p;
							m_visits[i] = true;

							if (i==uint32_t(_sink)) {		// nice, we've got to sink point.
								return true;
							}
							Q.enqueue(i);
						}
					}
				}

				return false;
			}
	};
}

#endif //
