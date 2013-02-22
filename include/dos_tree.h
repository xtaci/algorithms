/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * DYNAMIC ORDER STATISTIC
 *
 * Features:
 * 1. based on red-black tree
 * 2. O(logn) lookup time 
 * 3. Select the i-th largest element
 *
 * http://en.wikipedia.org/wiki/Order_statistic
 *
 ******************************************************************************/

#ifndef __DOS_TREE_H__
#define __DOS_TREE_H__

#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "generic.h"
#include "stack.h"
#include "double_linked_list.h"
#include "rbtree.h"

/**
 * dynamic order stat node structure definition
 */
typedef struct dostree_node_t {
	int key;	// the key	
	int size;	// the size of this subtree
	struct rbtree_node_t node;	// also, it's a red-black tree node.
} *dostree_node;

#define DOSNODE(rbnode) \
	((dostree_node)((char *)rbnode - (unsigned long)(&((dostree_node)0)->node)))

#define DOSNODE_SIZE(rbnode) \
	(rbnode?DOSNODE(rbnode)->size:0)

/**
 * Interfaces
 */
static inline rbtree dostree_create();
static inline void dostree_insert(rbtree t, int key);
static inline dostree_node dostree_lookup(rbtree_node n, int i);
static inline void dostree_delete(rbtree t, dostree_node node);

static void __fixup_size(rbtree_node x);
static inline dostree_node __dostree_new_node(int key, color 
			rbtree_node_color, rbtree_node left, rbtree_node right);
 

/**
 * first, we recalc the child size,
 * then, travels up to the root.
 */
static inline void 
__fixup_size(rbtree_node n)
{	
	if (n==NULL) return;

	// fix children
	rbtree_node child;
	if ((child = n->left)) {
		DOSNODE(child)->size = DOSNODE_SIZE(child->left) + DOSNODE_SIZE(child->right) + 1;
	}

	if ((child = n->right)) {
		DOSNODE(child)->size = DOSNODE_SIZE(child->left) + DOSNODE_SIZE(child->right) + 1;
	}

	// fix up to the root
	while(n != NULL) {
		// fix sibling, possible rotation.
		rbtree_node s;
		if (n->parent !=NULL && (s=__sibling(n))!=NULL) {
			DOSNODE(s)->size = DOSNODE_SIZE(s->left) + DOSNODE_SIZE(s->right)+ 1;
		}

		DOSNODE(n)->size = DOSNODE_SIZE(n->left) + DOSNODE_SIZE(n->right)+ 1;
		n = n->parent;
	}
}

/**
 * dostree_create
 * init an  dynamic order stat tree, same as red-black tree
 */
static inline rbtree 
dostree_create() 
{
	rbtree t = malloc(sizeof(struct rbtree_t));
	t->root = NULL;
	return t;
}

static inline dostree_node 
__dostree_new_node(int key, color rbtree_node_color, rbtree_node left, rbtree_node right) 
{
	dostree_node result = malloc(sizeof(struct dostree_node_t));
	result->key = key;
	result->node.color = rbtree_node_color;
	result->node.left = NULL;
	result->node.right = NULL;
	if(left !=NULL) left->parent = &result->node;
	if(right!=NULL) right->parent = &result->node;
	result->node.parent = NULL;
	return result;
}

/**
 * dostree_lookup
 *
 * select the i-th largest element
 */
static inline dostree_node 
dostree_lookup(rbtree_node n, int i) 
{
	if (n == NULL) return NULL;	 // beware of NULL pointer
	int size = DOSNODE_SIZE(n->left) + 1;

	if(i == size) return DOSNODE(n);
	if(i < size ) return dostree_lookup(n->left, i);
	else return dostree_lookup(n->right, i-size);
}

/**
 * dostree_insert
 * insert a new key into the dos tree
 */
static inline void 
dostree_insert(rbtree t, int key) 
{
	dostree_node inserted_node = __dostree_new_node(key, RED, NULL, NULL);
	rbtree_node n = t->root;

	if (t->root == NULL) {
		t->root = &inserted_node->node;
	}
	else {
		while (1) {
			if (key == DOSNODE(n)->key) {
				/* inserted_node isn't going to be used, don't leak it */
				free (inserted_node);
				return;
			} else if (key < DOSNODE(n)->key) {
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

	// fixup all size
	__fixup_size(&inserted_node->node);
}

/**
 * delete the key in the red-black tree
 */
static inline void
dostree_delete(rbtree t, dostree_node x)
{
	rbtree_node child;
	if (x == NULL) return;
	rbtree_node n = &x->node;

	if (n->left != NULL && n->right != NULL) {
		/* Copy key/value from predecessor and then delete it instead */
		rbtree_node pred = __maximum_node(n->left);
		DOSNODE(n)->key = DOSNODE(pred)->key;
		DOSNODE(n)->size = DOSNODE(pred)->size;
		n = pred;
	}

	assert(n->left == NULL || n->right == NULL);
	child = n->right == NULL ? n->left  : n->right;
	if (__node_color(n) == BLACK) {
		n->color = __node_color(child);
		__delete_case1(t, n);
	}
	__replace_node(t, n, child);
	if (n->parent == NULL && child != NULL)
		child->color = BLACK;

	// fix up size
	__fixup_size(n);
	free(DOSNODE(n));
}

#endif
