/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * INTERVAL-TREE
 *
 * Features:
 * 1. red-black tree based
 * 2. O(logn) lookup performance
 * 3. range search [low, high]
 * 
 * http://en.wikipedia.org/wiki/Interval_tree
 *
 ******************************************************************************/

#ifndef ALGO_INTERVAL_TREE_H__
#define ALGO_INTERVAL_TREE_H__

#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "generic.h"
#include "stack.h"
#include "double_linked_list.h"
#include "rbtree.h"

namespace alg {
	class IntervalTree:public RBTreeAbstract {
		public:
			/**
			 * Interval-Tree node definition
			 */
			typedef struct ivltree_node_t : public rbtree_node_t {
				int low;	// lower-bound
				int high;	// higher-bound
				int m;		// max subtree upper bound value
			} * ivltree_node;

#define IVLNODE(rbnode) static_cast<ivltree_node>(rbnode)
#define IVLNODE_M(rbnode) (rbnode?IVLNODE(rbnode)->m:INT_MIN)

		public:
			/**
			 * ivltree_create
			 * initialized an interval tree
			 * same as init an red-black tree
			 */
			IntervalTree() { }

			/**
			 * ivltree_lookup
			 *
			 * search range [low, high] for overlap, return only one element
			 * use lookup & delete & insert schema to get multiple elements
			 *
			 * NULL is returned if not found.
			 */
			ivltree_node lookup(int low, int high) {
				ivltree_node n = IVLNODE(get_root());
				while (n != NULL && (low > n->high || n->low > high)) { // should search in childs
					if (n->left !=NULL && low <=IVLNODE(n->left)->m) n = IVLNODE(n->left); // path choice on m.
					else n = IVLNODE(n->right);
				}

				return n;
			}

			/**
			 * ivltree_insert
			 * insert range [low, high] into red-black tree
			 */
			void insert(int low, int high) {
				ivltree_node inserted_node = new_node(low, high, RED, NULL, NULL);
				if (get_root() == NULL) {
					set_root(inserted_node);
				} else {
					ivltree_node n = IVLNODE(get_root());
					while (1) {
						// update 'm' for each node traversed from root
						if (inserted_node->m > n->m) {
							n->m = inserted_node->m;
						}

						// find a proper position
						if (low < n->low) {
							if (n->left == NULL) {
								n->left = inserted_node;
								break;
							} else {
								n = IVLNODE(n->left);
							}
						} else {
							if (n->right == NULL) {
								n->right = inserted_node;
								break;
							} else {
								n = IVLNODE(n->right);
							}
						}
					}
					inserted_node->parent = n;
				}
				insert_case1(inserted_node);
			}

			/**
			 * delete the key in the red-black tree
			 */
			void delete_key(ivltree_node n) {
				rbtree_node child;
				if (n == NULL) return;

				/* Copy fields from predecessor and then delete it instead */
				if (n->left != NULL && n->right != NULL) {
					ivltree_node pred = IVLNODE(maximum_node(n->left));
					n->low = pred->low;
					n->high= pred->high;
					n = pred;
				}

				// fixup the 'm' value until m is not the max value of the path.
				fixup_m(n);

				assert(n->left == NULL || n->right == NULL);
				child = n->right == NULL ? n->left : n->right;
				if (node_color(n) == BLACK) {
					n->color = node_color(child);
					delete_case1(n);
				}

				replace_node(n, child);
	    		if (n->parent == NULL && child != NULL)	// root
        			child->color = BLACK;
				delete(n);
			}

			void print() {
				print_helper(IVLNODE(get_root()), 0);
				puts("");
			}

			void print_helper(ivltree_node n, int indent) {
				int i;

				if (n == NULL) {
					fputs("<empty tree>", stdout);
					return;
				}

				if (n->right != NULL) {
					print_helper(IVLNODE(n->right), indent + INDENT_STEP);
				}
				for(i=0; i<indent; i++)
					fputs(" ", stdout);
				if (n->color == BLACK)
					printf("[%d %d, m->%d]\n", n->low,n->high,n->m);
				else
					printf("*[%d %d, m->%d]\n", n->low, n->high,n->m);
				if (n->left != NULL) {
					print_helper(IVLNODE(n->left), indent + INDENT_STEP);
				}
			}

			~IntervalTree() {
				destruct(IVLNODE(get_root()));
			}

		private:
			void destruct(ivltree_node n) {
				if (n==NULL) return;
				destruct(IVLNODE(n->left));
				destruct(IVLNODE(n->right));
				delete n;
			}

			/**
			 * fix 'm' value caused by rotation
			 */
			void rotate_left_callback(rbtree_node n, rbtree_node parent) {
				// parent inherit max m value
				IVLNODE(parent)->m = IVLNODE(n)->m;
				// update node 'm' value by it's children.
				IVLNODE(n)->m = Max(IVLNODE(n)->high, Max(IVLNODE_M(n->left), IVLNODE_M(n->right)));
			}

			void rotate_right_callback(rbtree_node n, rbtree_node parent) {
				rotate_left_callback(n, parent);
			}

			/**
			 * fix up 'm' value caued by deletion
			 */
			void fixup_m(rbtree_node n) {
				int m = IVLNODE(n)->m;
				int m_new = Max(IVLNODE_M(n->left), IVLNODE_M(n->right));

				// if current 'm' is not decided by n->high, just return.
				if (m==m_new) return;

				while(n->parent !=NULL) {
					/*
					   parent(high)
					   /	      \
					   n(m_new)	  sibling(m)

					 */	
					IVLNODE(n->parent)->m = 
						Max(IVLNODE(n->parent)->high, Max(m_new, IVLNODE_M(sibling(n))));

					if(IVLNODE_M(n->parent) > m) break;	// since node n does not affect
					//  the result anymore, we break.
					n = n->parent;
				}
			}

			/**
			 * create a new node, and set default vales.
			 */
			ivltree_node new_node(int low, int high, color rbtree_node_color, rbtree_node left, rbtree_node right) {
				ivltree_node result = new ivltree_node_t;
				result->low = low;
				result->high = high;
				result->m = high;
				result->color = rbtree_node_color;
				result->left = left;
				result->right = right;
				if(left !=NULL) left->parent = result;
				if(right!=NULL) right->parent = result;
				result->parent = NULL;
				return result;
			}
	};
}

#endif //
