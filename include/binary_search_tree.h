/*******************************************************************************
 * ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * BINARY SEARCH TREE
 *
 * Features:
 * 1. Expected search time is O(nlogn).
 * 2. Data should be !!!SHUFFLED!!! first before tree creation.
 * 3. First initialize the value of the root (pointer to the 
 *    structure treeNode) with NULL. eg:
 *    treeNode *root = NULL
 *
 * http://en.wikipedia.org/wiki/Binary_search_tree
 *
 ******************************************************************************/

#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

#include <stdlib.h>
#include <stdint.h>
#include <exception>

namespace alg {
	template<typename KeyT, typename ValueT>
	class BST {
	private:
		/**
		 * binary search tree definiton.
		 */
		struct treeNode {
			KeyT 	key;			// key
			ValueT 	value;			// data
			treeNode *parent;		// parent
			treeNode *left;			// left child
			treeNode *right;		// right child
		};

		class BSTException: public std::exception {
			public:
			virtual const char * what() const throw() {
				return "key does not exist";
			}
		};
	
	private:
		treeNode * m_root;		// the root
		const BSTException error;
	private:
		BST(const BST&);
		BST& operator=(const BST&);
	public:
		BST():m_root(NULL){};

		~BST() {
			__destruct(m_root);
		}

		ValueT operator[] (const KeyT & key) {
			if (m_root == NULL) throw error;
			treeNode * tmp = m_root;
	
			while(true) {
				if (key == tmp->key) return tmp->value;
				else if(key < tmp->key) {
					if (tmp->left == NULL) throw error;
					tmp = tmp->left;
				} else {
					if (tmp->right == NULL) throw error;
					tmp = tmp->right;
				}
			}
		}

		/**
		 * test whether the key is in the tree
		 */
		bool contains(const KeyT & key) {
			if (m_root == NULL) return false;
			treeNode * tmp = m_root;
	
			while(true) {
				if (key == tmp->key) return true;
				else if(key < tmp->key) {
					if (tmp->left == NULL) return false;
					tmp = tmp->left;
				} else {
					if (tmp->right == NULL) return false;
					tmp = tmp->right;
				}
			}
		}

		/**
		 * insert a new data into the binary search tree.
		 */
		void insert(const KeyT & key, const ValueT & value) {
			treeNode *z= new treeNode;
			z->key = key;
			z->value = value;
			z->left = z->right = z->parent = NULL;

			treeNode * n = m_root;
			treeNode * y = NULL;
			while(n!=NULL) {
				y = n;	
				if(key < n->key) {
					n = n->left;			
				} else {
					n = n->right;
				}
			}

			z->parent = y;
			if (y==NULL) {
				m_root = z;
			} else if (key < y->key) {
				y->left = z;
			} else {
				y->right = z;
			}
		}

		/**
		 * delete a key from the binary search tree.
		 */
		bool deleteKey(const KeyT & key) {
			treeNode * n = m_root;
			treeNode * z = NULL;

			while(n!=NULL) {
				if (key == n->key) {	// found!
					z = n;
					break;
				} else if(key < n->key) {
					n = n->left;
				} else {
					n = n->right;
				}
			}

			// delete the node
			if (z==NULL) {
				return false;
			}
		
			if (z->left == NULL) {
				transplant(z, z->right);
			} else if (z->right == NULL) {
				transplant(z, z->left);
			} else {
				// find the minimum element of the right subtree
				treeNode *y = minimum(z->right);	
				if (y->parent != z) {
					// replace y with right-child
					transplant(y, y->right);
					// replace right-child of y with the right-child of z
					y->right = z->right;
					// make y the parent of the right-child
					y->right->parent = y;
				}
			
				// replace z with y
				transplant(z,y);
				y->left = z->left;
				y->left->parent = y;
			}

			delete z;
			return true;
		}

	private:
		void __destruct(treeNode *n) {
			if (n==NULL) return;
			__destruct(n->left);
			__destruct(n->right);
			delete n;
		}

		/**
		 * replace node u with v.
		 */
		void transplant(treeNode *u, treeNode *v) {
			if (u->parent == NULL) {
				m_root = u;
			} else if (u == u->parent->left) {
				u->parent->left = v;
			} else {
				u->parent->right = v;
			}

			if (v!=NULL) {
				v->parent = u->parent;
			}
		}

		/**
		 * find the minimum element of the subtree
		 */
		treeNode * minimum(treeNode *x) {
			while (x->left != NULL) {
				x = x->left;
			}

			return x;
		}
	};
}

#endif //
