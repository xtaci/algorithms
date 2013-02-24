#ifndef __GRAPH_DEFS_H__
#define __GRAPH_DEFS_H__

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
 * Graph definition
 */
struct Graph {
	struct list_head a_head; // list header
	uint32_t num_vertex;
	uint32_t num_edges;
};

/**
 * find an adjacent list with vertex id == id 
 */
static struct Adjacent * 
graph_lookup(const struct Graph * g, uint32_t id)
{
	struct Adjacent * a;
	list_for_each_entry(a, &g->a_head, a_node){
		if (a->v.id == id) { return a;}
	}
	
	return NULL;
}

/**
 * get the Vertex from an adjacent list, according to vertex id
 */
static struct Vertex *
graph_get_vertex(const struct Graph * g, uint32_t from, uint32_t to)
{
	struct Vertex * v;
	struct Adjacent * _from = graph_lookup(g, from);

	list_for_each_entry(v, &_from->v_head, v_node){
		if (v->id == to ) { 
			return v;	
		}
	}

	return NULL;
}

#endif //
