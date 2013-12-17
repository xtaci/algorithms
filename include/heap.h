/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * Heap Data structure
 *
 * Heaps can be used as an array. For any key at array position I,
 I left child is at ( 2i ), right child is at ( 2i+1 ) and parent is 
 I at (int) (i / 2). Heap size is stored at index 0.
 *
 * Basic operations of a heap are:
 *
 * 1. Insert – Insert an key.
 * 2. Delete minimum – Delete and return the smallest item in the heap.
 *
 * http://en.wikipedia.org/wiki/Binary_heap
 ******************************************************************************/

#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include "hash_code.h"
#include "hash_table.h"

namespace alg { 
	/**
	 * define binary heap structure.
	 */
	template<typename T>
		class Heap {
			private:
				/**
				 * define key-value pair of heap struct.
				 */
				struct KV {
					public:
						int32_t key;
						T value;
				};
				int32_t m_size;		// current heap size.
				int32_t m_max;		// max heap size.
				KV * m_kvs;			// key value pairs.

				HashTable<T, int32_t>  * m_idx; // key -> idx

			public:
				Heap(int max) {
					m_size = 0;
					m_max = max+1;
					m_kvs = new KV[m_max];
					m_kvs[0].key = INT_MIN;
					m_idx = new HashTable<T, int32_t>(m_max);
				};

				~Heap() {
					delete [] m_kvs;
					delete m_idx;
				};

			private:
				Heap(const Heap &);
				Heap& operator=(const Heap&);

			public:

				inline int min_key() const { return m_kvs[1].key; };
				inline const T & min_value() const { return m_kvs[1].value; };

				// for loop through the kvs
				inline uint32_t count() const { return m_size; };
				inline const T & operator[] (uint32_t idx) const { return m_kvs[idx+1].value; };

				/**
				 * insert a 'key'->'value' pair into the heap.
				 */
				void insert(int key, const T & value) {
					// heap full, just return;
					if(m_size == m_max) return; 

					m_size++;
					m_kvs[m_size].key	= key;
					m_kvs[m_size].value	= value;
					(*m_idx)[value] = m_size;

					// Adjust its position
					int now = m_size;
					while(m_kvs[now/2].key > key) {
						m_kvs[now] = m_kvs[now/2];
						(*m_idx)[m_kvs[now/2].value] = now;
						now /= 2;
					}

					m_kvs[now].key		= key;
					m_kvs[now].value	= value;
					(*m_idx)[value] 	= now;
				}

				/**
				 * emptiness test
				 */
				inline bool is_empty() const { return (m_size==0)?true:false; }

				/**
				 * clear the heap
				 */
				inline void clear() { m_size = 0; }

				/**
				 * contains test
				 */
				bool contains(const T & value) {
					for(int32_t i=1;i<=m_size;i++) {
						if(m_kvs[i].value == value) return true;
					}

					return false;
				}

				/**
				 * delete the min element --> heap top.
				 */
				void delete_min() {
					// heap[1] is the minimum key. So we remove heap[1].
					// Size of the heap is decreased.  Now heap[1] has to be filled.
					// We put the last key in its place and see if it fits.  If it
					// does not fit, take minimum key among both its children and
					// replaces parent with it.  Again See if the last key fits 
					//in that place.
					int32_t lastKey;
					T lastValue;	
					int32_t child,now;

					// empty heap, just return
					if (m_size == 0) return; 

					lastKey = m_kvs[m_size].key;
					lastValue = m_kvs[m_size].value;
					m_size--;

					// now refers to the index at which we are now
					for(now = 1; now*2 <= m_size ;now = child) {
						// child is the index of the key which is minimum among 
						// both the children, Indexes of children are i*2 and i*2 + 1
						child = now*2;
						// child!=heapSize beacuse heap[heapSize+1] does not exist, 
						// which means it has only one child 
						if(child != m_size && m_kvs[child+1].key < m_kvs[child].key) {
							child++;	// choose the minium one.
						}
						// To check if the last key fits or not it suffices to check 
						// if the last key is less than the minimum key among both the children
						if(lastKey > m_kvs[child].key) {
							m_kvs[now] = m_kvs[child];
							(*m_idx)[m_kvs[now].value] = now;	// record index
						}
						else { // It fits there
							break;
						}
					}

					m_kvs[now].key 	= lastKey;
					m_kvs[now].value= lastValue;
					(*m_idx)[lastValue] 	= now;	// record index
				}

				/**
				 * so called DECREASE KEY operation.
				 * step 1. find the value
				 * step 2. decrease the key to the newkey
				 */
				void decrease_key(T value, int32_t newkey) {
					int32_t index = (*m_idx)[value];
					if (index > m_size || index == 0) return; 	// value not found 
					if (newkey >= m_kvs[index].key) return; 	// violate DECREASE meanning.
					T oldvalue = m_kvs[index].value;

					int now = index;
					while(m_kvs[now/2].key > newkey) {
						m_kvs[now] = m_kvs[now/2];
						(*m_idx)[m_kvs[now].value] = now;	// record index
						now /= 2;
					}

					m_kvs[now].key 	= newkey;
					m_kvs[now].value = oldvalue;
				}
		};
}

#endif //
