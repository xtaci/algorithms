/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * PRIORITY QUEUE 
 *
 * Features:
 * 1. A queue with prioity implemented in double linked list
 *
 * http://en.wikipedia.org/wiki/Priority_queue
 *
 ******************************************************************************/

#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "double_linked_list.h"

/**
 * definition of node of priority queue.
 */
struct PQNode {
	uint32_t priority;		
	uintptr_t value;
	struct list_head node;
};

/**
 * definition of a Priority Queue.
 */
struct PQ {
	struct list_head head;	
};

/**
 * create an empty priority queue.
 */
inline struct PQ * pq_create()
{
	struct PQ * pq;
	pq = (struct PQ *) malloc(sizeof(struct PQ));
	INIT_LIST_HEAD(&pq->head);
	return pq;
}

/**
 * queue a value with priority into the priority queue.
 */
inline void pq_queue(struct PQ * pq, uintptr_t value, uint32_t priority)
{
	struct PQNode * n = (struct PQNode *)malloc(sizeof(struct PQNode));
	n->priority = priority;
	n->value = value;

	if (list_empty(&pq->head))
	{
		list_add(&n->node, &pq->head);
	}
	else
	{
		struct PQNode * pos;
		list_for_each_entry(pos, &pq->head, node) {
			if (n->priority <= pos->priority) {
				__list_add(&n->node, pos->node.prev, &pos->node);
				break;
			}
		}
	}

	return;
}

/**
 * dequeue the most priority element
 */
inline uintptr_t pq_dequeue(struct PQ *pq)
{
	if (list_empty(&pq->head)) return 0;

	struct PQNode * n;
	n = list_entry(pq->head.next, struct PQNode, node);
	list_del(&n->node);

	uintptr_t ret = n->value;
	free(n);

	return ret;
}

/**
 * test whether the priority queue is empty
 */
inline bool pq_is_empty(struct PQ *pq)
{
	if (list_empty(&pq->head)) return true;
	return false;
}

#endif //
