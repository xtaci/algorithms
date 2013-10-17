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
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define BLOCKSIZE	4096
namespace alg {
	class BTree {
	private:
		// 4K node, 4096 bytes to write
		// t = 255
		typedef struct __attribute__ ((packed)) node_t {
			int16_t leaf;		// is leaf?
			int16_t n;			// num keys
			int32_t keys[509];	// keys
			int32_t c[510];		// childs pointers (file offsets related to 0)
			char padding[16];	// padding to 4096
			void *pc[510];	// memory
		} *node;

		struct search_r {
			node n;
			int32_t i;
		};
	private:
		node m_root;
		void * map;
		int fd;
	private:
		BTree(const BTree &);
		BTree& operator=(const BTree&);
	public:
		BTree(const char * path) {
			fd = open(path, O_RDWR);
			if (fd == -1)
				return;
			node x = allocate_node();
			x->leaf = true;
			x->n = 0;
			memset(x->keys, 0, sizeof(x->keys));
			memset(x->c, 0, sizeof(x->c));
			memset(x->pc, 0, sizeof(x->pc));
		}

		~BTree() {
			close(fd);
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
				return Search((node)x->pc[i], k);
			}
		}

	private:
		// disk ops
		node allocate_node() {
			node x = new node_t;
			return x;
		}
		
		void disk_read(node x, int32_t i) {
			if (x->pc[i] != NULL) {
				return;
			}

			x->pc[i] = malloc(sizeof(node_t));
			lseek(fd, x->c[i], SEEK_SET);
			read(fd, x->pc[i], BLOCKSIZE);
		}
	};
}
#endif //
