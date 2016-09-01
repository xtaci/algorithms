/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * RED-BLACK TREE DEFINITON
 *
 * Features:
 * 1. balanced tree
 * 2. O(logn) lookup performance
 *
 * http://en.wikipedia.org/wiki/Red_black_tree
 * http://en.literateprograms.org/Red-black_tree_(C)
 ******************************************************************************/

#ifndef ALGO_RBTREE_DEFS_H__
#define ALGO_RBTREE_DEFS_H__
#include <stdio.h>
#include <stdint.h>

namespace alg {
	class RBTreeAbstract {
		protected:
			static const int INDENT_STEP=4;

			enum rbtree_node_color { RED, BLACK };
			typedef enum rbtree_node_color color;

			typedef struct rbtree_node_t {
				rbtree_node_t* left;
				rbtree_node_t* right;
				rbtree_node_t* parent;
				enum rbtree_node_color color;
			} *rbtree_node;

		private:
			rbtree_node m_root;

		public:
			/**
			 * init a red-black tree 
			 */
			RBTreeAbstract() : m_root(NULL) {}
			virtual ~RBTreeAbstract() {}

		private:
			RBTreeAbstract(const RBTreeAbstract &);
			RBTreeAbstract& operator=(const RBTreeAbstract &);
		protected:
			// 
			inline rbtree_node get_root( ) { return m_root; }
			inline void set_root(rbtree_node new_root) { m_root = new_root; }

		protected:
			///
			/// THE RED-BLACK TREE CORE
			///
			rbtree_node grandparent(rbtree_node n) {
				assert (n != NULL);
				assert (n->parent != NULL); /* Not the root rbtree_node */
				assert (n->parent->parent != NULL); /* Not child of root */
				return n->parent->parent;
			}

			rbtree_node sibling(rbtree_node n) {
				assert (n != NULL);
				assert (n->parent != NULL); /* Root rbtree_node has no sibling */
				if (n == n->parent->left)
					return n->parent->right;
				else
					return n->parent->left;
			}

			rbtree_node uncle(rbtree_node n) {
				assert (n != NULL);
				assert (n->parent != NULL); /* Root rbtree_node has no uncle */
				assert (n->parent->parent != NULL); /* Children of root have no uncle */
				return sibling(n->parent);
			}

			color node_color(rbtree_node n) {
				return n == NULL ? BLACK : n->color;
			}

			/**
			 * According to rotation operation, n1 is the node, n2 is parent node affected by rotation
			 */
			virtual void rotate_left_callback(rbtree_node n1, rbtree_node n2) { }

			virtual void rotate_right_callback(rbtree_node n1, rbtree_node n2) { }


			void rotate_left(rbtree_node n) {
				rbtree_node r = n->right;
				replace_node(n, r);
				n->right = r->left;
				if (r->left != NULL) {
					r->left->parent = n;
				}
				r->left = n;
				n->parent = r;

				rotate_left_callback(n, r);
			}

			void rotate_right(rbtree_node n) {
				rbtree_node L = n->left;
				replace_node(n, L);
				n->left = L->right;
				if (L->right != NULL) {
					L->right->parent = n;
				}
				L->right = n;
				n->parent = L;

				rotate_right_callback(n, L);
			}

			void replace_node(rbtree_node oldn, rbtree_node newn) {
				if (oldn->parent == NULL) {
					m_root = newn;
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

			void insert_case1(rbtree_node n) {
				if (n->parent == NULL)
					n->color = BLACK;
				else
					insert_case2(n);
			}

			void insert_case2(rbtree_node n) {
				if (node_color(n->parent) == BLACK)
					return; /* Tree is still valid */
				else
					insert_case3(n);
			}

			void insert_case3(rbtree_node n) {
				if (node_color(uncle(n)) == RED) {
					n->parent->color = BLACK;
					uncle(n)->color = BLACK;
					grandparent(n)->color = RED;
					insert_case1(grandparent(n));
				} else {
					insert_case4(n);
				}
			}

			void insert_case4(rbtree_node n) {
				if (n == n->parent->right && n->parent == grandparent(n)->left) {
					rotate_left(n->parent);
					n = n->left;
				} else if (n == n->parent->left && n->parent == grandparent(n)->right) {
					rotate_right(n->parent);
					n = n->right;
				}
				insert_case5(n);
			}

			void insert_case5(rbtree_node n) {
				n->parent->color = BLACK;
				grandparent(n)->color = RED;
				if (n == n->parent->left && n->parent == grandparent(n)->left) {
					rotate_right(grandparent(n));
				} else {
					assert (n == n->parent->right && n->parent == grandparent(n)->right);
					rotate_left(grandparent(n));
				}
			}

			rbtree_node maximum_node(rbtree_node n) {
				assert (n != NULL);
				while (n->right != NULL) {
					n = n->right;
				}
				return n;
			}

			void delete_case1(rbtree_node n) {
				if (n->parent == NULL)
					return;
				else
					delete_case2(n);
			}

			void delete_case2(rbtree_node n) {
				if (node_color(sibling(n)) == RED) {
					n->parent->color = RED;
					sibling(n)->color = BLACK;
					if (n == n->parent->left)
						rotate_left(n->parent);
					else
						rotate_right(n->parent);
				}
				delete_case3(n);
			}

			void delete_case3(rbtree_node n) {
				if (node_color(n->parent) == BLACK &&
						node_color(sibling(n)) == BLACK &&
						node_color(sibling(n)->left) == BLACK &&
						node_color(sibling(n)->right) == BLACK) {
					sibling(n)->color = RED;
					delete_case1(n->parent);
				} else delete_case4(n);
			}

			void delete_case4(rbtree_node n) {
				if (node_color(n->parent) == RED &&
						node_color(sibling(n)) == BLACK &&
						node_color(sibling(n)->left) == BLACK &&
						node_color(sibling(n)->right) == BLACK) {
					sibling(n)->color = RED;
					n->parent->color = BLACK;
				} else delete_case5(n);
			}

			void delete_case5(rbtree_node n) {
				if (n == n->parent->left &&
						node_color(sibling(n)) == BLACK &&
						node_color(sibling(n)->left) == RED &&
						node_color(sibling(n)->right) == BLACK) {
					sibling(n)->color = RED;
					sibling(n)->left->color = BLACK;
					rotate_right(sibling(n));
				} else if (n == n->parent->right &&
						node_color(sibling(n)) == BLACK &&
						node_color(sibling(n)->right) == RED &&
						node_color(sibling(n)->left) == BLACK) {
					sibling(n)->color = RED;
					sibling(n)->right->color = BLACK;
					rotate_left(sibling(n));
				} 
				delete_case6(n);
			}

			void delete_case6(rbtree_node n) {
				sibling(n)->color = node_color(n->parent);
				n->parent->color = BLACK;
				if (n == n->parent->left) {
					assert (node_color(sibling(n)->right) == RED);
					sibling(n)->right->color = BLACK;
					rotate_left(n->parent);
				} else {
					assert (node_color(sibling(n)->left) == RED);
					sibling(n)->left->color = BLACK;
					rotate_right(n->parent);
				}
			}
	};
}

#endif
