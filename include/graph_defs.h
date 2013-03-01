#ifndef __GRAPH_DEFS_H__
#define __GRAPH_DEFS_H__

#include "double_linked_list.h"

namespace alg
{
	/**
	 * Graph definition
	 */
	class Graph {
	public:
		/**
		 * the connected Vertex
		 */
		struct Vertex {
			uint32_t id;
			int32_t weight;	
			struct list_head v_node; 

			Vertex(uint32_t vid) 
			{
				id = vid;
				weight = -INT_MAX;
			}
		};

		/**
		 * Adjacent Lists.
		 */
		struct Adjacent {
			struct Vertex v;
			struct list_head v_head;  // vertex list header
			struct list_head a_node; 
			uint32_t num_neigh;		// num of neighbours

			Adjacent(uint32_t id):v(id)
			{
				INIT_LIST_HEAD(&v_head);
				num_neigh = 0;
			}

			~Adjacent() 
			{
				Vertex * v, *vn;
				list_for_each_entry_safe(v, vn, &v_head, v_node){
					list_del(&v->v_node);
					delete v;
				}
			}

			const Vertex & vertex() const { return v;}

			void delete_vertex(uint32_t id)
			{
				Vertex * v, *vn;
				list_for_each_entry_safe(v, vn, &v_head, v_node){
					if (v->id == id ) {
						list_del(&v->v_node);
						num_neigh--;
						delete v;
						break;
					}
				}
			}
			
			/**
			 * get the Vertex from an adjacent list, according to vertex id
			 */
			Vertex * operator[] (uint32_t id) const
			{
				Vertex * v;
				list_for_each_entry(v, &v_head, v_node){
					if (v->id == id) { 
						return v;	
					}
				}
				return NULL;
			}
		};

	protected:
		uint32_t num_vertex;
		uint32_t num_edges;
	public:
		struct list_head a_head; // list header
		Graph()
		{
			num_vertex = 0;
			num_edges = 0;
			INIT_LIST_HEAD(&a_head);
		}

		virtual ~Graph() 
		{
			Adjacent * a, *an;
			list_for_each_entry_safe(a, an, &a_head, a_node){
				list_del(&a->a_node);
				delete a;
			}
		}

		uint32_t vertex_count() const {	return num_vertex; }
		uint32_t edge_count() const { return num_edges; }
		/**
		 * find an adjacent list with vertex id == id 
		 */
		Adjacent * operator[] (uint32_t id) const
		{
			Adjacent * a;
			list_for_each_entry(a, &a_head, a_node){
				if (a->v.id == id) { return a;}
			}
			
			return NULL;
		}

		/**
		 * print a graph
		 */
		void print() const
		{
			Adjacent * a;
			printf("Graph : %d vertex, %d edges\n", num_vertex,num_edges);
			list_for_each_entry(a, &a_head, a_node){
				printf("%d(neigh:%d)->{", a->v.id, a->num_neigh);
				Vertex * v;
				list_for_each_entry(v, &a->v_head, v_node){
					printf("%d(w:%d)\t", v->id, v->weight);
				}
				printf("}\n");
			}	
		}

		const list_head & list() const {return a_head; }
	protected:
		/**
		 * test if an edge exists
		 */
		bool is_adjacent(const struct Adjacent * from, const struct Adjacent * to)
		{
			struct Vertex * v;
			list_for_each_entry(v, &from->v_head, v_node){
				if (v->id == to->v.id ) { return true; }
			}
			return false;
		}
	};
}

#endif //
