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

#define MARK 0xDEADU

static void 
breadth_first_search(const struct Graph * g, uint32_t source)
{
	struct Adjacent * root = graph_lookup(g, source);
	struct HashTable * ht = hash_table_create(g->num_vertex);		

	if (root==NULL) return;

	// init
	Queue<uint32_t> Q(g->num_vertex);
	Q.enqueue(root->v.id);
	hash_table_set(ht, root->v.id, (uintptr_t)MARK);
	
	while(!Q.is_empty()) {
		uint32_t t = Q.front();
		printf("%d->", t);
		Q.dequeue();	
		struct Vertex * v;
		struct Adjacent * a = graph_lookup(g, t);
		list_for_each_entry(v, &a->v_head, v_node) {
			if ((uint32_t)hash_table_get(ht, v->id)!=MARK) {
				hash_table_set(ht, v->id, (uintptr_t)MARK);
				Q.enqueue(v->id); 
			}
		}
	}

	hash_table_destroy(ht);	
	printf("\n");
}

static void 
depth_first_search(const struct Graph *g, uint32_t source)
{
	struct Adjacent * root = graph_lookup(g, source);
	struct HashTable * ht = hash_table_create(g->num_vertex);		

	if (root==NULL) return;

	// init
	Stack<uint32_t> S(g->num_vertex);
	S.push(root->v.id);
	hash_table_set(ht, root->v.id, (uintptr_t)MARK);
	
	while(!S.is_empty()) {
		uint32_t t = S.top();	
		printf("%d->", t);
		S.pop();	
		struct Vertex * v;
		struct Adjacent * a = graph_lookup(g, t);
		list_for_each_entry(v, &a->v_head, v_node) {
			if ((uint32_t)hash_table_get(ht, v->id)!=MARK) {
				hash_table_set(ht, v->id, (uintptr_t)MARK);
				S.push(v->id);
			}
		}
	}
	
	hash_table_destroy(ht);	
	printf("\n");
}

#endif //
