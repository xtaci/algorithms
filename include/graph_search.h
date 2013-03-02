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

#ifndef __BREADTH_FIRST_SEARCH_H__
#define __BREADTH_FIRST_SEARCH_H__

#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#include "queue.h"
#include "stack.h"
#include "directed_graph.h"
#include "hash_table.h"

namespace alg 
{
	static void breadth_first_search(const Graph & g, uint32_t source)
	{
		static const uint32_t MARK = 0xDEAD;

		Graph::Adjacent * root = g[source];
		HashTable<uint32_t> ht(g.vertex_count());		

		if (root==NULL) return;

		// init
		Queue<uint32_t> Q(g.vertex_count());
		Q.enqueue(root->v.id);
		ht[root->v.id] = MARK;
		
		while(!Q.is_empty()) {
			uint32_t t = Q.front();
			printf("%d->", t);
			Q.dequeue();	
			Graph::Vertex * v;
			Graph::Adjacent * a = g[t];
			list_for_each_entry(v, &a->v_head, v_node) {
				if (!ht.contains(v->id) || ht[v->id]!=MARK) {
					ht[v->id] = MARK;
					Q.enqueue(v->id); 
				}
			}
		}

		printf("\n");
	}

	static void depth_first_search(const Graph & g, uint32_t source)
	{
		static const uint32_t MARK = 0xDEAD;

		Graph::Adjacent * root = g[source];
		HashTable<uint32_t> ht(g.vertex_count());		

		if (root==NULL) return;

		// init
		Stack<uint32_t> S(g.vertex_count());
		S.push(root->v.id);
		ht[root->v.id] = MARK;
		
		while(!S.is_empty()) {
			uint32_t t = S.top();	
			printf("%d->", t);
			S.pop();	
			Graph::Vertex * v;
			Graph::Adjacent * a = g[t];
			list_for_each_entry(v, &a->v_head, v_node) {
				if (!ht.contains(v->id) || ht[v->id] !=MARK) {
					ht[v->id] = MARK;
					S.push(v->id);
				}
			}
		}
		
		printf("\n");
	}
}

#endif //
