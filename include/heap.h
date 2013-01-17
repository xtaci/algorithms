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

struct Heap {
	uint32_t size;
	uint32_t max;
	int * keys;
	void ** values;
};

#define HEAP_COPY(heap, to, from) 		\
do {										\
	heap->keys[to] = heap->keys[from];			\
	heap->values[to] = heap->values[from];		\
} while(0)


#define HEAP_ASSIGN(heap, idx, key, value) 	\
do {										\
	heap->keys[idx] = key;					\
	heap->values[idx] = value;				\
} while(0)

#define HEAP_MIN_KEY(heap) (heap->keys[1])
#define HEAP_MIN_VALUE(heap) (heap->values[1])

/**
 * HEAP_FOR_EACH	iterate over list of given type
 * @counter an integer variable for counting
 * @data:	the type * to use as a loop counter.
 * @heap:	the heap struct 
 */
#define HEAP_FOR_EACH(counter, data, heap)				\
	for (counter=1,data=(typeof(*data) *)(heap->values[counter]); \
		counter<=heap->size; \
		counter++, data=(typeof(*data) *)(heap->values[counter]))

/**
 * heap init
 */
inline struct Heap * heap_init(int max)
{
	struct Heap * heap = (struct Heap *)malloc(sizeof(struct Heap));
	heap->size = 0;
	heap->max = max+1;
	heap->keys = (int *)malloc(sizeof(int) * heap->max);
    heap->keys[0] = -INT_MAX;
	heap->values= (void **)malloc(sizeof(void *) * heap->max);
	return heap;
}

/**
 * heap_insert an key->value pair into the heap 
 */
inline void heap_insert(struct Heap * heap, int key, void * value)
{
		// heap full, just return;
		if(heap->size == heap->max) return; 

        heap->size++;
		HEAP_ASSIGN(heap, heap->size, key, value);/*heap_insert in the last place*/

        /*Adjust its position*/
        int now = heap->size;
        while(heap->keys[now/2] > key) 
        {
				HEAP_COPY(heap, now, now/2);
                now /= 2;
        }
		HEAP_ASSIGN(heap, now, key, value);
}

inline bool heap_is_empty(struct Heap * heap)
{
	return (heap->size==0)?true:false;
}

inline void heap_delete_min(struct Heap * heap)
{
        /* heap[1] is the minimum key. So we remove heap[1]. Size of the heap is decreased. 
           Now heap[1] has to be filled. We put the last key in its place and see if it fits.
           If it does not fit, take minimum key among both its children and replaces parent with it.
           Again See if the last key fits in that place.*/
        int lastKey;
		void * lastValue;	
 		int child,now;

		// empty heap, just return
		if (heap->size == 0) return; 
       
        lastKey = heap->keys[heap->size];
        lastValue = heap->values[heap->size];
		heap->size--;

        /* now refers to the index at which we are now */
        for(now = 1; now*2 <= heap->size ;now = child)
        {
                /* child is the index of the key which is minimum among both the children */ 
                /* Indexes of children are i*2 and i*2 + 1*/
                child = now*2;
                /*child!=heapSize beacuse heap[heapSize+1] does not exist, which means it has only one 
                  child */
                if(child != heap->size && heap->keys[child+1] < heap->keys[child] ) 
                {
                        child++;
                }
                /* To check if the last key fits ot not it suffices to check if the last key
                   is less than the minimum key among both the children*/
                if(lastKey > heap->keys[child])
                {
					HEAP_COPY(heap, now, child);
                }
                else /* It fits there */
                {
                        break;
                }
        }

		HEAP_ASSIGN(heap, now, lastKey, lastValue);
}

/**
 * so called DECREASE KEY operation.
 */
inline void heap_decrease_key(struct Heap * heap, int index, int key)
{
	if (key >= heap->keys[index]) return; 	// violate DECREASE meanning.
	
    int now = index;
	void * value = heap->values[index];

    while(heap->keys[now/2] > key) 
    {
			HEAP_COPY(heap, now, now/2);
            now /= 2;
    }
	HEAP_ASSIGN(heap, now, key, value);
}

/**
 * find the index where data resides
 */
inline int heap_find_data(const struct Heap * heap, const void * data)
{
	int i;
    for (i=1;i<=heap->size;i++) {
        if (heap->values[i] == data) return i;
    }
	return -1;
}

#endif //
