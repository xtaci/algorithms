/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
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

namespace alg
{
	template<typename KeyT, typename ValueT>
	class BST
	{
	private:
		/**
		 * binary search tree definiton.
		 */
		struct treeNode
		{
			KeyT 	key;			// key
			ValueT 	value;			// data
			treeNode *parent;		// parent
			treeNode *left;			// left child
			treeNode *right;		// right child
		};

		class BSTException: public std::exception
		{
			public:
			virtual const char * what() const throw()
			{
				return "key does not exist";
			}
		};
	
	private:
		treeNode * m_root;
		const BSTException error;
	
	public:
		BST():m_root(NULL){};

		~BST() {
			destruct(m_root);
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
		bool insert(const KeyT & key, const ValueT & value) {
			treeNode *newnode = new treeNode;
			newnode->key = key;
			newnode->value = value;
			newnode->left = newnode->right = newnode->parent = NULL;

			if (m_root == NULL){
				m_root = newnode;
				return true;
			}

			treeNode * n = m_root;
			while(true) {
				if (key == n->key) {	// already inserted
					delete newnode;
					return false;
				}
				else if(key < n->key) {
					if (n->left == NULL) {
						newnode->parent = n;
						n->left = newnode;
						return true;
					} else n = n->left;
				} else {
					if (n->right == NULL) {
						newnode->parent = n;
						n->right = newnode;
						return true;
					} else n = n->right;
				}
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
				}
				else if(key < n->key) {
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
				treeNode *y = minimum(z->right);
				if (y->parent != z) {
					transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}

				transplant(z,y);
				y->left = z->left;
				y->left->parent = y;
			}
		}

	private:
		void destruct(treeNode *n) {
			if (n==NULL) return;
			destruct(n->left);
			destruct(n->right);
			delete n;
		}

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

		treeNode * minimum(treeNode *x) {
			while (x->left != NULL) {
				x = x->left;
			}

			return x;
		}

	private:
		BST(const BST&);
		BST& operator=(const BST&);
	};
}

#endif //
