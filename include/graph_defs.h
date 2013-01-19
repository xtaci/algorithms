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
 * Undirected Graph
 */
struct Graph {
	struct list_head a_head; // list header
	uint32_t num_vertex;
	uint32_t num_edges;
};

/**
 * find an adjacent list with vertex id == id 
 */
inline struct Adjacent * graph_lookup(const struct Graph * g, uint32_t id)
{
	struct Adjacent * a;
	list_for_each_entry(a, &g->a_head, a_node){
		if (a->v.id == id) { return a;}
	}
	
	return NULL;
}

#endif //
