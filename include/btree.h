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
#define T 255
namespace alg {
	class BTree {
	private:
		// 4K node, 4096 bytes to write
		// t = 255
		typedef struct __attribute__ ((packed)) node_t {
			int16_t leaf;		// is leaf?
			int16_t n;			// num key
			int32_t offset;		// block offset
			int32_t key[509];	// key
			int32_t c[510];		// childs pointers (file offsets related to 0)
			char padding[12];	// padding to 4096
			void *pc[510];		// memory
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
			node x = (node)allocate_node();
			x->leaf = true;
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
			while (i<=x->n && k > x->key[i]) i++;

			if (i <= x->n && k == x->key[i]) {
				ret.n = x, ret.i = i;
				return ret;
			} else if (x->leaf) {
				ret.n = NULL, ret.i = i;
				return ret;
			} else {
				READ(x, i);
				return Search((node)x->pc[i], k);
			}
		}

	private:
		// disk ops
		void * allocate_node() {
			node x = (node)malloc(sizeof(node_t));
			x->leaf = false;
			x->n = 0;
			x->offset = -1;
			memset(x->key, 0, sizeof(x->key));
			memset(x->c, 0, sizeof(x->c));
			memset(x->pc, 0, sizeof(x->pc));
			return x;
		}

		void split_child(node x, int32_t i) {
			node z = (node)allocate_node();
			node y = (node)x->pc[i];
			z->leaf = y->leaf;
			z->n = T - 1;

			int j;
			for (j=1;j<=T-1;j++) {	// init z
				z->key[j] = y->key[j+T];
			}

			if (y->leaf == false) {
				for (j=1;j<=T;j++) {
					z->c[j] = y->c[j+T];
					z->pc[j] = y->pc[j+T];	// copy mem ref also
				}
			}

			y->n = T-1;	// splited y
			WRITE(y);
			WRITE(z);

			for (j=x->n+1;j>=i+1;j--) {
				x->c[j+1] = x->c[j];	// shift
				x->pc[j+1] = x->pc[j];
			}

			// relocate z
			x->c[i+1] = z->offset;
			x->pc[i+1] = z;

			for (j=x->n;j>=i;j--) {
				x->key[j+1] = x->key[j];
			}
			x->key[i] = y->key[T];
			x->n = x->n +1;
			WRITE(x);
		}
		
		void READ(node x, int32_t i) {
			if (x->pc[i] != NULL) {
				return;
			}

			x->pc[i] = allocate_node();
			lseek(fd, x->c[i], SEEK_SET);
			read(fd, x->pc[i], BLOCKSIZE);
		}

		void WRITE(node x) {
			if (x->offset !=-1) {
				lseek(fd, x->offset, SEEK_SET);
			} else {
				x->offset = lseek(fd,0, SEEK_END);
			}
			write(fd, x, BLOCKSIZE);
		}
	};
}
#endif //
