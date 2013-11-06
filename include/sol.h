/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * SELF ORGANIZED LINKED-LIST
 *
 * Features:
 * 1. Implementation of MTF (move-to-front)
 * 2. Implementation of MAO (move-ahead-one position)
 * 3. Based on double linked list
 *
 * http://en.wikipedia.org/wiki/Self-organizing_list
 *
 ******************************************************************************/

#ifndef __SOL_H__
#define __SOL_H__
#include "double_linked_list.h"

namespace alg {
	/**
	 * Move a node to the front
	 */
	static inline void list_mtf(struct list_head *entry, struct list_head *head) {
		if (entry->prev == head) return;
		__list_del(entry->prev, entry->next);
		__list_add(entry, head, head->next);
	}


	/**
	 * Move a node ahead one position
	 */
	static inline void list_mao(struct list_head *entry, struct list_head * head) {
		// if the entry in the 1st position
		if (entry->prev == head) return;
		struct list_head * prev = entry->prev;
		__list_del(entry->prev, entry->next);
		__list_add(entry, prev->prev, prev);
	}
}
#endif //
