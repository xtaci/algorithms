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

#ifndef __EDMONDS_KARP_H__
#define __EDMONDS_KARP_H__

#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#include "directed_graph.h"
#include "hash_table.h"
#include "queue.h"
#include "2darray.h" 

namespace alg 
{
	/**
	 * maximal flow result structure
	 */
	struct EKResult {
		uint32_t maxflow;	// max flow from src.
		int ** residual;	// residual network , 2d array
		int * pre; 			// pre node of current node 
		bool * visits; 		// mark whether current node is visited

		HashTable<uint32_t> * map;		// vertex id to ordinary row/col number mapping
		HashTable<uint32_t> * rmap;	// reverse mapping of map.
		uint32_t num_vertex;
	};

	// return the ordinary number of a vertex id
	#define MAP(map, id) hash_table_get(map, id)

	static bool __ek_find_path(struct EKResult * result, uint32_t _src, uint32_t _sink);
	/**
	 * edmonds karp algorithm for maximal flow 
	 * a 2d flow array is returned.
	 */
	static struct EKResult *
	edmonds_karp(Graph * g, uint32_t src, uint32_t sink)
	{
		struct EKResult * result = 
			(struct EKResult*)malloc(sizeof(struct EKResult));

		result->maxflow = 0;
		result->pre = (int *)malloc(sizeof(int)*g->vertex_count());
		result->visits = (bool *)malloc(sizeof(bool)*g->vertex_count());

		// residual network 2d array allocating
		result->residual = (int **)malloc(sizeof(int*)*g->vertex_count());
		for (uint32_t i=0; i< g->vertex_count();i++) {
			result->residual[i] = (int*)malloc(sizeof(int)*g->vertex_count());
			memset(result->residual[i], 0, sizeof(int)*g->vertex_count());
		}

		result->map = new HashTable<uint32_t>(g->vertex_count());
		result->rmap = new HashTable<uint32_t>(g->vertex_count());
		result->num_vertex = g->vertex_count();

		// step 1.
		// map vertex ids to ordinal row/col number, and reverse mapping.
		Graph::Adjacent * a;
		int id=0;
		list_for_each_entry(a, &g->a_head, a_node){
			(*result->map)[a->v.id] = id;
			(*result->rmap)[id] = a->v.id;
			id++;
		}

		// step 2. define residual network
		list_for_each_entry(a, &g->a_head, a_node){
			Graph::Vertex * v;
			list_for_each_entry(v, &a->v_head, v_node){
				int from = (*result->map)[a->v.id];
				int to = (*result->map)[v->id];
				result->residual[from][to] = v->weight;
			}
		}

		// step 3. find augument path repeatedly.
		int _src = (*result->map)[src];
		int _sink = (*result->map)[sink];
		int * pre = result->pre;
		int ** residual = result->residual;
		while(__ek_find_path(result, _src, _sink)) {
			int delta = INT_MAX;	

			// find minimal delta
			int i;	
			for (i=_sink;i!=_src;i= pre[i]) {
				delta = Min(delta, residual[pre[i]][i]);
			}

			// for each edge, change residual network
			for (i=_sink; i!=_src;i= pre[i]) {
				residual[pre[i]][i] -= delta;
				residual[i][pre[i]] += delta;
			}

			result->maxflow += delta;
		}

		return result;
	}

	/**
	 * free the result
	 */ 
	static void edmonds_karp_free(struct EKResult * result)
	{
		for (uint32_t i=0; i< result->num_vertex;i++) {
			free(result->residual[i]);
		}

		delete result->residual;
		delete result->pre;
		delete result->visits;

		delete result->map;
		delete result->rmap;
		
		free(result);
	}

	/**
	 * find a augument path. using breadth first search
	 */
	static bool 
	__ek_find_path(struct EKResult * result, uint32_t _src, uint32_t _sink)
	{
		Queue<int32_t> Q(result->num_vertex); 

		// clear visit flag & path
		int * pre = result->pre;
		bool * visits = result->visits;
		int ** residual = result->residual;

		memset(pre, -1, sizeof(int)*result->num_vertex);
		memset(visits, false, sizeof(bool)*result->num_vertex);

		// src setting
		pre[_src] = _src;	
		visits[_src] = true;
		Q.enqueue(_src);

		while(!Q.is_empty()) {
			int p = Q.front();
			Q.dequeue();

			for (uint32_t i=0;i< result->num_vertex;i++) {
				if (residual[p][i] >0 && !visits[i]) {
					pre[i] = p;
					visits[i] = true;

					if (i==_sink) {		// nice, we've got to sink point.
						return true;
					}
					Q.enqueue(i);
				}
			}
		}

		return false;
	}
}

#endif //
