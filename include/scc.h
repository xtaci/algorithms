/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * STRONGLY CONNECTED COMPONENT
 *
 * In the mathematical theory of directed graphs, a graph is said to be strongly
 * connected if every vertex is reachable from every other vertex. The strongly 
 * connected components of an arbitrary directed graph form a partition into 
 * subgraphs that are themselves strongly connected. It is possible to test the
 * strong connectivity of a graph, or to find its strongly connected components,
 * in linear time.
 *
 * http://en.wikipedia.org/wiki/Strongly_connected_component
 ******************************************************************************/

#ifndef ALGO_SCC_H__
#define ALGO_SCC_H__
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include "graph_defs.h"
#include "graph_search.h"
#include "heap.h"

namespace alg {
	/**
	 * Output Strongly Connected Component of a Graph
	 */
	static void SCC(DirectedGraph &g) {
		// call DFS(G) to compute finishing times u.f for each vertex u
		DFS(g);
		// the transpose of the graph
		DirectedGraph * GT = g.transpose();
		// step 1. discover vertices of G in decreasing of u.f
		Heap<int32_t> Q(g.vertex_count()) ;
		Graph::Adjacent * a;
		list_for_each_entry(a, &g.list(), a_node) {
			Q.push(INT_MAX - a->f, a->v.id);	// descending order of a->f
		}

		// step 2. discover 
		// mark all vertex color to WHITE   
		list_for_each_entry(a, &GT->list(), a_node) {
			a->color = Graph::WHITE;
		}

		// step 3. call DFS(GT), but in the main loop of DFS, consider the vertices
		// in order of decreasing u.f (as computed in line 1)
		while(!Q.is_empty()) {
			Heap<int32_t>::elem e = Q.pop();
			int32_t key = e.key;
			int32_t id = e.data;
			if ((*GT)[id]->color == Graph::WHITE) {
				printf("component:%d %d\n",id, INT_MAX - key);
				_DFS_VISIT(*GT, (*GT)[id]);
				printf("\n");
			}
		}
		delete GT;
	}
}

#endif //
