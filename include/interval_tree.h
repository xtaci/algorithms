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

#ifndef __INTERVAL_TREE_H__
#define __INTERVAL_TREE_H__

#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "generic.h"
#include "stack.h"
#include "double_linked_list.h"
#include "rbtree.h"

namespace alg
{
	class IntervalTree:public RBTree<int,int>
	{
	public:
		/**
		 * Interval-Tree node definition
		 */
		typedef struct ivltree_node_t{
			int low;	// lower-bound
			int high;	// higher-bound
			int m;		// max subtree upper bound value
			rbtree_node_t node;	// red-black tree structure
		} * ivltree_node;

#define IVLNODE(rbnode) \
	((ivltree_node)((char *)rbnode - (unsigned long)(&((ivltree_node)0)->node)))

#define IVLNODE_M(rbnode) \
	(rbnode?IVLNODE(rbnode)->m:INT_MIN)

	public:
		/**
		 * ivltree_create
		 * initialized an interval tree
		 * same as init an red-black tree
		 */
		IntervalTree() 
		{
			cb_left = cb_right = fix_rotation;
		}

		/**
		 * ivltree_lookup
		 *
		 * search range [low, high] for overlap, return only one element
		 * use lookup & delete & insert schema to get multiple elements
		 *
		 * NULL is returned if not found.
		 */
		ivltree_node lookup(int low, int high) 
		{
			rbtree_node n = root;
			while (n != NULL && (low > IVLNODE(n)->high || IVLNODE(n)->low > high)) { // should search in childs
				if (n->left !=NULL && low <=IVLNODE(n->left)->m) n = n->left; // path choice on m.
				else n = n->right;
			}

			return n==NULL?NULL:IVLNODE(n); // beware of the NULL pointer
		}

		/**
		 * ivltree_insert
		 * insert range [low, high] into red-black tree
		 */
		void insert(int low, int high) 
		{
			ivltree_node inserted_node = new_node(low, high, RED, NULL, NULL);
			if (root == NULL) {
				root = &inserted_node->node;
			} else {
				rbtree_node n = root;
				while (1) {
					// update 'm' for each node traversed from root
					if (inserted_node->m > IVLNODE(n)->m) {
						IVLNODE(n)->m = inserted_node->m;
					}

					// find a proper position
					if (low < IVLNODE(n)->low) {
						if (n->left == NULL) {
							n->left = &inserted_node->node;
							break;
						} else {
							n = n->left;
						}
					} else {
						if (n->right == NULL) {
							n->right = &inserted_node->node;
							break;
						} else {
							n = n->right;
						}
					}
				}
				inserted_node->node.parent = n;
			}
			insert_case1(&inserted_node->node);
		}

		/**
		 * delete the key in the red-black tree
		 */
		void delete_key(ivltree_node x) 
		{
			rbtree_node child;
			if (x == NULL) return;
			rbtree_node n = &x->node;

			// phase 1. fixup the 'm' value until m is not the max value of the path.
			fixup_m(n);

			// phase 2. red black tree deletion
			if (n->left != NULL && n->right != NULL) {
				/* Copy key/value from predecessor and then delete it instead */
				rbtree_node pred = maximum_node(n->left);
				IVLNODE(n)->low = IVLNODE(pred)->low;
				IVLNODE(n)->high= IVLNODE(pred)->high;
				n = pred;
			}

			assert(n->left == NULL || n->right == NULL);
			child = n->right == NULL ? n->left : n->right;
			if (node_color(n) == BLACK) {
				n->color = node_color(child);
				delete_case1(n);
			}
			replace_node(n, child);
			if (n->parent == NULL && child != NULL)
				child->color = BLACK;

			delete(IVLNODE(n));
		}

		void print() {
			print_helper(root, 0);
			puts("");
		}

		void print_helper(rbtree_node n, int indent) {
			int i;

			if (n == NULL) {
				fputs("<empty tree>", stdout);
				return;
			}

			if (n->right != NULL) {
				print_helper(n->right, indent + INDENT_STEP);
			}
			for(i=0; i<indent; i++)
				fputs(" ", stdout);
			if (n->color == BLACK)
				printf("[%d %d, m->%d]\n", IVLNODE(n)->low,IVLNODE(n)->high,IVLNODE(n)->m);
			else
				printf("*[%d %d, m->%d]\n", IVLNODE(n)->low, IVLNODE(n)->high,IVLNODE(n)->m);
			if (n->left != NULL) {
				print_helper(n->left, indent + INDENT_STEP);
			}
		}


	private:
		/**
		 * fix 'm' value caused by rotation
		 */
		static void fix_rotation(rbtree_node n, rbtree_node parent)
		{
			// parent inherit max m value
			IVLNODE(parent)->m = IVLNODE(n)->m;

			// update node 'm' value by it's children.
			IVLNODE(n)->m = 
				Max(IVLNODE(n)->high, Max(IVLNODE_M(n->left), IVLNODE_M(n->right)));
		}

		/**
		 * fix up 'm' value caued by deletion
		 */
		void fixup_m(rbtree_node n)
		{
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
		ivltree_node new_node(int low, int high, color rbtree_node_color, rbtree_node left, rbtree_node right) 
		{
			ivltree_node result = new ivltree_node_t;
			result->low = low;
			result->high = high;
			result->m = high;
			result->node.color = rbtree_node_color;
			result->node.left = left;
			result->node.right = right;
			if(left !=NULL) left->parent = &result->node;
			if(right!=NULL) right->parent = &result->node;
			result->node.parent = NULL;
			return result;
		}
	};
}

#endif //
