/*****************************************
 * DANIEL'S PRIVATE ALGORITHM IMPLEMENTAIONS
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
 *******************************************/

#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

struct Heap {
	uint32_t size;
	uint32_t max;
	int * keys;
	void ** values;
};

#define HEAP_COPY(heap, idx1, idx2) 		\
do {										\
	heap->keys[idx1] = heap->keys[idx2];			\
	heap->values[idx1] = heap->values[idx2];		\
} while(0)


#define HEAP_ASSIGN(heap, idx, key, value) 	\
do {										\
	heap->keys[idx] = key;					\
	heap->values[idx] = value;				\
} while(0)

#define HEAP_MIN_KEY(heap) (heap->keys[1])
#define HEAP_MIN_VALUE(heap) (heap->values[1])

/**
 * heap init
 */
inline struct Heap * heap_init(int max)
{
	struct Heap * heap = (struct Heap *)malloc(sizeof(struct Heap));
	heap->size = 0;
	heap->max = max;
	heap->keys = (int *)malloc(sizeof(int) * max);
    heap->keys[0] = -INT_MAX;
	heap->values= (void **)malloc(sizeof(void *) * max);
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
		HEAP_ASSIGN(heap, now, key, value);/*heap_insert in the last place*/
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



#endif //
