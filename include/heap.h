/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * Heap Data structure
 *
 * In computer science, a heap is a specialized tree-based data structure that 
 * satisfies the heap property: If A is a parent node of B then the key of node
 * A is ordered with respect to the key of node B with the same ordering applying 
 * across the heap. Heaps can be classified further as either a "max heap" or 
 * a "min heap". In a max heap, the keys of parent nodes are always greater
 * than or equal to those of the children and the highest key is in the root node.
 * In a min heap, the keys of parent nodes are less than or equal to those of 
 * the children and the lowest key is in the root node. Heaps are crucial in 
 * several efficient graph algorithms such as Dijkstra's algorithm, and in 
 * the sorting algorithm heapsort. A common implementation of a heap is the 
 * binary heap, in which the tree is a complete binary tree (see figure).
 *
 * Basic operations of a heap are:
 *
 * 1. Push – Insert an key.
 * 2. Pop – Delete and return the smallest item in the heap.
 * 3. Remove - Remove an element
 *
 * http://en.wikipedia.org/wiki/Binary_heap
 ******************************************************************************/

#ifndef ALGO_HEAP_H__
#define ALGO_HEAP_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include "generic.h"

namespace alg { 
	/**
	 * define binary heap structure.
	 */
	template<typename T>
		class Heap {
			public:
				/**
				 * define key-value pair of heap struct.
				 */
				struct elem {
					public:
						int key;
						T data;
				};

			private:
				int m_size;		// current heap size.
				int m_max;		// max heap size.
				elem * m_heap;	// key value pairs.
			public:
				Heap(int max) {
					m_size = 0;
					m_max = max;
					m_heap = new elem[m_max];
				};

				~Heap() {
					delete [] m_heap;
				};

			private:
				Heap(const Heap &);
				Heap& operator=(const Heap&);

			public:
				// for loop through the kvs
				inline int count() const { return m_size; };

				/**
				 * insert a 'key'->'value' pair into the heap.
				 */
				void push(int key, const T & data) {
					// heap full, just return;
					if(m_size == m_max) return; 
					// put in the back, and try move upward the heap
					m_heap[m_size].key = key;
					m_heap[m_size].data= data;
					up(m_size);
					m_size++;
				}

				/**
				 * emptiness test
				 */
				inline bool is_empty() const { return (m_size==0)?true:false; }

				/**
				 * clear the heap
				 */
				inline void clear() { m_size = 0; }

				bool contains(const T & data) {
					for(int i=0;i<m_size;i++) {
						if(m_heap[i].data== data) return true;
					}
					return false;
				}

				/**
				 * pop the min element
				 */
				elem pop() {
					int n = m_size-1;
					swap(m_heap[0],m_heap[n]);
					down(0, n);
					m_size--;
					return m_heap[m_size];
				}

				/**
				 *  remove the given data
				 */
				bool remove(const T &data) {
					for (int i=0;i<m_size;i++) { // loop finding 
						if (m_heap[i].data == data) { // found
							int n = m_size-1;
							if (n != i) {
								swap(m_heap[i], m_heap[n]);
								down(i, m_size); 
								up(i);
							}
							m_size--;
							return true;
						}
					}
					return false;
				}

				/**
				 *  decrease key
				 *  simpliy implemented as remove then push
				 */
				void decrease_key(const T &data, int newkey) {
					if (remove(data)) {
						push(newkey, data);
					}
				}

				void up(int j) {
					for (;;) {
						int i = (j-1)/2; // parent
						if (i==j || !less(j,i))  {	// j not smaller than i
							break;
						}
						swap(m_heap[i], m_heap[j]);
						j=i;
					}
				}

				void down(int i, int n) {
					for(;;) {
						int j1 = 2*i+1;	// left child
						if (j1 >=n || j1 < 0) { // j1 < 0 after int overflow
							break;
						}

						int j = j1;
						int j2 = j1+1; // right child
						if (j2 < n && !less(j1,j2)) {
							j = j2; 	// choose the minium one.
						}

						if (!less(j,i)) {
							break;
						}
						swap(m_heap[i], m_heap[j]);
						i=j;
					}
				}

				void print_heap() {
					for (int i=0;i<m_size;i++) {
						printf("key:%d value:%d ", m_heap[i].key, m_heap[i].data);
					}
					printf("\n");
				}

				bool less(int i, int j) {
					return m_heap[i].key < m_heap[j].key;
				}
		};
}

#endif //
