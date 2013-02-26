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


/**
 * define binary heap structure.
 */
template<typename T>
class Heap {
private:
	/**
	 * define key-value pair of heap struct.
	 */
	class KV {
	public:
		int key;
		T value;
	};
	uint32_t m_size;	// current heap size.
	uint32_t m_max;		// max heap size.
	KV * m_kvs;			// key value pairs.
public:
	Heap(int max) {
		m_size = 0;
		m_max = max+1;
		m_kvs = new KV[m_max];
		m_kvs[0].key = INT_MIN;
	};

	~Heap() {
		delete [] m_kvs;
	};

	inline int min_key() {
		return m_kvs[1].key;
	};

	inline const T & min_value() {
		return m_kvs[1].value;
	};

	// for loop through the kvs
	inline uint32_t count() {
		return m_size;
	};

	inline const T & operator[] (uint32_t idx) {
		return m_kvs[idx+1].value;
	};

	/**
	 * insert a 'key'->'value' pair into the heap.
	 */
	void insert(int key, const T & value) {
		// heap full, just return;
		if(m_size == m_max) return; 

		m_size++;
		m_kvs[m_size].key	= key;
		m_kvs[m_size].value	= value;

		/*Adjust its position*/
		int now = m_size;
		while(m_kvs[now/2].key > key) 
		{
			m_kvs[now] = m_kvs[now/2];
			now /= 2;
		}

		m_kvs[now].key		= key;
		m_kvs[now].value	= value;
	}

	/**
	 * emptiness test
 	 */
	inline bool is_empty() {
		return (m_size==0)?true:false;
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
		int lastKey;
		T lastValue;	
		uint32_t child,now;

		// empty heap, just return
		if (m_size == 0) return; 
	   
		lastKey = m_kvs[m_size].key;
		lastValue = m_kvs[m_size].value;
		m_size--;

		// now refers to the index at which we are now
		for(now = 1; now*2 <= m_size ;now = child)
		{
			// child is the index of the key which is minimum among 
			// both the children, Indexes of children are i*2 and i*2 + 1
			child = now*2;
			// child!=heapSize beacuse heap[heapSize+1] does not exist, 
			// which means it has only one child 
			if(child != m_size && 
				m_kvs[child+1].key < m_kvs[child].key) {
				child++;	// choose the minium one.
			}
			// To check if the last key fits or not it suffices to check 
			// if the last key is less than the minimum key among both the children
			if(lastKey > m_kvs[child].key) {
				m_kvs[now] = m_kvs[child];
			}
			else { // It fits there
				break;
			}
		}

		m_kvs[now].key 	= lastKey;
		m_kvs[now].value= lastValue;
	};

	/**
	 * so called DECREASE KEY operation.
	 */
	inline void decrease_key(int index, int key)
	{
		if (key >= m_kvs[index].key) return; 	// violate DECREASE meanning.
		
		int now = index;
		uintptr_t value = m_kvs[index].value;

		while(m_kvs[now/2].key > key) 
		{
			m_kvs[now] = m_kvs[now/2];
			now /= 2;
		}

		m_kvs[now].key 	= key;
		m_kvs[now].value= value;
	};

	/**
	 * return the index where value resides
	 */
	inline int find_value(const T & value)
	{
		int i;
		for (i=1;i<=m_size;i++) {
			if (m_kvs[i].value == value) return i;
		}
		return -1;
	};

};

#endif //
