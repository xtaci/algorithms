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
 * http://en.literateprograms.org/Red-black_tree_(C)
 ******************************************************************************/

#ifndef ALGO_RBTREE_H__
#define ALGO_RBTREE_H__
#include <stdio.h>
#include <stdint.h>
#include <stdexcept>
#include "rbtree_defs.h"

namespace alg {
	template<typename KeyT, typename ValueT>
		class RBTree:public RBTreeAbstract {	
			private:
				// a default Key-Value node.
				struct KVNode: public rbtree_node_t {
					KeyT key;
					ValueT value;
				};

#define KVNODE(node) static_cast<KVNode *>(node)
				void destruct(KVNode * n) {
					if (n==NULL) return;
					destruct(KVNODE(n->left));
					destruct(KVNODE(n->right));
					delete n;
				}

			public:
				~RBTree() {
					destruct(KVNODE(get_root()));
				}

				/**
				 * rbtree_insert
				 * insert a key-value pair into red-black tree
				 */
				void insert(const KeyT & key, const ValueT & value) {
					KVNode * inserted_node = new_node(key, value, RED, NULL, NULL);
					if (get_root() == NULL) {
						set_root(inserted_node);
					} else {
						KVNode * n = KVNODE(get_root());
						while (1) {
							if (key == n->key) {
								n->value = value;
								/* inserted_node isn't going to be used, don't leak it */
								delete (inserted_node);
								return;
							} else if (key < n->key) {
								if (n->left == NULL) {
									n->left = inserted_node;
									break;
								} else {
									n = static_cast<KVNode*>(n->left);
								}
							} else {
								assert (key > n->key);
								if (n->right == NULL) {
									n->right = inserted_node;
									break;
								} else {
									n = static_cast<KVNode*>(n->right);
								}
							}
						}
						inserted_node->parent = n;
					}
					insert_case1(inserted_node);
				}

				/**
				 * contain test
				 */
				bool contains(KeyT key) {
					if (lookup_node(key))
						return true;
					return false;
				}

				/**
				 * rbtree_lookup
				 * search in red-black tree
				 */
				ValueT operator [] (KeyT key) {
					KVNode * n = lookup_node(key);
					if (n==NULL) throw std::out_of_range ("no such key");
					return n->value;
				}

				/**
				 * delete the key in the red-black tree
				 */
				void delete_key(KeyT key) {
					rbtree_node child;
					KVNode * n = lookup_node(key);
					if (n == NULL) return;  /* Key not found, do nothing */
					if (n->left != NULL && n->right != NULL) {
						/* Copy key/value from predecessor and then delete it instead */
						KVNode * pred = static_cast<KVNode*>(maximum_node(n->left));
						n->key   = pred->key;
						n->value = pred->value;
						n = pred;
					}

					assert(n->left == NULL || n->right == NULL);
					child = n->right == NULL ? n->left  : n->right;
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
					print_helper(KVNODE(get_root()), 0);
					puts("");
				}
			protected:
				void print_helper(KVNode * n, int indent) {
					int i;
					if (n == NULL) {
						fputs("<empty tree>", stdout);
						return;
					}
					if (n->right != NULL) {
						print_helper(KVNODE(n->right), indent + INDENT_STEP);
					}
					for(i=0; i<indent; i++)
						fputs(" ", stdout);
					if (n->color == BLACK)
						printf("%d\n", (int)n->key);
					else
						printf("<%d>\n", (int)n->key);
					if (n->left != NULL) {
						print_helper(KVNODE(n->left), indent + INDENT_STEP);
					}
				}

				KVNode * new_node(KeyT key, ValueT value, color rbtree_node_color, rbtree_node left, rbtree_node right) {
					KVNode * result =new KVNode;
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

				KVNode * lookup_node(KeyT key) {
					KVNode * n = KVNODE(get_root());
					while (n != NULL) {
						if (key == n->key) {
							return n;
						} else if (key < n->key) {
							n = KVNODE(n->left);
						} else {
							n = KVNODE(n->right);
						}
					}
					return n;
				}
		};
}

#endif
