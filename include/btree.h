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
#include <memory>

#define BLOCKSIZE	4096
#define T 			255
#define LEAF 		0x0001
#define ONDISK		0x0002
#define MARKFREE	0x0004

namespace alg {
	class BTree {
		private:
			// 4K node, 4096 bytes to write
			// t = 255
			struct node_t {
				uint16_t n;				// num key
				uint16_t flag;			// flags
				uint32_t offset;		// block offset (8 byte head)
				char padding[12];		// padding to 4096
				int32_t key[509];		// key
				int32_t c[510];			// childs pointers (file offsets related to 0)
			} __attribute__ ((packed));
			typedef struct node_t *node;

		public:	
			// node and index
			struct nr {
				uint32_t offset;
				int32_t idx;
			};
		private:
			node m_root;
			int fd;
		private:
			BTree(const BTree &);
			BTree& operator=(const BTree&);
		public:
			BTree(const char * path) {
				fd = open(path, O_RDWR|O_CREAT, 0640);
				if (fd == -1)
					return;
				node x = (node)allocate_node();
				int n = read(fd,x,BLOCKSIZE);
				if (n != BLOCKSIZE) {	// init new btree
					x->flag |= LEAF;
					WRITE(x);
				}
				m_root = (node)x;
			}

			~BTree() {
				close(fd);
			}

			nr Search(int32_t x) {
				return search(m_root, x);
			}

			void Insert(int32_t k) {
				node r = m_root;
				if (r->n == 2*T - 1) {
					// place the old root node to the end of the file
					m_root->flag &= ~ONDISK;
					WRITE(m_root);
					// new root
					node s = (node)allocate_node();
					s->flag &= ~LEAF;
					s->flag |= ONDISK;	// write to offset 0
					s->offset = 0;
					s->n = 0;
					s->c[0] = m_root->offset;
					// free old & set new
					free(m_root);
					m_root = s;
					split_child(s, 0);
					insert_nonfull(s, k);
				} else {
					insert_nonfull(r, k);
				}
			}

			void DeleteKey(int32_t k) {
				node x =  m_root;
				delete_op(m_root, k);
			}

		private:
			/**
			 * search a key, returns node and index
			 */
			nr search(node x, int32_t k) {
				int32_t i = 0;
				nr ret;
				while (i<x->n && k > x->key[i]) i++;

				if (i<x->n && k == x->key[i]) {	// search in [0,n-1]
					ret.offset = x->offset;
					ret.idx = i;
					return ret;
				} else if (x->flag & LEAF) {	// leaf, no more childs
					ret.offset = 0;
					ret.idx = -1;
					return ret;
				} else {
					std::auto_ptr<node_t> xi(READ(x, i));	// in last child
					return search(xi.get(), k);
				}
			}

			/**
			 * insert into non-full node
			 */
			void insert_nonfull(node x, int32_t k) {
				int32_t i = x->n-1;
				if (x->flag & LEAF) {	// insert into leaf
					while (i>=0 && k < x->key[i]) {	// shift from right to left, when k < key[i]
						x->key[i+1] = x->key[i];
						i = i - 1;
					}
					x->key[i+1] = k;
					x->n = x->n + 1;
					WRITE(x);
				} else {
					while(i>=0 && k < x->key[i]) {
						i = i-1;
					}
					i=i+1;
					node xi = READ(x, i);
					if (xi->n == 2*T-1) {
						split_child(x, i);
						if (k > x->key[i]) {
							i = i+1;
						}
						// reload x[i] after split_child(will modify child x[i])
						xi = READ(x, i);
					}
					insert_nonfull(xi, k);
					free(xi);
				}
			}

			/**
			 * allocate empty node struct
			 */
			void * allocate_node() {
				node x = (node)malloc(sizeof(node_t));
				x->n = 0;
				x->offset = 0;
				x->flag = 0;
				memset(x->key, 0, sizeof(x->key));
				memset(x->c, 0, sizeof(x->c));
				return x;
			}

			/**
			 * split a node into 2.
			 */
			void split_child(node x, int32_t i) {
				std::auto_ptr<node_t> z((node)allocate_node());
				std::auto_ptr<node_t> y(READ(x, i));
				z->flag &= ~LEAF;
				z->flag |= (y->flag & LEAF);
				z->n = T - 1;

				int32_t j;
				for (j=0;j<T-1;j++) {	// init z, t-1 keys
					z->key[j] = y->key[j+T];
				}

				if (!(y->flag & LEAF)) {	// if not leaf, copy childs too.
					for (j=0;j<T;j++) {
						z->c[j] = y->c[j+T];
					}
				}

				y->n = T-1;	// shrink y to t-1 elements
				WRITE(y.get());
				WRITE(z.get());

				for (j=x->n;j>=i+1;j--) { // make place for the new child in x
					x->c[j+1] = x->c[j];
				}

				x->c[i+1] = z->offset; // make z the child of x
				for (j=x->n-1;j>=i;j--) { // move keys in x
					x->key[j+1] = x->key[j];
				}
				x->key[i] = y->key[T-1];	// copy the middle element of y into x
				x->n = x->n+1;
				WRITE(x);
			}

			/**
			 * recursive deletion.
			 */
			void delete_op(node x, int32_t k) {
				int32_t i;
				if (x->n == 0) {	// emtpy node
					return;
				}
			
				i = x->n - 1;
				while (i>=0 && k < x->key[i]) { // search the key.
					i = i - 1;
				}

				if (x->key[i] == k) {	// key in this node.
					if (x->flag & LEAF) {	// if it's a leaf node. case 1.
						int j;
						for (j = i;j<x->n-1;j++) {	// shift copy
							x->key[j] = x->key[j+1];
						}
						WRITE(x);
						return;
					} else { // in non-leaf node
						node y, z;
						if (i-1 >= 0) {	// case 2a
							y = READ(x, i-1);
							std::auto_ptr<node_t> _y(y);
							if (y->n >= T) {		
								x->key[i] = y->key[y->n-1];
								WRITE(x);
								delete_op(y, x->key[i]);
								return;
							}
						}

						if (i+1 < x->n) { // case 2b
							z = READ(x, i+1);
							std::auto_ptr<node_t> _z(z);
							if (z->n >= T) {
								x->key[i] = z->key[0];
								WRITE(x);
								delete_op(z, x->key[i]);
								return;
							}
						}

						if (y->n == T-1 && z->n == T-1) { // case 2c
							// merge k & z into y
							y->key[y->n] = k;

							int j;
							for (j=0;j<z->n;j++) {	// merge n keys, k already in 
								y->key[y->n+j+1] = z->key[j];
							}
							for (j=0;j<z->n+1;j++) {	// merge n+1 childs
								y->c[y->n+j+1] = z->key[j];
							}
							// mark free this node
							z->flag |= MARKFREE;
							y->n = y->n + z->n + 1; // size after merge
							WRITE(z);
							WRITE(y);

							// shift x
							for (j=i;j<x->n-1;j++) {
								x->key[i] = x->key[i+1];
							}
							x->n = x->n - 1;
							WRITE(x);

							// recursive delete k
							delete_op(y, k);
							return;
						}

					}
				} else {	// case 3
					i = i+1;	// child to search
					std::auto_ptr<node_t> ci(READ(x, i));
				
					if (ci->n == T-1) { // case 3a.
						if (i-1>=0) {
							std::auto_ptr<node_t> left(READ(x, i-1)); // left sibling
							if (left->n > T) {
								int j;
								for (j=ci->n-2;j>=0;j++) { // right shift ci keys
									ci->key[j+1] = ci->key[j];
								}

								for (j=ci->n-1;j>=0;j++) { // right shift ci childs
									ci->c[j+1] = ci->c[j];
								}
								ci->n = ci->n+1;
								ci->key[0] = x->key[i];	// copy key from x[i] to ci[0]
								ci->c[0] = left->c[left->n];	// copy child pointer from left last child
								x->key[i] = left->key[left->n-1];	// copy from left last key
								left->n = left->n-1;	// decrease left num keys

								WRITE(ci.get());
								WRITE(x);
								WRITE(left.get());
								delete_op(ci.get(), k); 
							}
						}
						
						if (i+1<ci->n) {
							std::auto_ptr<node_t> right(READ(x, i+1)); // right sibling
							if (right->n > T) {
								ci->key[ci->n-1] = x->key[i];
								ci->c[ci->n] = right->c[0];
								ci->n = ci->n+1;
								x->key[i] = right->key[0];

								int j;
								for (j=0;j<right->n-1;j++) { // left shift sibling keys
									right->key[j] = right->key[j+1];
								}

								for (j=0;j<right->n;j++) { // left shift ci childs
									right->c[j] = right->c[j+1];
								}

								WRITE(ci.get());
								WRITE(x);
								WRITE(right.get());
								delete_op(ci.get(), k); 
							}
						}
					}
				}

				return;
			}


			/**
			 * Read a 4K-block from disk, and returns the node struct.
			 */
			node READ(node x, int32_t i) {
				void *xi = allocate_node();
				lseek(fd, x->c[i], SEEK_SET);
				read(fd, xi, BLOCKSIZE);
				return (node)xi;
			}

			/**
			 * 	update a node struct to file, create if offset is -1.
			 */
			void WRITE(node x) {
				if (x->flag & ONDISK) {
					lseek(fd, x->offset, SEEK_SET);
				} else {
					x->offset = lseek(fd,0, SEEK_END);
				}
				x->flag |= ONDISK;
				write(fd, x, BLOCKSIZE);
			}
	};
}
#endif //
