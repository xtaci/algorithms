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


enum dostree_node_color { RED, BLACK };
typedef enum dostree_node_color color;
typedef struct dostree_node_t {
    int key;
	int size;
    struct dostree_node_t* left;
    struct dostree_node_t* right;
    struct dostree_node_t* parent;
    enum dostree_node_color color;
} *dostree_node;

typedef struct dostree_t {
    dostree_node root;
} *dostree;

/**
 * Interfaces
 */
inline dostree dostree_create();
inline void dostree_insert(dostree t, int key);
inline dostree_node dostree_lookup(dostree_node n, int i);
inline void dostree_delete(dostree t, dostree_node node);

/**
 * Auxillary functions
 */
static inline dostree_node grandparent(dostree t, dostree_node n);
static inline dostree_node sibling(dostree t, dostree_node n);
static inline dostree_node uncle(dostree t, dostree_node n);
static inline color node_color(dostree_node n);

static inline dostree_node new_node(dostree t, int key, color node_color);
static inline void rotate_left(dostree t, dostree_node n);
static inline void rotate_right(dostree t, dostree_node n);

static inline void replace_node(dostree t, dostree_node oldn, dostree_node newn);
static inline void insert_case1(dostree t, dostree_node n);
static inline void insert_case2(dostree t, dostree_node n);
static inline void insert_case3(dostree t, dostree_node n);
static inline void insert_case4(dostree t, dostree_node n);
static inline void insert_case5(dostree t, dostree_node n);
static inline dostree_node maximum_node(dostree t, dostree_node root);
static inline void delete_case1(dostree t, dostree_node n);
static inline void delete_case2(dostree t, dostree_node n);
static inline void delete_case3(dostree t, dostree_node n);
static inline void delete_case4(dostree t, dostree_node n);
static inline void delete_case5(dostree t, dostree_node n);
static inline void delete_case6(dostree t, dostree_node n);

static void fixup_size(dostree t, dostree_node x);


#ifdef __COMPILE_OBJ__
struct dostree_node_t dos_nil_t = 
	{.key = INT_MIN, .size=0, .color=BLACK, .left=&dos_nil_t, .right=&dos_nil_t, .parent=&dos_nil_t};
dostree_node dos_nil = &dos_nil_t;
#endif
 

/**
 *  Travels up to the root fixing the size fields after
 *  an insertion or deletion 
 */
static inline void fixup_size(dostree t, dostree_node x)
{
	while(x != dos_nil) {
		x->size = x->left->size + x->right->size + 1;
		x = x->parent;
	}
}
static inline dostree_node grandparent(dostree t, dostree_node n) {
    assert (n != dos_nil);
    assert (n->parent != dos_nil); /* Not the root dostree_node */
    assert (n->parent->parent != dos_nil); /* Not child of root */
    return n->parent->parent;
}

static inline dostree_node sibling(dostree t, dostree_node n) {
    assert (n != dos_nil);
    assert (n->parent != dos_nil); /* Root dostree_node has no sibling */
    if (n == n->parent->left)
        return n->parent->right;
    else
        return n->parent->left;
}

static inline dostree_node uncle(dostree t, dostree_node n) {
    assert (n != dos_nil);
    assert (n->parent != dos_nil); /* Root dostree_node has no uncle */
    assert (n->parent->parent != dos_nil); /* Children of root have no uncle */
    return sibling(t,n->parent);
}

static inline color node_color(dostree_node n) { return n->color; }

/**
 * dostree_create
 * init an interval tree
 */
inline dostree dostree_create() {
    dostree t = malloc(sizeof(struct dostree_t));
	t->root = dos_nil;
    return t;
}

static inline dostree_node new_node(dostree t, int key, color dostree_node_color) {
    dostree_node result = malloc(sizeof(struct dostree_node_t));
    result->key = key;
    result->color = dostree_node_color;
    result->left = dos_nil;
    result->right = dos_nil;
    result->parent = dos_nil;
    return result;
}

/**
 * dostree_lookup
 *
 * select the i-th largest element
 */
inline dostree_node dostree_lookup(dostree_node n, int i) {
	if (n == dos_nil) return dos_nil;
	int size = n->left->size + 1;
	if(i == size) return n;
	if(i < size ) return dostree_lookup(n->left, i);
	else return dostree_lookup(n->right, i-size);
}

static inline void rotate_left(dostree t, dostree_node n) {
    dostree_node r = n->right;
    replace_node(t, n, r);
    n->right = r->left;
    if (r->left != dos_nil) {
        r->left->parent = n;
    }
    r->left = n;
    n->parent = r;

	// recalc size
	n->size = n->left->size + n->right->size + 1;
	r->size = r->left->size + r->right->size + 1;
}

static inline void rotate_right(dostree t, dostree_node n) {
    dostree_node L = n->left;
    replace_node(t, n, L);
    n->left = L->right;
    if (L->right != dos_nil) {
        L->right->parent = n;
    }
    L->right = n;
    n->parent = L;

	// recalc size
	n->size = n->left->size + n->right->size + 1;
	L->size = L->left->size + L->right->size + 1;
}

static inline void replace_node(dostree t, dostree_node oldn, dostree_node newn) {
    if (oldn->parent == dos_nil) {
        t->root = newn;
    } else {
        if (oldn == oldn->parent->left)
            oldn->parent->left = newn;
        else
            oldn->parent->right = newn;
    }
    if (newn != dos_nil) {
        newn->parent = oldn->parent;
    }
}

/**
 * dostree_insert
 * insert a new key into the dos tree
 */
inline void dostree_insert(dostree t, int key) {
    dostree_node inserted_node = new_node(t, key, RED);
    if (t->root == dos_nil) {
        t->root = inserted_node;
	}
	else {
    	dostree_node n = t->root;
		while (1) {
			if (key == n->key) {
				/* inserted_node isn't going to be used, don't leak it */
				free (inserted_node);
				return;
			} else if (key < n->key) {
				if (n->left == dos_nil) {
					n->left = inserted_node;
					break;
				} else {
					n = n->left;
				}
			} else {
				if (n->right == dos_nil) {
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

	// fixup all size
	fixup_size(t, inserted_node);
}

static inline void insert_case1(dostree t, dostree_node n) {
    if (n->parent == dos_nil)
        n->color = BLACK;
    else
        insert_case2(t, n);
}

static inline void insert_case2(dostree t, dostree_node n) {
    if (node_color(n->parent) == BLACK)
        return; /* Tree is still valid */
    else
        insert_case3(t, n);
}

static inline void insert_case3(dostree t, dostree_node n) {
    if (node_color(uncle(t,n)) == RED) {
        n->parent->color = BLACK;
        uncle(t,n)->color = BLACK;
        grandparent(t,n)->color = RED;
        insert_case1(t, grandparent(t,n));
    } else {
        insert_case4(t, n);
    }
}

static inline void insert_case4(dostree t, dostree_node n) {
    if (n == n->parent->right && n->parent == grandparent(t,n)->left) {
        rotate_left(t, n->parent);
        n = n->left;
    } else if (n == n->parent->left && n->parent == grandparent(t,n)->right) {
        rotate_right(t, n->parent);
        n = n->right;
    }
    insert_case5(t, n);
}

static inline void insert_case5(dostree t, dostree_node n) {
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
inline void dostree_delete(dostree t, dostree_node n) {
    dostree_node child;
    if (n == dos_nil) return;
    if (n->left != dos_nil && n->right != dos_nil) {
        /* Copy key/value from predecessor and then delete it instead */
        dostree_node pred = maximum_node(t, n->left);
        n->key = pred->key;
		n->size = pred->size;
        n = pred;
    }

    assert(n->left == dos_nil || n->right == dos_nil);
    child = n->right == dos_nil ? n->left  : n->right;
    if (node_color(n) == BLACK) {
        n->color = node_color(child);
        delete_case1(t, n);
    }
    replace_node(t, n, child);
    if (n->parent == dos_nil && child != dos_nil)
        child->color = BLACK;
    free(n);
	
	// fix up size
	fixup_size(t, child);
}

static inline dostree_node maximum_node(dostree t, dostree_node n) {
    while (n->right != dos_nil) {
        n = n->right;
    }
    return n;
}
static inline void delete_case1(dostree t, dostree_node n) {
    if (n->parent == dos_nil)
        return;
    else
        delete_case2(t, n);
}
static inline void delete_case2(dostree t, dostree_node n) {
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

static inline void delete_case3(dostree t, dostree_node n) {
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

static inline void delete_case4(dostree t, dostree_node n) {
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

static inline void delete_case5(dostree t, dostree_node n) {
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

static inline void delete_case6(dostree t, dostree_node n) {
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
