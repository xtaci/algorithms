/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * UNDIRECTED GRAPH
 *
 * Features:
 * 1. Adjacency List Implementation
 *
 * http://en.wikipedia.org/wiki/Undirected_graph
 *
 ******************************************************************************/

#ifndef __UNDIRECTED_GRAPH_H__
#define __UNDIRECTED_GRAPH_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include "graph_defs.h"
#include "double_linked_list.h"

static inline struct Vertex * undirected_graph_new_vertex(uint32_t id)
{
	struct Vertex * v = (struct Vertex *)malloc(sizeof(struct Vertex));		
	v->id = id;
	v->weight = -INT_MAX;
	return v;
}


/**
 * delete a vertex from adjacent list
 */
static inline void undirected_graph_del_me_from_adjacent(struct Adjacent * a, uint32_t id)
{
	struct Vertex * v, *vn;
	list_for_each_entry_safe(v, vn, &a->v_head, v_node){
		if (v->id == id ) {
			list_del(&v->v_node);
			free(v);
			break;
		}
	}
}

/**
 * test if an edge exists
 */
static inline bool undirected_graph_is_adjacent(struct Adjacent * from, struct Adjacent * to)
{
	struct Vertex * v;
	list_for_each_entry(v, &from->v_head, v_node){
		if (v->id == to->v.id ) { return true; }
	}
	return false;
}

/**
 * create a new undirected graph data structure and initialize it.
 */
inline struct Graph * undirected_graph_create()
{
	struct Graph * g = (struct Graph *)malloc(sizeof(struct Graph));
	g->num_vertex = 0;
	g->num_edges = 0;
	INIT_LIST_HEAD(&g->a_head);

	return g;
}

/**
 * create a new vertex and add to the graph, with specified id.
 */
inline bool undirected_graph_add_vertex(struct Graph * g, uint32_t id)
{
	if (graph_lookup(g,id)!=NULL) return false;

	// new empty adjacent list
	struct Adjacent * a = (struct Adjacent *)malloc(sizeof(struct Adjacent));
	INIT_LIST_HEAD(&a->v_head);
	a->v.id = id; 	// new vertex id
	a->num_neigh = 0;
	list_add_tail(&a->a_node, &g->a_head);
	g->num_vertex++;

	return true;
}

/**
 * delete a vertex with specified id 
 */
inline void undirected_graph_del_vertex(struct Graph * g, uint32_t id)
{
	struct Adjacent * a = graph_lookup(g, id);
	if (a==NULL) return;
	
	struct Vertex * v,* vn;
	// find connected-vertex
	list_for_each_entry_safe(v, vn, &a->v_head, v_node){
		struct Adjacent * neigh = graph_lookup(g, v->id);
		undirected_graph_del_me_from_adjacent(neigh, id);
		list_del(&v->v_node);
		free(v);
		neigh->num_neigh--;
		g->num_edges--;
	}

	// delete adjacent list itself.
	list_del(&a->a_node);
	free(a);
	g->num_vertex--;
}


/**
 * add an edge for x<->y
 */
inline bool undirected_graph_add_edge(struct Graph * g, uint32_t x, uint32_t y, int32_t weight)
{
	struct Adjacent * a1 = graph_lookup(g, x);
	struct Adjacent * a2 = graph_lookup(g, y);

	if (a1==NULL || a2==NULL) return false;
	if (undirected_graph_is_adjacent(a1, a2)) return false;
	
	// create new vertex & add to adjacent list
	struct Vertex * n = undirected_graph_new_vertex(y);
	n->weight = weight;
	list_add_tail(&n->v_node, &a1->v_head);
	
	n = undirected_graph_new_vertex(x);
	n->weight = weight;
	list_add_tail(&n->v_node, &a2->v_head);

	g->num_edges++;
	a1->num_neigh++;
	a2->num_neigh++;

	return true;
}

/**
 * delete an edge for x<->y
 */
inline void undirected_graph_del_edge(struct Graph * g, uint32_t x, uint32_t y)
{
	struct Adjacent * a1 = graph_lookup(g, x);
	struct Adjacent * a2 = graph_lookup(g, y);
	if (a1==NULL || a2==NULL) return ;
	if (!undirected_graph_is_adjacent(a1, a2)) return ;
	
	struct Vertex * v, *n;
	// find x->.....y...	
	list_for_each_entry_safe(v, n, &a1->v_head, v_node){
		if (v->id == y) {
			list_del(&v->v_node);
			free(v);
			g->num_edges--;
			a1->num_neigh--;
		}
	}

	// find y->.....x...	
	list_for_each_entry_safe(v, n, &a2->v_head, v_node){
		if (v->id == x) {
			list_del(&v->v_node);
			free(v);
			a2->num_neigh--;
		}
	}
}

/**
 * print a graph
 */
inline void undirected_graph_print(const struct Graph * g)
{
	struct Adjacent * a;
	printf("Graph : %d vertex, %d edges\n", g->num_vertex,g->num_edges);
	list_for_each_entry(a, &g->a_head, a_node){
		printf("%d(neigh:%d)->{", a->v.id, a->num_neigh);
		struct Vertex * v;
		list_for_each_entry(v, &a->v_head, v_node){
			printf("%d(w:%d)\t", v->id, v->weight);
		}
		printf("}\n");
	}	
}

#endif //
