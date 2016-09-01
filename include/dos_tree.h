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

#ifndef ALGO_DOS_TREE_H__
#define ALGO_DOS_TREE_H__

#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "generic.h"
#include "stack.h"
#include "double_linked_list.h"
#include "rbtree.h"

namespace alg {
	class DosTree:public RBTreeAbstract {
		public:
			/**
			 * dynamic order stat node structure definition
			 */
			typedef struct dostree_node_t : public rbtree_node_t {
				int key;	// the key	
				int size;	// the size of this subtree
			} *dostree_node;

#define DOSNODE(rbnode) static_cast<dostree_node>(rbnode)
#define DOSNODE_SIZE(rbnode) (rbnode?DOSNODE(rbnode)->size:0)

		public:
			DosTree() { }
			~DosTree() {
				destruct(DOSNODE(get_root()));
			}
		private:
			DosTree(const DosTree&);
			DosTree& operator=(const DosTree&);

			void destruct(dostree_node n) {
				if (n==NULL) return;
				destruct(DOSNODE(n->left));
				destruct(DOSNODE(n->right));
				delete n;
			}

		public:
			dostree_node index(int index) {
				return lookup_node(get_root(),index);
			}

			/**
			 * dostree_insert
			 * insert a new key into the dos tree
			 */
			void insert(int key) {
				dostree_node inserted_node = new_node(key, RED, NULL, NULL);

				if (get_root() == NULL) {
					set_root(inserted_node);
				}
				else {
					rbtree_node n = DOSNODE(get_root());
					while (1) {
						// incr 1 for each node on the path traversed from the root
						DOSNODE(n)->size+=1;
						if (key < DOSNODE(n)->key) {
							if (n->left == NULL) {
								n->left = inserted_node;
								break;
							} else {
								n = n->left;
							}
						} else {
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

				// fix red-black properties
				insert_case1(inserted_node);
			}

			/**
			 * delete the key in the red-black tree
			 */
			void delete_key(dostree_node n) {
				rbtree_node child;

				/* Copy key/value from predecessor and then delete it instead */
				if (n->left != NULL && n->right != NULL) {
					dostree_node pred = DOSNODE(maximum_node(n->left));
					DOSNODE(n)->key = DOSNODE(pred)->key;
					DOSNODE(n)->size = DOSNODE(pred)->size;
					n = pred;
				}

				// fix up size from pred
				fixup_size(n);

				assert(n->left == NULL || n->right == NULL);
				child = n->right == NULL ? n->left  : n->right;
				if (node_color(n) == BLACK) {
					n->color = node_color(child);
					delete_case1(n);
				}
				replace_node(n, child);
	    		if (n->parent == NULL && child != NULL)	// root
        			child->color = BLACK;
				delete (DOSNODE(n));
			}

			void print() {
				print_helper(get_root(), 0);
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
					printf("[key:%d size:%d]\n", DOSNODE(n)->key,DOSNODE(n)->size);
				else
					printf("*[key:%d size:%d]\n", DOSNODE(n)->key, DOSNODE(n)->size);
				if (n->left != NULL) {
					print_helper(n->left, indent + INDENT_STEP);
				}
			}
		private:
			/**
			 * dostree_lookup
			 *
			 * select the i-th largest element
			 */
			dostree_node lookup_node(rbtree_node n, int i) {
				if (n == NULL) return NULL;	 // beware of NULL pointer
				int size = DOSNODE_SIZE(n->left) + 1;

				if(i == size) return DOSNODE(n);
				if(i < size ) return lookup_node(n->left, i);
				else return lookup_node(n->right, i-size);
			}

			/**
			 * left/right rotation call back function
			 */
			void rotate_left_callback(rbtree_node n, rbtree_node parent) {
				DOSNODE(parent)->size = DOSNODE_SIZE(n);
				DOSNODE(n)->size = DOSNODE_SIZE(n->left) + DOSNODE_SIZE(n->right) + 1;
			}

			void rotate_right_callback(rbtree_node n, rbtree_node parent) {
				rotate_left_callback(n,parent);
			}

			/**
			 * fix procedure caused by deletion
			 */
			void fixup_size(rbtree_node n) {	
				// fix up to the root
				do {
					DOSNODE(n)->size -= 1;
					n = n->parent;
				} while(n != NULL); 
			}

			static inline dostree_node new_node(int key, color rbtree_node_color, rbtree_node left, rbtree_node right) {
				dostree_node result =new dostree_node_t;
				result->key = key;
				result->size = 1;
				result->color = rbtree_node_color;
				result->left = NULL;
				result->right = NULL;
				if(left !=NULL) left->parent = result;
				if(right!=NULL) right->parent = result;
				result->parent = NULL;
				return result;
			}

	};
}

#endif
