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
 * define key-value pair of heap struct.
 */
typedef struct {
	int key;
	uintptr_t value;
} HeapKV;

/**
 * define binary heap structure.
 */
struct Heap {
	uint32_t size;	// current heap size.
	uint32_t max;	// max heap size.
	HeapKV * kvs;	// key value pairs.
};

#define HEAP_ASSIGN(heap, idx, _key, _value) 	\
do {										\
	heap->kvs[idx].key = _key;					\
	heap->kvs[idx].value = _value;				\
} while(0)

#define HEAP_MIN_KEY(heap) (heap->kvs[1].key)
#define HEAP_MIN_VALUE(heap) (heap->kvs[1].value)

/**
 * HEAP_FOR_EACH	iterate over list of given type
 * @counter an integer variable for counting
 * @data:	the type * to use as a loop counter.
 * @heap:	the heap struct 
 */
#define HEAP_FOR_EACH(counter, data, heap)				\
	for (counter=1,data=(typeof(*data) *)(heap->kvs[counter].value); \
		counter<=heap->size; \
		counter++, data=(typeof(*data) *)(heap->kvs[counter].value))

/**
 * heap structure init, 'max' element is allocated.
 */
static inline struct Heap * 
heap_init(int max)
{
	struct Heap * heap = (struct Heap *)malloc(sizeof(struct Heap));
	heap->size = 0;
	heap->max = max+1;
	heap->kvs = (HeapKV *)malloc(sizeof(HeapKV) * heap->max);
	heap->kvs[0].key = -INT_MAX;
	return heap;
}

/**
 * insert a 'key'->'value' pair into the heap.
 */
static inline void 
heap_insert(struct Heap * heap, int key, uintptr_t value)
{
	// heap full, just return;
	if(heap->size == heap->max) return; 

    heap->size++;
	HEAP_ASSIGN(heap, heap->size, key, value);/*heap_insert in the last place*/

    /*Adjust its position*/
    int now = heap->size;
    while(heap->kvs[now/2].key > key) 
    {
		heap->kvs[now] = heap->kvs[now/2];
        now /= 2;
    }
	HEAP_ASSIGN(heap, now, key, value);
}

/**
 * test whether the heap is empty.
 */
static inline bool
heap_is_empty(struct Heap * heap)
{
	return (heap->size==0)?true:false;
}

/**
 * delete the min element --> heap top.
 */
static void 
heap_delete_min(struct Heap * heap)
{
    // heap[1] is the minimum key. So we remove heap[1].
	// Size of the heap is decreased.  Now heap[1] has to be filled.
	// We put the last key in its place and see if it fits.  If it
	// does not fit, take minimum key among both its children and
	// replaces parent with it.  Again See if the last key fits 
	//in that place.
    int lastKey;
	uintptr_t lastValue;	
	int child,now;

	// empty heap, just return
	if (heap->size == 0) return; 
   
    lastKey = heap->kvs[heap->size].key;
    lastValue = heap->kvs[heap->size].value;
	heap->size--;

    // now refers to the index at which we are now
    for(now = 1; now*2 <= heap->size ;now = child)
    {
		// child is the index of the key which is minimum among 
		// both the children, Indexes of children are i*2 and i*2 + 1
		child = now*2;
		// child!=heapSize beacuse heap[heapSize+1] does not exist, 
		// which means it has only one child 
		if(child != heap->size && 
			heap->kvs[child+1].key < heap->kvs[child].key) {
			child++;	// choose the minium one.
		}
		// To check if the last key fits or not it suffices to check 
		// if the last key is less than the minimum key among both the children
		if(lastKey > heap->kvs[child].key) {
			heap->kvs[now] = heap->kvs[child];
		}
		else { // It fits there
			break;
		}
    }

	HEAP_ASSIGN(heap, now, lastKey, lastValue);
}

/**
 * so called DECREASE KEY operation.
 */
static inline void 
heap_decrease_key(struct Heap * heap, int index, int key)
{
	if (key >= heap->kvs[index].key) return; 	// violate DECREASE meanning.
	
    int now = index;
	uintptr_t value = heap->kvs[index].value;

    while(heap->kvs[now/2].key > key) 
    {
		heap->kvs[now] = heap->kvs[now/2];
        now /= 2;
    }
	HEAP_ASSIGN(heap, now, key, value);
}

/**
 * find the index where value resides
 */
static inline int 
heap_find_value(const struct Heap * heap, const uintptr_t value)
{
	int i;
    for (i=1;i<=heap->size;i++) {
        if (heap->kvs[i].value == value) return i;
    }
	return -1;
}

#endif //
