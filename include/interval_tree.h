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

/**
 * Interfaces
 */
static inline rbtree ivltree_create();
static inline void ivltree_insert(rbtree t, int low, int high);
static inline ivltree_node ivltree_lookup(rbtree t, int low, int high);
static inline void ivltree_delete(rbtree t, ivltree_node n);

/**
 * Auxillary functions
 */
static inline ivltree_node __ivltree_new_node(int low, int high, 
			color rbtree_node_color, rbtree_node left, rbtree_node right);
static inline void __fixup_max(rbtree_node n);

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
    return t;
}

/**
 *  malloc a new node, and set default vales.
 */
static inline ivltree_node 
__ivltree_new_node(int low, int high, 
		color rbtree_node_color, rbtree_node left, rbtree_node right) 
{
	ivltree_node result = malloc(sizeof(struct ivltree_node_t));
	result->low = low;
	result->high = high;
	result->node.color = rbtree_node_color;
	result->node.left = left;
	result->node.right = right;
	if(left !=NULL) left->parent = &result->node;
	if(right!=NULL) right->parent = &result->node;
	result->node.parent = NULL;
	return result;
}


#define IVLNODE(rbnode) \
	((ivltree_node)((char *)rbnode - (unsigned long)(&((ivltree_node)0)->node)))

/**
 * ivltree_lookup
 *
 * search range [low, high] for overlap, return only one element
 * use lookup & delete & insert schema to get multiple elements
 *
 * NULL is returned if not found.
 */
static inline ivltree_node 
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
static inline void 
ivltree_insert(rbtree t, int low, int high) 
{
	ivltree_node inserted_node = __ivltree_new_node(low, high, RED, NULL, NULL);
	if (t->root == NULL) {
		t->root = &inserted_node->node;
	} else {
		rbtree_node n = t->root;
		while (1) {
			if (low == IVLNODE(n)->low) {
				/* inserted_node isn't going to be used, don't leak it */
				free (inserted_node);
				return;
			} else if (low < IVLNODE(n)->low) {
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

	// fix the m all the way up
	__fixup_max(&inserted_node->node);
}

/**
 * first, we recalc the sibling  & childsize,
 * then travels up to the root fixing the m field.
 */
static inline void 
__fixup_max(rbtree_node n)
{
	if (n==NULL) return;

	// fix children
	rbtree_node child;
	if ((child = n->left)) {
		int max_left = child->left?IVLNODE(child->left)->m:INT_MIN;	
		int max_right = child->right?IVLNODE(child->right)->m:INT_MIN;	
		IVLNODE(child)->m = Max(IVLNODE(child)->high, Max(max_left, max_right));
	}

	if ((child = n->right)) {
		int max_left = child->left?IVLNODE(child->left)->m:INT_MIN;	
		int max_right = child->right?IVLNODE(child->right)->m:INT_MIN;	
		IVLNODE(child)->m = Max(IVLNODE(child)->high, Max(max_left, max_right));
	}

	// fix sibling
	rbtree_node s;
	if (n->parent !=NULL && (s=__sibling(n))!=NULL) {
		int max_left = s->left?IVLNODE(s->left)->m:INT_MIN;	
		int max_right = s->right?IVLNODE(s->right)->m:INT_MIN;	
		IVLNODE(s)->m = Max(IVLNODE(s)->high, Max(max_left, max_right));
	}

	// fix up to the root
	while(n != NULL) {
		int max_left = n->left?IVLNODE(n->left)->m:INT_MIN;	
		int max_right = n->right?IVLNODE(n->right)->m:INT_MIN;	

		IVLNODE(n)->m = Max(IVLNODE(n)->high, Max(max_left, max_right));
		n=n->parent;
	}
}

/**
 * delete the key in the red-black tree
 */
static inline void 
ivltree_delete(rbtree t, ivltree_node x) 
{
	rbtree_node child;
	if (x == NULL) return;
	rbtree_node n = &x->node;

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

	// fix up max 
	__fixup_max(n);
	free(IVLNODE(n));
}

#endif //
