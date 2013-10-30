/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * FIBONACCI HEAP
 *
 * In computer science, a Fibonacci heap is a heap data structure consisting of 
 * a collection of trees. It has a better amortized running time than a binomial
 * heap. Fibonacci heaps were developed by Michael L. Fredman and Robert E. Tarjan
 * in 1984 and first published in a scientific journal in 1987. The name of 
 * Fibonacci heap comes from Fibonacci numbers which are used in the 
 * running time analysis.
 *
 * http://en.wikipedia.org/wiki/Fibonacci_heap
 ******************************************************************************/

#ifndef __FIB_HEAP_H__
#define __FIB_HEAP_H__
#include <math.h>
#include <stdint.h>
#include <unistd.h>
#include "double_linked_list.h"
namespace alg {
	template<typename _Key,typename _Val>
		class FibHeap {
			public:
				typedef _Key key_type;
				typedef _Val value_type;
				typedef struct node_t {
					int32_t degree;
					node_t * parent;
					node_t * child;	
					bool mark;
					key_type key;
					value_type value;
					struct list_head node;	// list data struct
				} *Node;
			private:
				FibHeap(const FibHeap &);
				FibHeap& operator=(const FibHeap&);
			private:
				int32_t n;	
				Node min;
				struct list_head rootlist;
			public:
				FibHeap():n(0),min(0){
					INIT_LIST_HEAD(&rootlist);
				}

				/**
				 * insert a value into the Fibonacci Heap
				 */
				void Insert(key_type key, value_type value) {
					Node x = new node_t;
					x->degree = 0;
					x->p = NULL;
					x->child = NULL;
					x->mark = false;
					if (min == NULL) {
						min = x;
						list_add(&x->node, &rootlist);
					} else {
						list_add(&x->node, &rootlist);
						if (x->key < min->key) {
							min = x;
						}
					}
					n = n+1;
				}

				/**
				 * Union 2 Fibonacci-Heap
				 */
				static FibHeap* Union(FibHeap *H1, FibHeap *H2) {
					FibHeap * H = new FibHeap();
					H->min = H1->min;
					H->rootlist = H1->rootlist;
					list_splice(&H->rootlist, &H1->rootlist);	// concat 2 root-list
					list_splice(&H->rootlist, &H2->rootlist);
					if (H1->min == NULL || (H2.min != NULL && H2->min.key < H1->min.key)) {
						H->min = H2->min;
					}
					H->n = H1->n + H2->n;
					return H;
				}

				/**
				 * Extract Min Element
				 */
				Node * ExtractMin() {
					Node z = min;
					if (z != NULL) {
						Node n, ns;
						// for each child x of z, add x to the root list of H
						list_for_each_entry_safe(n,ns, z->child, node){
							list_add(&n->node, &rootlist);
							n->parent = NULL;
						}

						// remove z from the root list of H
						list_del(&z->node, &rootlist);
						if (z == z->next) {	// the only node on the root list
							min = NULL;
						} else {
							min = z->right;
							Consolidate();
						}
						n = n + 1;
					}
				}

				void Consolidate() {
				}
			
				int32_t D(int32_t n) {
					return int32_t(ceil(log(n)));
				}
		};
}

#endif //
