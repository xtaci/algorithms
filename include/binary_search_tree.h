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
			treeNode *left;	// left child
			treeNode *right;	// right child
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
		BSTException error;
	
	public:
		BST():m_root(NULL){};

		~BST()
		{
			destruct(m_root);
		}

		ValueT operator[] (const KeyT & key)
		{
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
		bool contains(const KeyT & key)
		{
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
		bool insert(const KeyT & key, const ValueT & value)
		{
			treeNode *n = new treeNode;
			n->key = key;
			n->value = value;
			n->left = n->right = NULL;

			if (m_root == NULL){
				m_root = n;
				return true;
			}
			treeNode * tmp = m_root;
				
			while(true) {
				if (key == tmp->key) {	// already inserted
					delete n;
					return false;
				}
				else if(key < tmp->key) {
					if (tmp->left == NULL) {
						tmp->left = n;
						return true;
					} else tmp = tmp->left;
				} else {
					if (tmp->right == NULL) {
						tmp->right = n;
						return true;
					} else tmp = tmp->right;
				}
			}
		}
	private:
		void destruct(treeNode *n)
		{
			if (n==NULL) return;
			destruct(n->left);
			destruct(n->right);
			delete n;
		}

	private:
		BST(const BST&);
		BST& operator=(const BST&);
	};
}

#endif //
