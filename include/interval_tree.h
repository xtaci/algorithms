/*******************************************
 * DANIEL'S PRIVATE ALGORITHM IMPLEMENTAIONS
 * Interval-Tree
 * Features:
 * 1. balanced tree
 * 2. O(logn) lookup performance
 * 3. range search [low, high]
 *******************************************/
#ifndef __INTERVAL_TREE_H__
#define __INTERVAL_TREE_H__

#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "generic.h"
#include "stack.h"
#include "double_linked_list.h"


enum inttree_node_color { RED, BLACK };
typedef enum inttree_node_color color;
typedef struct inttree_node_t {
    int low;
    int high;
	int m;
    struct inttree_node_t* left;
    struct inttree_node_t* right;
    struct inttree_node_t* parent;
    enum inttree_node_color color;
} *inttree_node;

typedef struct inttree_t {
    inttree_node root;
} *inttree;

/**
 * Interfaces
 */
inttree inttree_create();
void inttree_insert(inttree t, int low, int high);
inttree_node inttree_lookup(inttree t, int low, int high);
void inttree_delete(inttree t, inttree_node n);

/**
 * Auxillary functions
 */
static inttree_node grandparent(inttree t, inttree_node n);
static inttree_node sibling(inttree t, inttree_node n);
static inttree_node uncle(inttree t, inttree_node n);
static color node_color(inttree_node n);

static inttree_node new_node(inttree t, int low, int high, color node_color);
static void rotate_left(inttree t, inttree_node n);
static void rotate_right(inttree t, inttree_node n);

static void replace_node(inttree t, inttree_node oldn, inttree_node newn);
static void insert_case1(inttree t, inttree_node n);
static void insert_case2(inttree t, inttree_node n);
static void insert_case3(inttree t, inttree_node n);
static void insert_case4(inttree t, inttree_node n);
static void insert_case5(inttree t, inttree_node n);
static inttree_node maximum_node(inttree t, inttree_node root);
static void delete_case1(inttree t, inttree_node n);
static void delete_case2(inttree t, inttree_node n);
static void delete_case3(inttree t, inttree_node n);
static void delete_case4(inttree t, inttree_node n);
static void delete_case5(inttree t, inttree_node n);
static void delete_case6(inttree t, inttree_node n);

static void fixup_max(inttree t,inttree_node x);


/* program should define nil by the macro following */
extern inttree_node nil;
/**
 * this macro should be called once and only.
 */
#define DEFINE_INTTREE_NIL_NODE	 	\
	struct inttree_node_t nil_t = 	\
		{.low = INT_MIN, .high=INT_MIN, .color=BLACK, .left=&nil_t, .right=&nil_t, .parent=&nil_t};\
	inttree_node nil = &nil_t;
 
static inline inttree_node grandparent(inttree t, inttree_node n) {
    assert (n != nil);
    assert (n->parent != nil); /* Not the root inttree_node */
    assert (n->parent->parent != nil); /* Not child of root */
    return n->parent->parent;
}

static inline inttree_node sibling(inttree t, inttree_node n) {
    assert (n != nil);
    assert (n->parent != nil); /* Root inttree_node has no sibling */
    if (n == n->parent->left)
        return n->parent->right;
    else
        return n->parent->left;
}

static inline inttree_node uncle(inttree t, inttree_node n) {
    assert (n != nil);
    assert (n->parent != nil); /* Root inttree_node has no uncle */
    assert (n->parent->parent != nil); /* Children of root have no uncle */
    return sibling(t,n->parent);
}

static inline color node_color(inttree_node n) { return n->color; }

/**
 * inttree_create
 * init an interval tree
 */
inline inttree inttree_create() {
    inttree t = malloc(sizeof(struct inttree_t));
    t->root = nil;
    return t;
}

static inline inttree_node new_node(inttree t, int low, int high, color inttree_node_color) {
    inttree_node result = malloc(sizeof(struct inttree_node_t));
    result->low = low;
    result->high = high;
    result->color = inttree_node_color;
    result->left = nil;
    result->right = nil;
    result->parent = nil;
    return result;
}

/**
 * inttree_lookup
 *
 * search range [low, high] for overlap, return only one element
 * use lookup & delete & insert schema to get multiple elements
 */
inline inttree_node inttree_lookup(inttree t, int low, int high) {
    inttree_node x = t->root;
    while (x != nil && (low > x->high || x->low > high) ) {
		if (x->left !=nil && low <=x->left->m) x = x->left;
		else x = x->right;
    }
    return x;
}

static inline void rotate_left(inttree t, inttree_node n) {
    inttree_node r = n->right;
    replace_node(t, n, r);
    n->right = r->left;
    if (r->left != nil) {
        r->left->parent = n;
    }
    r->left = n;
    n->parent = r;
	// fix m
	n->m = Max(n->left->m, Max(n->right->m, n->high));
    r->m = Max(n->m, Max(r->right->m, r->high));
}

static inline void rotate_right(inttree t, inttree_node n) {
    inttree_node L = n->left;
    replace_node(t, n, L);
    n->left = L->right;
    if (L->right != nil) {
        L->right->parent = n;
    }
    L->right = n;
    n->parent = L;
	// fix m
	n->m = Max(n->left->m, Max(n->right->m,n->high));
    L->m = Max(L->left->m, Max(n->m,L->high));
}

static inline void replace_node(inttree t, inttree_node oldn, inttree_node newn) {
    if (oldn->parent == nil) {
        t->root = newn;
    } else {
        if (oldn == oldn->parent->left)
            oldn->parent->left = newn;
        else
            oldn->parent->right = newn;
    }
    if (newn != nil) {
        newn->parent = oldn->parent;
    }
}

/**
 * inttree_insert
 * insert range [low, high] into red-black tree
 */
inline void inttree_insert(inttree t, int low, int high) {
    inttree_node inserted_node = new_node(t,low, high, RED);
	if (t->root == nil) {
        t->root = inserted_node;
    } else {
        inttree_node n = t->root;
		while (1) {
			if (low == n->low) {
				/* inserted_node isn't going to be used, don't leak it */
				free (inserted_node);
				return;
			} else if (low < n->low) {
				if (n->left == nil) {
					n->left = inserted_node;
					break;
				} else {
					n = n->left;
				}
			} else {
				if (n->right == nil) {
					n->right = inserted_node;
					break;
				} else {
					n = n->right;
				}
			}
		}
		inserted_node->parent = n;
	}
    
    insert_case1(t, inserted_node);
	
	// fix the m all the way up
	fixup_max(t, inserted_node);
}

/**
 *  Travels up to the root fixing the maxHigh fields after
 *  an insertion or deletion 
 */
static inline void fixup_max(inttree t,inttree_node x)
{
	while(x != nil) {
		x->m = Max(x->high,Max(x->left->m,x->right->m));
		x=x->parent;
	}
}

static inline void insert_case1(inttree t, inttree_node n) {
    if (n->parent == nil)
        n->color = BLACK;
    else
        insert_case2(t, n);
}

static inline void insert_case2(inttree t, inttree_node n) {
    if (node_color(n->parent) == BLACK)
        return; /* Tree is still valid */
    else
        insert_case3(t, n);
}

static inline void insert_case3(inttree t, inttree_node n) {
    if (node_color(uncle(t,n)) == RED) {
        n->parent->color = BLACK;
        uncle(t,n)->color = BLACK;
        grandparent(t,n)->color = RED;
        insert_case1(t, grandparent(t,n));
    } else {
        insert_case4(t, n);
    }
}

static inline void insert_case4(inttree t, inttree_node n) {
    if (n == n->parent->right && n->parent == grandparent(t,n)->left) {
        rotate_left(t, n->parent);
        n = n->left;
    } else if (n == n->parent->left && n->parent == grandparent(t,n)->right) {
        rotate_right(t, n->parent);
        n = n->right;
    }
    insert_case5(t, n);
}

static inline void insert_case5(inttree t, inttree_node n) {
    n->parent->color = BLACK;
    grandparent(t,n)->color = RED;
    if (n == n->parent->left && n->parent == grandparent(t,n)->left) {
        rotate_right(t, grandparent(t,n));
    } else {
        assert (n == n->parent->right && n->parent == grandparent(t,n)->right);
        rotate_left(t, grandparent(t,n));
    }
}

/**
 * delete the key in the red-black tree
 */
inline void inttree_delete(inttree t, inttree_node n) {
    inttree_node child;
    if (n == nil) return;
    if (n->left != nil && n->right != nil) {
        /* Copy key/value from predecessor and then delete it instead */
        inttree_node pred = maximum_node(t, n->left);
        n->low = pred->low;
        n->high= pred->high;
        n = pred;
    }

    assert(n->left == nil || n->right == nil);
    child = n->right == nil ? n->left  : n->right;
    if (node_color(n) == BLACK) {
        n->color = node_color(child);
        delete_case1(t, n);
    }
    replace_node(t, n, child);
    if (n->parent == nil && child != nil)
        child->color = BLACK;
    free(n);

	// fix up max 
	fixup_max(t, child);
}

static inline inttree_node maximum_node(inttree t, inttree_node n) {
    while (n->right != nil) {
        n = n->right;
    }
    return n;
}
static inline void delete_case1(inttree t, inttree_node n) {
    if (n->parent == nil)
        return;
    else
        delete_case2(t, n);
}
static inline void delete_case2(inttree t, inttree_node n) {
    if (node_color(sibling(t,n)) == RED) {
        n->parent->color = RED;
        sibling(t,n)->color = BLACK;
        if (n == n->parent->left)
            rotate_left(t, n->parent);
        else
            rotate_right(t, n->parent);
    }
    delete_case3(t, n);
}

static inline void delete_case3(inttree t, inttree_node n) {
    if (node_color(n->parent) == BLACK &&
        node_color(sibling(t,n)) == BLACK &&
        node_color(sibling(t,n)->left) == BLACK &&
        node_color(sibling(t,n)->right) == BLACK)
    {
        sibling(t,n)->color = RED;
        delete_case1(t, n->parent);
    }
    else
        delete_case4(t, n);
}

static inline void delete_case4(inttree t, inttree_node n) {
    if (node_color(n->parent) == RED &&
        node_color(sibling(t,n)) == BLACK &&
        node_color(sibling(t,n)->left) == BLACK &&
        node_color(sibling(t,n)->right) == BLACK)
    {
        sibling(t,n)->color = RED;
        n->parent->color = BLACK;
    }
    else
        delete_case5(t, n);
}

static inline void delete_case5(inttree t, inttree_node n) {
    if (n == n->parent->left &&
        node_color(sibling(t,n)) == BLACK &&
        node_color(sibling(t,n)->left) == RED &&
        node_color(sibling(t,n)->right) == BLACK)
    {
        sibling(t,n)->color = RED;
        sibling(t,n)->left->color = BLACK;
        rotate_right(t, sibling(t,n));
    }
    else if (n == n->parent->right &&
             node_color(sibling(t,n)) == BLACK &&
             node_color(sibling(t,n)->right) == RED &&
             node_color(sibling(t,n)->left) == BLACK)
    {
        sibling(t,n)->color = RED;
        sibling(t,n)->right->color = BLACK;
        rotate_left(t, sibling(t,n));
    }
    delete_case6(t, n);
}

static inline void delete_case6(inttree t, inttree_node n) {
    sibling(t,n)->color = node_color(n->parent);
    n->parent->color = BLACK;
    if (n == n->parent->left) {
        assert (node_color(sibling(t,n)->right) == RED);
        sibling(t,n)->right->color = BLACK;
        rotate_left(t, n->parent);
    }
    else
    {
        assert (node_color(sibling(t,n)->left) == RED);
        sibling(t,n)->left->color = BLACK;
        rotate_right(t, n->parent);
    }
}

#endif
