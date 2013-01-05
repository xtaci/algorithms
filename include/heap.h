/*****************************************
 * DANIEL'S PRIVATE ALGORITHM IMPLEMENTAIONS
 * Heap Data structure
 *
 * Heaps can be used as an array. For any element at array position I,
 I left child is at ( 2i ), right child is at ( 2i+1 ) and parent is 
 I at (int) (i / 2). Heap size is stored at index 0.
 *
 * Basic operations of a heap are:
 *
 * 1. Insert – Insert an element.
 * 2. Delete minimum – Delete and return the smallest item in the heap.
 *******************************************/

#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

struct Heap {
	uint32_t heapSize;
	uint32_t heapMax;
	int * heap;
};

/**
 * heap init
 */
inline struct Heap * heap_init(int max)
{
	struct Heap * heap = (struct Heap *)malloc(sizeof(struct Heap));
	heap->heapSize = 0;
	heap->heapMax = max;
	heap->heap = (int *)malloc(sizeof(int) * max);
    heap->heap[0] = -INT_MAX;

	return heap;
}

/**
 * heap_insert an element into the heap 
 */
inline void heap_insert(struct Heap * heap, int element)
{
		// heap full, just return;
		if(heap->heapSize == heap->heapMax) return; 

        heap->heapSize++;
        heap->heap[heap->heapSize] = element; /*heap_insert in the last place*/

        /*Adjust its position*/
        int now = heap->heapSize;
        while(heap->heap[now/2] > element) 
        {
                heap->heap[now] = heap->heap[now/2];
                now /= 2;
        }
        heap->heap[now] = element;
}

inline int heap_delete_min(struct Heap * heap)
{
        /* heap[1] is the minimum element. So we remove heap[1]. Size of the heap is decreased. 
           Now heap[1] has to be filled. We put the last element in its place and see if it fits.
           If it does not fit, take minimum element among both its children and replaces parent with it.
           Again See if the last element fits in that place.*/
        int minElement,lastElement,child,now;
        minElement = heap->heap[1];
        lastElement = heap->heap[heap->heapSize--];
        /* now refers to the index at which we are now */
        for(now = 1; now*2 <= heap->heapSize ;now = child)
        {
                /* child is the index of the element which is minimum among both the children */ 
                /* Indexes of children are i*2 and i*2 + 1*/
                child = now*2;
                /*child!=heapSize beacuse heap[heapSize+1] does not exist, which means it has only one 
                  child */
                if(child != heap->heapSize && heap->heap[child+1] < heap->heap[child] ) 
                {
                        child++;
                }
                /* To check if the last element fits ot not it suffices to check if the last element
                   is less than the minimum element among both the children*/
                if(lastElement > heap->heap[child])
                {
                        heap->heap[now] = heap->heap[child];
                }
                else /* It fits there */
                {
                        break;
                }
        }
        heap->heap[now] = lastElement;
        return minElement;
}



#endif //
