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
namespace alg {
	class BTree {
	private:
		// 4K node, 4080 bytes
		typedef struct node_t {
			int16_t leaf;		// is leaf?
			int16_t n;			// num keys
			int32_t keys[509];	// keys
			int32_t c[510];		// childs pointers(file offsets)
		} *node;
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
		}

	private:
		node allocate_node() {
			node x = new node_t;
			return x;
		}
	};
}
#endif //
