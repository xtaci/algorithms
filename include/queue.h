/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 * QUEUE 
 *
 * Features:
 * 1. Queue with capcity 
 *
 * http://en.wikipedia.org/wiki/Queue_(data_structure)
 *
 ******************************************************************************/

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdbool.h>
#include <stdint.h>

/**
 * Queue has five properties. capacity stands for the maximum number of 
 * elements Queue can hold. Size stands for the current size of the Queue
 * and elements is the array of elements. front is the index of first element
 * (the index at which we remove the element) and rear is the index of last
 * element (the index at which we insert the element) 
 */
typedef struct Queue
{
	uint32_t capacity;
	uint32_t size;
	uint32_t front;
	int32_t rear;
	uintptr_t * elements;
}Queue;

/**
 * create_queue function takes argument the maximum number of elements the Queue
 * can hold, creates a Queue according to it and returns a pointer to the
 * Queue. 
 */
inline Queue * create_queue(uint32_t maxElements)
{
	/* Create a Queue */
	Queue *Q;
	Q = (Queue *)malloc(sizeof(Queue));
	/* Initialise its properties */
	Q->elements = (uintptr_t *)malloc(sizeof(uintptr_t)*maxElements);
	Q->size = 0;
	Q->capacity = maxElements;
	Q->front = 0;
	Q->rear = -1;
	/* Return the pointer */
	return Q;
}

/**
 * Dequeue
 */
inline void dequeue(Queue *Q)
{
	/* If Queue size is zero then it is empty. So we cannot pop */
	if(Q->size==0)
	{
		return;
	}
	/* Removing an element is equivalent to incrementing index of front by one */
	else
	{
		Q->size--;
		Q->front++;
		/* As we fill elements in circular fashion */
		if(Q->front==Q->capacity)
		{
			Q->front=0;
		}
	}
	return;
}

/**
 * return the front element.
 */
inline uintptr_t queue_front(const Queue *Q)
{
	/* Return the element which is at the front*/
	return Q->elements[Q->front];
}

inline bool queue_is_empty(const Queue * Q)
{
	if (Q->size ==0) return true;
	return false;
}

/**
 * Enqueue
 * returns false when queue is full
 */
inline bool enqueue(Queue *Q, uintptr_t element)
{
	/* If the Queue is full, we cannot push an element into it as there is no space for it.*/
	if(Q->size == Q->capacity)
	{
		return false;
	}
	else
	{
		Q->size++;
		Q->rear = Q->rear + 1;
		/* As we fill the queue in circular fashion */
		if(Q->rear == Q->capacity)
		{
			Q->rear = 0;
		}
		/* Insert the element in its rear side */ 
		Q->elements[Q->rear] = element;
	
		return true;
	}
}

/**
 * queue destroy 
 */
inline void queue_destroy(Queue * Q)
{
	free(Q->elements);
	free(Q);
}

#endif //
