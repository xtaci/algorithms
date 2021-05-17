/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * BREADTH FIRST SEARCH
 *
 * Features:
 *   In graph theory, breadth-first search (BFS) is a strategy for searching in
 * a graph when search is limited to essentially two operations: 
 *   (a) visit and inspect a node of a graph;
 *   (b) gain access to visit the nodes that neighbor the currently visited node.
 *   The BFS begins at a root node and inspects all the neighboring nodes. Then
 * for each of those neighbor nodes in turn, it inspects their neighbor nodes 
 * which were unvisited, and so on. Compare it with the depth-first search.
 *
 * http://en.wikipedia.org/wiki/Breadth-first_search
 *
 ******************************************************************************/

#ifndef ALGO_BREADTH_FIRST_SEARCH_H__
#define ALGO_BREADTH_FIRST_SEARCH_H__

#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#include "queue.h"
#include "stack.h"
#include "directed_graph.h"
#include "hash_table.h"

namespace alg {
	/**
	 * BREADTH FIRST SEARCH
	 */
	static void BFS(const Graph & g, int32_t src_id) {
		// mark all vertex color to WHITE	
		Graph::Adjacent * a;
		list_for_each_entry(a, &g.list(), a_node) {
			a->color = Graph::WHITE;
			a->d = INT_MAX;
		}

		Graph::Adjacent * s = g[src_id];
		s->d = 0;
		Queue<uint32_t> Q(g.vertex_count());
		Q.enqueue(s->v.id);

		while(!Q.is_empty()) {
			uint32_t id = Q.front();
			printf("%d->", id);		// output discovered id
			Q.dequeue();	
			Graph::Vertex * _v;
			Graph::Adjacent * u = g[id];
			list_for_each_entry(_v, &u->v_head, v_node) {
				Graph::Adjacent * v = g[_v->id];	// retrive the original adjacent list
				if (v->color == Graph::WHITE) {		// to change node color
					v->color = Graph::GRAY;
					v->d = u->d + 1;
					Q.enqueue(v->v.id); 
				}
			}
			u->color = Graph::BLACK;
		}
		printf("\n");
	}

	static void _DFS_VISIT(Graph &g, Graph::Adjacent * u);
	/**
	 * DEPTH FIRST SEARCH
	 */
	static void DFS(Graph & g) {
		// mark all vertex color to WHITE	
		Graph::Adjacent * a;
		list_for_each_entry(a, &g.list(), a_node) {
			a->color = Graph::WHITE;
		}

		// for each vertex
		g.graph_tick = 0;
		list_for_each_entry(a, &g.list(), a_node) {
			if (a->color == Graph::WHITE) {
				printf("DFS from : %d\t",a->v.id);
				_DFS_VISIT(g, a);
				printf("\n");
			}
		}
		printf("\n");
	}

	/**
	 * recursivly visit (Call Stack)
	 */
	static void _DFS_VISIT(Graph &g, Graph::Adjacent * u) {
		// white vertex u has just benn discovered
		u->d = ++g.graph_tick;
		u->color = Graph::GRAY;

		Graph::Vertex * _v;
		list_for_each_entry(_v, &u->v_head, v_node) { // explore edge (u, v)
			Graph::Adjacent * v = g[_v->id];	// retrive the original adjacent list
			if (v->color == Graph::WHITE) {
				_DFS_VISIT(g, v);
			}
		}
		u->color = Graph::BLACK;
		u->f = ++g.graph_tick;
		printf("%d(d:%d, f:%d) -> ", u->v.id, u->d, u->f);
	}
}

#endif //
