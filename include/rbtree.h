/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * RED-BLACK TREE
 *
 * Features:
 * 1. balanced tree
 * 2. O(logn) lookup performance
 *
 * http://en.wikipedia.org/wiki/Red_black_tree
 *     
 ******************************************************************************/

#ifndef __RBTREE_H__
#define __RBTREE_H__
#include <stdint.h>

enum rbtree_node_color { RED, BLACK };
typedef enum rbtree_node_color color;
typedef struct rbtree_node_t {
    uintptr_t key;
    uintptr_t value;
    struct rbtree_node_t* left;
    struct rbtree_node_t* right;
    struct rbtree_node_t* parent;
    enum rbtree_node_color color;
} *rbtree_node;

typedef struct rbtree_t {
    rbtree_node root;
} *rbtree;

/**
 * Interfaces
 */
typedef int (*compare_func)(uintptr_t left, uintptr_t right);
static rbtree rbtree_create();
static void rbtree_insert(rbtree t, uintptr_t key, uintptr_t value, compare_func compare);
static uintptr_t rbtree_lookup(rbtree t, uintptr_t key, compare_func compare);
static void rbtree_delete(rbtree t, uintptr_t key, compare_func compare);


/**
 * Auxillary functions
 */
static rbtree_node __grandparent(rbtree_node n);
static rbtree_node __sibling(rbtree_node n);
static rbtree_node __uncle(rbtree_node n);
static color __node_color(rbtree_node n);

static rbtree_node __new_node(uintptr_t key, uintptr_t value, color node_color, rbtree_node left, rbtree_node right);
static rbtree_node __lookup_node(rbtree t, uintptr_t key, compare_func compare);
static void __rotate_left(rbtree t, rbtree_node n);
static void __rotate_right(rbtree t, rbtree_node n);

static void __replace_node(rbtree t, rbtree_node oldn, rbtree_node newn);
static void __insert_case1(rbtree t, rbtree_node n);
static void __insert_case2(rbtree t, rbtree_node n);
static void __insert_case3(rbtree t, rbtree_node n);
static void __insert_case4(rbtree t, rbtree_node n);
static void __insert_case5(rbtree t, rbtree_node n);
static rbtree_node __maximum_node(rbtree_node root);
static void __delete_case1(rbtree t, rbtree_node n);
static void __delete_case2(rbtree t, rbtree_node n);
static void __delete_case3(rbtree t, rbtree_node n);
static void __delete_case4(rbtree t, rbtree_node n);
static void __delete_case5(rbtree t, rbtree_node n);
static void __delete_case6(rbtree t, rbtree_node n);

static rbtree_node 
__grandparent(rbtree_node n) 
{
    assert (n != NULL);
    assert (n->parent != NULL); /* Not the root rbtree_node */
    assert (n->parent->parent != NULL); /* Not child of root */
    return n->parent->parent;
}

static rbtree_node 
__sibling(rbtree_node n) 
{
    assert (n != NULL);
    assert (n->parent != NULL); /* Root rbtree_node has no sibling */
    if (n == n->parent->left)
        return n->parent->right;
    else
        return n->parent->left;
}

static rbtree_node 
__uncle(rbtree_node n) 
{
    assert (n != NULL);
    assert (n->parent != NULL); /* Root rbtree_node has no uncle */
    assert (n->parent->parent != NULL); /* Children of root have no uncle */
    return __sibling(n->parent);
}

static color 
__node_color(rbtree_node n) 
{
    return n == NULL ? BLACK : n->color;
}

/**
 * rbtree_create
 * init a red-black tree 
 */
static rbtree 
rbtree_create() 
{
    rbtree t = malloc(sizeof(struct rbtree_t));
    t->root = NULL;
    return t;
}

static rbtree_node 
__new_node(uintptr_t key, uintptr_t value, color rbtree_node_color, rbtree_node left, rbtree_node right) {
    rbtree_node result = malloc(sizeof(struct rbtree_node_t));
    result->key = key;
    result->value = value;
    result->color = rbtree_node_color;
    result->left = left;
    result->right = right;
    if (left  != NULL)  left->parent = result;
    if (right != NULL) right->parent = result;
    result->parent = NULL;
    return result;
}

static rbtree_node 
__lookup_node(rbtree t, uintptr_t key, compare_func compare) {
    rbtree_node n = t->root;
    while (n != NULL) {
        int comp_result = compare(key, n->key);
        if (comp_result == 0) {
            return n;
        } else if (comp_result < 0) {
            n = n->left;
        } else {
            assert(comp_result > 0);
            n = n->right;
        }
    }
    return n;
}

/**
 * rbtree_lookup
 * search in red-black tree
 */
static uintptr_t 
rbtree_lookup(rbtree t, uintptr_t key, compare_func compare) 
{
    rbtree_node n = __lookup_node(t, key, compare);
    return n == NULL ? 0 : n->value;
}

static void 
__rotate_left(rbtree t, rbtree_node n) 
{
    rbtree_node r = n->right;
    __replace_node(t, n, r);
    n->right = r->left;
    if (r->left != NULL) {
        r->left->parent = n;
    }
    r->left = n;
    n->parent = r;
}

static void 
__rotate_right(rbtree t, rbtree_node n) 
{
    rbtree_node L = n->left;
    __replace_node(t, n, L);
    n->left = L->right;
    if (L->right != NULL) {
        L->right->parent = n;
    }
    L->right = n;
    n->parent = L;
}

static void 
__replace_node(rbtree t, rbtree_node oldn, rbtree_node newn) 
{
    if (oldn->parent == NULL) {
        t->root = newn;
    } else {
        if (oldn == oldn->parent->left)
            oldn->parent->left = newn;
        else
            oldn->parent->right = newn;
    }
    if (newn != NULL) {
        newn->parent = oldn->parent;
    }
}

/**
 * rbtree_insert
 * insert a key-value pair into red-black tree
 * you must specify your own compare function
 */
static void 
rbtree_insert(rbtree t, uintptr_t key, uintptr_t value, compare_func compare) 
{
    rbtree_node inserted_node = __new_node(key, value, RED, NULL, NULL);
    if (t->root == NULL) {
        t->root = inserted_node;
    } else {
        rbtree_node n = t->root;
        while (1) {
            int comp_result = compare(key, n->key);
            if (comp_result == 0) {
                n->value = value;
                /* inserted_node isn't going to be used, don't leak it */
                free (inserted_node);
                return;
            } else if (comp_result < 0) {
                if (n->left == NULL) {
                    n->left = inserted_node;
                    break;
                } else {
                    n = n->left;
                }
            } else {
                assert (comp_result > 0);
                if (n->right == NULL) {
                    n->right = inserted_node;
                    break;
                } else {
                    n = n->right;
                }
            }
        }
        inserted_node->parent = n;
    }
    __insert_case1(t, inserted_node);
}

static void 
__insert_case1(rbtree t, rbtree_node n) 
{
    if (n->parent == NULL)
        n->color = BLACK;
    else
        __insert_case2(t, n);
}

static void 
__insert_case2(rbtree t, rbtree_node n) 
{
    if (__node_color(n->parent) == BLACK)
        return; /* Tree is still valid */
    else
        __insert_case3(t, n);
}

static void 
__insert_case3(rbtree t, rbtree_node n) 
{
    if (__node_color(__uncle(n)) == RED) {
        n->parent->color = BLACK;
        __uncle(n)->color = BLACK;
        __grandparent(n)->color = RED;
        __insert_case1(t, __grandparent(n));
    } else {
        __insert_case4(t, n);
    }
}

static void 
__insert_case4(rbtree t, rbtree_node n) 
{
    if (n == n->parent->right && n->parent == __grandparent(n)->left) {
        __rotate_left(t, n->parent);
        n = n->left;
    } else if (n == n->parent->left && n->parent == __grandparent(n)->right) {
        __rotate_right(t, n->parent);
        n = n->right;
    }
    __insert_case5(t, n);
}

static void 
__insert_case5(rbtree t, rbtree_node n) 
{
    n->parent->color = BLACK;
    __grandparent(n)->color = RED;
    if (n == n->parent->left && n->parent == __grandparent(n)->left) {
        __rotate_right(t, __grandparent(n));
    } else {
        assert (n == n->parent->right && n->parent == __grandparent(n)->right);
        __rotate_left(t, __grandparent(n));
    }
}

/**
 * delete the key in the red-black tree
 */
static void 
rbtree_delete(rbtree t, uintptr_t key, compare_func compare) 
{
    rbtree_node child;
    rbtree_node n = __lookup_node(t, key, compare);
    if (n == NULL) return;  /* Key not found, do nothing */
    if (n->left != NULL && n->right != NULL) {
        /* Copy key/value from predecessor and then delete it instead */
        rbtree_node pred = __maximum_node(n->left);
        n->key   = pred->key;
        n->value = pred->value;
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
    free(n);
}

static rbtree_node 
__maximum_node(rbtree_node n) 
{
    assert (n != NULL);
    while (n->right != NULL) {
        n = n->right;
    }
    return n;
}

static void 
__delete_case1(rbtree t, rbtree_node n) 
{
    if (n->parent == NULL)
        return;
    else
        __delete_case2(t, n);
}

static void 
__delete_case2(rbtree t, rbtree_node n) 
{
    if (__node_color(__sibling(n)) == RED) {
        n->parent->color = RED;
        __sibling(n)->color = BLACK;
        if (n == n->parent->left)
            __rotate_left(t, n->parent);
        else
            __rotate_right(t, n->parent);
    }
    __delete_case3(t, n);
}

static void 
__delete_case3(rbtree t, rbtree_node n) 
{
    if (__node_color(n->parent) == BLACK &&
        __node_color(__sibling(n)) == BLACK &&
        __node_color(__sibling(n)->left) == BLACK &&
        __node_color(__sibling(n)->right) == BLACK)
    {
        __sibling(n)->color = RED;
        __delete_case1(t, n->parent);
    }
    else
        __delete_case4(t, n);
}

static void 
__delete_case4(rbtree t, rbtree_node n) 
{
    if (__node_color(n->parent) == RED &&
        __node_color(__sibling(n)) == BLACK &&
        __node_color(__sibling(n)->left) == BLACK &&
        __node_color(__sibling(n)->right) == BLACK)
    {
        __sibling(n)->color = RED;
        n->parent->color = BLACK;
    }
    else
        __delete_case5(t, n);
}

static void 
__delete_case5(rbtree t, rbtree_node n) {
    if (n == n->parent->left &&
        __node_color(__sibling(n)) == BLACK &&
        __node_color(__sibling(n)->left) == RED &&
        __node_color(__sibling(n)->right) == BLACK)
    {
        __sibling(n)->color = RED;
        __sibling(n)->left->color = BLACK;
        __rotate_right(t, __sibling(n));
    }
    else if (n == n->parent->right &&
             __node_color(__sibling(n)) == BLACK &&
             __node_color(__sibling(n)->right) == RED &&
             __node_color(__sibling(n)->left) == BLACK)
    {
        __sibling(n)->color = RED;
        __sibling(n)->right->color = BLACK;
        __rotate_left(t, __sibling(n));
    }
    __delete_case6(t, n);
}

static void 
__delete_case6(rbtree t, rbtree_node n) 
{
    __sibling(n)->color = __node_color(n->parent);
    n->parent->color = BLACK;
    if (n == n->parent->left) {
        assert (__node_color(__sibling(n)->right) == RED);
        __sibling(n)->right->color = BLACK;
        __rotate_left(t, n->parent);
    }
    else
    {
        assert (__node_color(__sibling(n)->left) == RED);
        __sibling(n)->left->color = BLACK;
        __rotate_right(t, n->parent);
    }
}

#endif
