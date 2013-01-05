/*******************************************
 * DANIEL'S PRIVATE ALGORITHM IMPLEMENTAIONS
 * Queue Implementation
 * Features:
 * 1. Queue with capcity 
 *******************************************/
#ifndef __QUEUE_H__
#define __QUEUE_H__
/**
 * Queue has five properties. capacity stands for the maximum number of 
 * elements Queue can hold. Size stands for the current size of the Queue
 * and elements is the array of elements. front is the index of first element
 * (the index at which we remove the element) and rear is the index of last
 * element (the index at which we insert the element) 
 */
typedef struct Queue
{
	int capacity;
	int size;
	int front;
	int rear;
	int *elements;
}Queue;

/**
 * createQueue function takes argument the maximum number of elements the Queue
 * can hold, creates a Queue according to it and returns a pointer to the
 * Queue. 
 */
inline Queue * createQueue(int maxElements)
{
	/* Create a Queue */
	Queue *Q;
	Q = (Queue *)malloc(sizeof(Queue));
	/* Initialise its properties */
	Q->elements = (int *)malloc(sizeof(int)*maxElements);
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
inline void Dequeue(Queue *Q)
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
 * front
 * returns false when queue is empty
 */
inline int front(Queue *Q, int * rval)
{
	if(Q->size==0)
	{
		return false;
	}
	/* Return the element which is at the front*/
	*rval = Q->elements[Q->front];
	return true;
}

/**
 * Enqueue
 * returns false when queue is full
 */
inline int Enqueue(Queue *Q,int element)
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

#endif //
