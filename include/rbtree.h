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
#include <stdio.h>
#include <stdint.h>

namespace alg
{
	const int INDENT_STEP=4;

	template<typename KeyT, typename ValueT>
	class RBTree 
	{
	protected:
		enum rbtree_node_color { RED, BLACK };
		typedef enum rbtree_node_color color;
		typedef struct rbtree_node_t {
			KeyT key;
			ValueT value;
			rbtree_node_t* left;
			rbtree_node_t* right;
			rbtree_node_t* parent;
			enum rbtree_node_color color;
		} *rbtree_node;

		/**
		 * According to rotation operation, n1 is the node, n2 is parent node affected by rotation
		 */
		typedef void (*rotate_callback)(rbtree_node n1, rbtree_node n2);

		rbtree_node root;
		rotate_callback cb_left;
		rotate_callback cb_right;	

	public:
		/**
		 * init a red-black tree 
		 */
		RBTree() 
		{
			root = NULL;
			cb_left = NULL;
			cb_right = NULL;
		}

		virtual ~RBTree()
		{
			// TODO: delete the nodes
		}
		
		/**
		 * rbtree_insert
		 * insert a key-value pair into red-black tree
		 * you must specify your own compare function
		 */
		virtual void insert(const KeyT & key, const ValueT & value) 
		{
			rbtree_node inserted_node = new_node(key, value, RED, NULL, NULL);
			if (root == NULL) {
				root = inserted_node;
			} else {
				rbtree_node n = root;
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
							n = n->left;
						}
					} else {
						assert (key > n->key);
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
			insert_case1(inserted_node);
		}
	
		/**
		 * rbtree_lookup
		 * search in red-black tree
		 */
		virtual ValueT lookup(KeyT key) 
		{
			rbtree_node n = lookup_node(key);
			return n == NULL ? NULL : n->value;
		}

		/**
		 * delete the key in the red-black tree
		 */
		virtual void delete_key(KeyT key) 
		{
			rbtree_node child;
			rbtree_node n = lookup_node(key);
			if (n == NULL) return;  /* Key not found, do nothing */
			if (n->left != NULL && n->right != NULL) {
				/* Copy key/value from predecessor and then delete it instead */
				rbtree_node pred = maximum_node(n->left);
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
			if (n->parent == NULL && child != NULL)
				child->color = BLACK;
			delete(n);
		}

		virtual void print() {
			print_helper(root, 0);
			puts("");
		}
	protected:
		virtual void print_helper(rbtree_node n, int indent) {
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
				printf("%d\n", (int)n->key);
			else
				printf("<%d>\n", (int)n->key);
			if (n->left != NULL) {
				print_helper(n->left, indent + INDENT_STEP);
			}
		}

		rbtree_node grandparent(rbtree_node n) 
		{
			assert (n != NULL);
			assert (n->parent != NULL); /* Not the root rbtree_node */
			assert (n->parent->parent != NULL); /* Not child of root */
			return n->parent->parent;
		}

		rbtree_node sibling(rbtree_node n) 
		{
			assert (n != NULL);
			assert (n->parent != NULL); /* Root rbtree_node has no sibling */
			if (n == n->parent->left)
				return n->parent->right;
			else
				return n->parent->left;
		}

		rbtree_node uncle(rbtree_node n) 
		{
			assert (n != NULL);
			assert (n->parent != NULL); /* Root rbtree_node has no uncle */
			assert (n->parent->parent != NULL); /* Children of root have no uncle */
			return sibling(n->parent);
		}

		color node_color(rbtree_node n) 
		{
			return n == NULL ? BLACK : n->color;
		}

		
		rbtree_node new_node(KeyT key, ValueT value, color rbtree_node_color, rbtree_node left, rbtree_node right) {
			rbtree_node result =new rbtree_node_t;
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

		rbtree_node lookup_node(KeyT key) {
			rbtree_node n = root;
			while (n != NULL) {
				if (key == n->key) {
					return n;
				} else if (key < n->key) {
					n = n->left;
				} else {
					n = n->right;
				}
			}
			return n;
		}

		void rotate_left(rbtree_node n) 
		{
			rbtree_node r = n->right;
			replace_node(n, r);
			n->right = r->left;
			if (r->left != NULL) {
				r->left->parent = n;
			}
			r->left = n;
			n->parent = r;

			if (cb_left!=NULL) (*cb_left)(n, r);		// rotation call back 
		}

		void rotate_right(rbtree_node n) 
		{
			rbtree_node L = n->left;
			replace_node(n, L);
			n->left = L->right;
			if (L->right != NULL) {
				L->right->parent = n;
			}
			L->right = n;
			n->parent = L;

			if (cb_right!=NULL) (*cb_right)(n, L);		// rotation call back 
		}

		void replace_node(rbtree_node oldn, rbtree_node newn) 
		{
			if (oldn->parent == NULL) {
				root = newn;
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

		void insert_case1(rbtree_node n) 
		{
			if (n->parent == NULL)
				n->color = BLACK;
			else
				insert_case2(n);
		}

		void insert_case2(rbtree_node n) 
		{
			if (node_color(n->parent) == BLACK)
				return; /* Tree is still valid */
			else
				insert_case3(n);
		}

		void insert_case3(rbtree_node n) 
		{
			if (node_color(uncle(n)) == RED) {
				n->parent->color = BLACK;
				uncle(n)->color = BLACK;
				grandparent(n)->color = RED;
				insert_case1(grandparent(n));
			} else {
				insert_case4(n);
			}
		}

		void insert_case4(rbtree_node n) 
		{
			if (n == n->parent->right && n->parent == grandparent(n)->left) {
				rotate_left(n->parent);
				n = n->left;
			} else if (n == n->parent->left && n->parent == grandparent(n)->right) {
				rotate_right(n->parent);
				n = n->right;
			}
			insert_case5(n);
		}

		void insert_case5(rbtree_node n) 
		{
			n->parent->color = BLACK;
			grandparent(n)->color = RED;
			if (n == n->parent->left && n->parent == grandparent(n)->left) {
				rotate_right(grandparent(n));
			} else {
				assert (n == n->parent->right && n->parent == grandparent(n)->right);
				rotate_left(grandparent(n));
			}
		}

		rbtree_node maximum_node(rbtree_node n) 
		{
			assert (n != NULL);
			while (n->right != NULL) {
				n = n->right;
			}
			return n;
		}

		void delete_case1(rbtree_node n) 
		{
			if (n->parent == NULL)
				return;
			else
				delete_case2(n);
		}

		void delete_case2(rbtree_node n) 
		{
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

		void delete_case3(rbtree_node n) 
		{
			if (node_color(n->parent) == BLACK &&
				node_color(sibling(n)) == BLACK &&
				node_color(sibling(n)->left) == BLACK &&
				node_color(sibling(n)->right) == BLACK)
			{
				sibling(n)->color = RED;
				delete_case1(n->parent);
			}
			else
				delete_case4(n);
		}

		void delete_case4(rbtree_node n) 
		{
			if (node_color(n->parent) == RED &&
				node_color(sibling(n)) == BLACK &&
				node_color(sibling(n)->left) == BLACK &&
				node_color(sibling(n)->right) == BLACK)
			{
				sibling(n)->color = RED;
				n->parent->color = BLACK;
			}
			else
				delete_case5(n);
		}

		void delete_case5(rbtree_node n) 
		{
			if (n == n->parent->left &&
				node_color(sibling(n)) == BLACK &&
				node_color(sibling(n)->left) == RED &&
				node_color(sibling(n)->right) == BLACK)
			{
				sibling(n)->color = RED;
				sibling(n)->left->color = BLACK;
				rotate_right(sibling(n));
			}
			else if (n == n->parent->right &&
					 node_color(sibling(n)) == BLACK &&
					 node_color(sibling(n)->right) == RED &&
					 node_color(sibling(n)->left) == BLACK)
			{
				sibling(n)->color = RED;
				sibling(n)->right->color = BLACK;
				rotate_left(sibling(n));
			}
			delete_case6(n);
		}

		void delete_case6(rbtree_node n) 
		{
			sibling(n)->color = node_color(n->parent);
			n->parent->color = BLACK;
			if (n == n->parent->left) {
				assert (node_color(sibling(n)->right) == RED);
				sibling(n)->right->color = BLACK;
				rotate_left(n->parent);
			}
			else
			{
				assert (node_color(sibling(n)->left) == RED);
				sibling(n)->left->color = BLACK;
				rotate_right(n->parent);
			}
		}
	};
}

#endif
