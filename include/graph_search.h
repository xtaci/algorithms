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

static inline void 
breadth_first_search(const struct Graph * g, uint32_t source)
{
	struct Adjacent * root = graph_lookup(g, source);
	struct HashTable * ht = hash_table_create(g->num_vertex);		

	if (root==NULL) return;

	// init
	Queue * Q = create_queue(g->num_vertex);
	enqueue(Q, (uintptr_t)root->v.id);
	hash_table_set(ht, root->v.id, (uintptr_t)MARK);
	
	while(!queue_is_empty(Q)) {
		uint32_t t = (uint32_t)queue_front(Q);	
		printf("%d->", t);
		dequeue(Q);	
		struct Vertex * v;
		struct Adjacent * a = graph_lookup(g, t);
		list_for_each_entry(v, &a->v_head, v_node) {
			if ((uint32_t)hash_table_get(ht, v->id)!=MARK) {
				hash_table_set(ht, v->id, (uintptr_t)MARK);
				enqueue(Q, (uintptr_t)v->id); 
			}
		}
	}

	hash_table_destroy(ht);	
	printf("\n");
}

static inline void 
depth_first_search(const struct Graph *g, uint32_t source)
{
	struct Adjacent * root = graph_lookup(g, source);
	struct HashTable * ht = hash_table_create(g->num_vertex);		

	if (root==NULL) return;

	// init
	Stack * S = create_stack(g->num_vertex);
	push(S, (uintptr_t)root->v.id);
	hash_table_set(ht, root->v.id, (uintptr_t)MARK);
	
	while(!stack_is_empty(S)) {
		uint32_t t = (uint32_t)top(S);	
		printf("%d->", t);
		pop(S);	
		struct Vertex * v;
		struct Adjacent * a = graph_lookup(g, t);
		list_for_each_entry(v, &a->v_head, v_node) {
			if ((uint32_t)hash_table_get(ht, v->id)!=MARK) {
				hash_table_set(ht, v->id, (uintptr_t)MARK);
				push(S, (uintptr_t)v->id); 
			}
		}
	}
	
	hash_table_destroy(ht);	
	printf("\n");
}

#endif //
