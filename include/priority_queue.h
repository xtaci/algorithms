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
 * 1. A queue with prioity implemented in double linked list.
 * 2. The queue is in ascending order of priority.
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
 * definition of a node of priority queue.
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
	uint32_t count;
	struct list_head head;	
};

/**
 * create an empty priority queue.
 */
static inline struct PQ * 
pq_create()
{
	struct PQ * pq;
	pq = (struct PQ *) malloc(sizeof(struct PQ));
	pq->count = 0;
	INIT_LIST_HEAD(&pq->head);
	return pq;
}

/**
 * queue a value with priority into the priority queue.
 */
static inline void 
pq_queue(struct PQ * pq, uintptr_t value, uint32_t priority)
{
	struct PQNode * n = (struct PQNode *)malloc(sizeof(struct PQNode));
	n->priority = priority;
	n->value = value;

	if (list_empty(&pq->head))	// empty list, just add in.
	{
		list_add(&n->node, &pq->head);
		pq->count++;
	}
	else
	{
		// sequentially find the apropriate position
		struct PQNode * pos;
		bool found = false;
		list_for_each_entry(pos, &pq->head, node) {
			if (n->priority <= pos->priority) {
				__list_add(&n->node, pos->node.prev, &pos->node);
				pq->count++;
				found = true;
				break;
			}
		}

		if (!found) {	// we reach the end of the list.
			list_add_tail(&n->node, &pq->head);
			pq->count++;
		}
	}

	return;
}

/**
 * dequeue the most priority element, i.e. the first element.
 * return 0 when the list is empty.
 * check pq_is_empty() before pq_dequeue().
 */
static inline uintptr_t 
pq_dequeue(struct PQ *pq, uint32_t * prio )
{
	if (list_empty(&pq->head)) return 0;

	struct PQNode * n;
	n = list_entry(pq->head.next, struct PQNode, node);
	list_del(&n->node);
	pq->count--;

	uintptr_t ret = n->value;
	*prio = n->priority;
	free(n);

	return ret;
}

/**
 * test whether the priority queue is empty
 */
static inline bool 
pq_is_empty(struct PQ *pq)
{
	if (list_empty(&pq->head)) return true;
	return false;
}

/**
 * get the exact number of data
 */
static inline uint32_t 
pq_count(struct PQ *pq)
{
	return pq->count;
}

/**
 * safe destroy the priority queue
 */
static inline void 
pq_destroy(struct PQ * pq)
{
	struct PQNode * pos, * n;
	list_for_each_entry_safe(pos,n, &pq->head, node) {
		list_del(&pos->node);
	}
}

#endif //
