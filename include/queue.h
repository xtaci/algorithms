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

#ifndef ALGO_QUEUE_H__
#define ALGO_QUEUE_H__

#include <stdbool.h>
#include <stdint.h>
#include <exception>

namespace alg {
	/**
	 * Queue Definition
	 */
	template<typename T>
		class Queue {
			private:
				class QueueEmptyException: public std::exception {
					public:
						virtual const char * what() const throw() {
							return "Queue is empty.";
						}
				} excp_empty;

			private:
				uint32_t m_capacity;		// queue capacity
				uint32_t m_size;			// current queue size
				uint32_t m_front;			// index of the first element
				uint32_t m_rear;			// index of the last element
				T * m_elements;	// the elements

			public:
				/**
				 * constructor takes argument the maximum number of elements the Queue
				 * can hold, creates a Queue according to it and returns a pointer to the
				 * Queue. 
				 */
				Queue(uint32_t max) {
					this->m_elements = new T[max];
					this->m_size = 0;
					this->m_capacity = max;
					this->m_front =0;
					this->m_rear = -1;
				};

				~Queue() {
					delete [] m_elements;	
				};
			private:
				Queue(const Queue &);
				Queue& operator=(const Queue &);
			public:
				/**
				 * Dequeue
				 */
				inline void dequeue() {
					/* If Queue size is zero then it is empty. So we cannot pop */
					if(m_size==0) {
						return;
					}
					/* Removing an element is equivalent to incrementing index of front by one */
					else {
						m_size--;
						m_front++;
						/* As we fill elements in circular fashion */
						if(m_front==m_capacity) {
							m_front=0;
						}
					}
					return;
				};

				/**
				 * return the front element.
				 */
				inline const T& front() const {
					if (m_size==0) throw excp_empty;
					return m_elements[m_front];	
				};

				/**
				 * test weather the queue is empty
				 */
				inline bool is_empty() const {
					if (m_size ==0) return true;
					return false;
				};

				/**
				 * enqueue an element
				 * returns false when queue is full
				 */
				bool enqueue(const T & element) {
					// If the Queue is full, we cannot push an element into it
					// as there is no space for it.*/
					if(m_size == m_capacity) {
						return false;
					}
					else {
						m_size++;
						m_rear++;
						/* As we fill the queue in circular fashion */
						if(m_rear == m_capacity) {
							m_rear = 0;
						}
						/* Insert the element in its rear side */ 
						m_elements[m_rear] = element;

						return true;
					}
				};

				/**
				 * return the queue count.
				 */
				inline uint32_t count() const { return m_size; };

				/**
				 * return the queue capacity.
				 */
				inline uint32_t capcity() const { return m_capacity; };
		};
}
#endif //
