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

#ifndef ALGO_PRIORITY_QUEUE_H__
#define ALGO_PRIORITY_QUEUE_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "double_linked_list.h"

namespace alg {
	/**
	 * definition of a Priority Queue.
	 */
	template<typename T>
		class PQ {
			/**
			 * definition of a node of priority queue.
			 */
			struct PQNode {
				int priority;		
				T value;
				struct list_head node;
			};

			private:
			uint32_t m_count;
			struct list_head m_head;	
			public:
			/**
			 * create an empty priority queue.
			 */
			PQ() {
				m_count = 0;
				INIT_LIST_HEAD(&m_head);
			}

			~PQ() {
				PQNode * pos, * n;
				list_for_each_entry_safe(pos,n, &m_head, node) {
					list_del(&pos->node);
					delete pos;
				}
			}
			private:
			PQ(const PQ&);
			PQ& operator=(const PQ&);
			public:

			/**
			 * queue a value with priority into the priority queue.
			 */
			void queue(const T &value, uint32_t priority) {
				PQNode * n = new PQNode;
				n->priority = priority;
				n->value = value;

				if (list_empty(&m_head)) {	// empty list, just add in.
					list_add(&n->node, &m_head);
					m_count++;
				} else {
					// sequentially find the appropriate position
					PQNode * pos;
					bool found = false;
					list_for_each_entry(pos, &m_head, node) {
						if (n->priority <= pos->priority) {
							list_add_(&n->node, pos->node.prev, &pos->node);
							m_count++;
							found = true;
							break;
						}
					}

					if (!found) {	// we reach the end of the list.
						list_add_tail(&n->node, &m_head);
						m_count++;
					}
				}
			}

			/**
			 * return top element
			 * check is_empty() before top().
			 */
			inline const T & top(int * prio) const {
				PQNode * n;
				n = list_entry(m_head.next, PQNode, node);
				*prio = n->priority;
				return n->value;
			}

			/**
			 * dequeue the most priority element, i.e. the first element.
			 */
			inline void dequeue() {
				if (list_empty(&m_head)) return;

				PQNode * n;
				n = list_entry(m_head.next, PQNode, node);
				list_del(&n->node);
				m_count--;
				delete n;
			}

			/**
			 * test whether the priority queue is empty
			 */
			inline bool is_empty() const {
				if (list_empty(&m_head)) return true;
				return false;
			}

			/**
			 * get the exact number of data
			 */
			inline uint32_t count() const { return m_count; }
		};
}

#endif //
