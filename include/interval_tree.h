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

/**
 * Interval-Tree node definition
 */
typedef struct ivltree_node_t {
	int low;	// lower-bound
	int high;	// higher-bound
	int m;		// max subtree upper bound value
	struct rbtree_node_t node;	// red-black tree structure
} *ivltree_node;

#define IVLNODE(rbnode) \
	((ivltree_node)((char *)rbnode - (unsigned long)(&((ivltree_node)0)->node)))

#define IVLNODE_M(rbnode) \
	(rbnode?IVLNODE(rbnode)->m:INT_MIN)

/**
 * Interfaces
 */
static inline rbtree ivltree_create();
static void ivltree_insert(rbtree t, int low, int high);
static ivltree_node ivltree_lookup(rbtree t, int low, int high);
static void ivltree_delete(rbtree t, ivltree_node n);

/**
 * Auxillary functions
 */
static ivltree_node __ivltree_new_node(int low, int high, 
			color rbtree_node_color, rbtree_node left, rbtree_node right);

/**
 * fix 'm' value caused by rotation
 */
static void __ivltree_fix_rotation(rbtree_node n, rbtree_node parent)
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
static void __ivltree_fixup_m(rbtree_node n)
{
	int m = IVLNODE(n)->m;
	int m_new = Max(IVLNODE_M(n->left), IVLNODE_M(n->right));

	while(n->parent !=NULL) {
		//
		// 		   parent(high)
		//         /	      \
		//		n(m_new)	  sibling(m)
		// 
		//
		IVLNODE(n->parent)->m = 
			Max(IVLNODE(n->parent)->high, Max(m_new, IVLNODE_M(__sibling(n))));

		if(IVLNODE_M(n->parent) > m) break;	// since node n does not affect
											//  the result anymore, we break.
		n = n->parent;
	}
}

/**
 * ivltree_create
 * initialized an interval tree
 * same as init an red-black tree
 */
static inline rbtree 
ivltree_create() 
{
    rbtree t = malloc(sizeof(struct rbtree_t));
    t->root = NULL;
	t->cb_left = t->cb_right = __ivltree_fix_rotation;
    return t;
}

/**
 *  malloc a new node, and set default vales.
 */
static ivltree_node 
__ivltree_new_node(int low, int high, 
		color rbtree_node_color, rbtree_node left, rbtree_node right) 
{
	ivltree_node result = malloc(sizeof(struct ivltree_node_t));
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



/**
 * ivltree_lookup
 *
 * search range [low, high] for overlap, return only one element
 * use lookup & delete & insert schema to get multiple elements
 *
 * NULL is returned if not found.
 */
static ivltree_node 
ivltree_lookup(rbtree t, int low, int high) 
{
    rbtree_node n = t->root;
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
static void 
ivltree_insert(rbtree t, int low, int high) 
{
	ivltree_node inserted_node = __ivltree_new_node(low, high, RED, NULL, NULL);
	if (t->root == NULL) {
		t->root = &inserted_node->node;
	} else {
		rbtree_node n = t->root;
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
	__insert_case1(t, &inserted_node->node);
}

/**
 * delete the key in the red-black tree
 */
static void 
ivltree_delete(rbtree t, ivltree_node x) 
{
	rbtree_node child;
	if (x == NULL) return;
	rbtree_node n = &x->node;

	// phase 1. fixup the 'm' value until m is not the max value of the path.
	__ivltree_fixup_m(n);

	// phase 2. red black tree deletion
	if (n->left != NULL && n->right != NULL) {
		/* Copy key/value from predecessor and then delete it instead */
		rbtree_node pred = __maximum_node(n->left);
		IVLNODE(n)->low = IVLNODE(pred)->low;
		IVLNODE(n)->high= IVLNODE(pred)->high;
		n = pred;
	}

	assert(n->left == NULL || n->right == NULL);
	child = n->right == NULL ? n->left : n->right;
	if (__node_color(n) == BLACK) {
		n->color = __node_color(child);
		__delete_case1(t, n);
	}
	__replace_node(t, n, child);
	if (n->parent == NULL && child != NULL)
		child->color = BLACK;

	free(IVLNODE(n));
}

#endif //
