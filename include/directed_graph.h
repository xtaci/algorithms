/*******************************************
 * DANIEL'S PRIVATE ALGORITHM IMPLEMENTAIONS
 * Directed Graph Data Structure
 * Features:
 * 1. Adjacency List Implementation
 *******************************************/
#ifndef __DIRECTED_GRAPH_H__
#define __DIRECTED_GRAPH_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include "double_linked_list.h"

/**
 * the connected Vertex
 */
struct Vertex {
	uint32_t id;
	int32_t weight;	
	struct list_head v_node; 
	// void * data;
};

/**
 * Adjacent Lists.
 */
struct Adjacent {
	struct Vertex v;
	struct list_head v_head;  // vertex list header
	struct list_head a_node; 
	uint32_t num_neigh;		// num of neighbours
};

/**
 * Undirected Graph
 */
struct DirectedGraph {
	struct list_head a_head; // list header
	uint32_t num_vertex;
	uint32_t num_edges;
};


static inline struct Vertex * directed_graph_new_vertex(uint32_t id)
{
	struct Vertex * v = (struct Vertex *)malloc(sizeof(struct Vertex));		
	v->id = id;
	v->weight = -INT_MAX;
	return v;
}


/**
 * delete a vertex from adjacent list
 */
static inline void directed_graph_del_me_from_adjacent(struct DirectedGraph * g, struct Adjacent * a, uint32_t id)
{
	struct Vertex * v, *vn;
	list_for_each_entry_safe(v, vn, &a->v_head, v_node){
		if (v->id == id ) {
			list_del(&v->v_node);
			free(v);
			g->num_edges--;
			a->num_neigh--;
			break;
		}
	}
}

/**
 * find an adjacent list with vertex id == id 
 */
static inline struct Adjacent * directed_graph_lookup(struct DirectedGraph * g, uint32_t id)
{
	struct Adjacent * a;
	list_for_each_entry(a, &g->a_head, a_node){
		if (a->v.id == id) { return a;}
	}
	
	return NULL;
}

/**
 * test if an edge exists
 */
static inline bool directed_graph_is_adjacent(struct Adjacent * from, struct Adjacent * to)
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
inline struct DirectedGraph * directed_graph_create()
{
	struct DirectedGraph * g = (struct DirectedGraph *)malloc(sizeof(struct DirectedGraph));
	g->num_vertex = 0;
	g->num_edges = 0;
	INIT_LIST_HEAD(&g->a_head);

	return g;
}

/**
 * create a new vertex and add to the graph, with specified id.
 */
inline bool directed_graph_add_vertex(struct DirectedGraph * g, uint32_t id)
{
	if (directed_graph_lookup(g,id)!=NULL) return false;

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
inline void directed_graph_del_vertex(struct DirectedGraph * g, uint32_t id)
{
	struct Adjacent * a = directed_graph_lookup(g, id);
	if (a==NULL) return;
	
	// delete every connection, iterator through every vertex
	struct Adjacent * tmp_adj;
	list_for_each_entry(tmp_adj, &g->a_head, a_node){
		if (tmp_adj->v.id != a->v.id) directed_graph_del_me_from_adjacent(g, tmp_adj, id);
	}

	// delete adjacent list itself.
	g->num_vertex--;
	g->num_edges -= a->num_neigh;
	list_del(&a->a_node);
	free(a);
}


/**
 * add an edge for x -> y
 */
inline bool directed_graph_add_edge(struct DirectedGraph * g, uint32_t x, uint32_t y, int32_t weight)
{
	struct Adjacent * a1 = directed_graph_lookup(g, x);
	struct Adjacent * a2 = directed_graph_lookup(g, y);

	// make sure both vertex exists & not connected from x->y
	if (a1==NULL || a2==NULL) return false;
	if (directed_graph_is_adjacent(a1, a2)) return false;

	// create new vertex & add to adjacent list
	struct Vertex * n = directed_graph_new_vertex(y);
	n->weight = weight;
	list_add_tail(&n->v_node, &a1->v_head);
	
	g->num_edges++;
	a1->num_neigh++;

	return true;
}

/**
 * delete an edge for x -> y
 */
inline void directed_graph_del_edge(struct DirectedGraph * g, uint32_t x, uint32_t y)
{
	struct Adjacent * a1 = directed_graph_lookup(g, x);
	struct Adjacent * a2 = directed_graph_lookup(g, y);
	if (a1==NULL || a2==NULL) return ;
	if (!directed_graph_is_adjacent(a1, a2)) return ;
	
	struct Vertex * v, *n;
	// find y in adjacent list of x
	list_for_each_entry_safe(v, n, &a1->v_head, v_node){
		if (v->id == y) {
			list_del(&v->v_node);
			free(v);
			g->num_edges--;
			a1->num_neigh--;
		}
	}
}

/**
 * print a graph
 */
inline void directed_graph_print(struct DirectedGraph * g)
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
