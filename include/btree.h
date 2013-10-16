/*******************************************************************************
 * ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * B-TREE
 *
 * In computer science, a B-tree is a tree data structure that keeps data sorted 
 * and allows searches, sequential access, insertions, and deletions in 
 * logarithmic time. The B-tree is a generalization of a binary search tree in 
 * that a node can have more than two children. (Comer 1979, p. 123) Unlike 
 * self-balancing binary search trees, the B-tree is optimized for systems that 
 * read and write large blocks of data. It is commonly used in databases and 
 * filesystems.
 *
 * http://en.wikipedia.org/wiki/B-tree
 ******************************************************************************/

#ifndef __BTREE_H__
#define __BTREE_H__
#include <stdint.h>
#include <string.h>
namespace alg {
	class BTree {
	private:
		// 4K node, 4080 bytes
		// t = 255
		typedef struct node_t {
			int16_t leaf;		// is leaf?
			int16_t n;			// num keys
			int32_t keys[509];	// keys
			int32_t c[510];		// childs pointers (file offsets)
			node_t* pc[510];	// childs pointers (memory pointers)
		} *node;

		struct search_r {
			node n;
			int32_t i;
		};
	private:
		node m_root;
	private:
		BTree(const BTree &);
		BTree& operator=(const BTree&);
	public:
		BTree() {
			node x = allocate_node();
			x->leaf = true;
			x->n = 0;
			memset(x->keys, 0, sizeof(x->keys));
			memset(x->c, 0, sizeof(x->c));
		}

		/**
		 * search a key, returns node and index
		 */
		search_r Search(node x, int32_t k) {
			int i = 1;
			search_r ret;
			while (i<=x->n && k > x->keys[i]) i++;

			if (i <= x->n && k == x->keys[i]) {
				ret.n = x, ret.i = i;
				return ret;
			} else if (x->leaf) {
				ret.n = NULL, ret.i = i;
				return ret;
			} else {
				disk_read(x, i);
				return Search(x->pc[i], k);
			}
		}

	private:
		// disk ops
		node allocate_node() {
			node x = new node_t;
			return x;
		}
		
		void disk_read(node x, int32_t i) {
		}
	};
}
#endif //
