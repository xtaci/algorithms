/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * STACK
 *
 * Features:
 * 1. Stack with capcity 
 * 
 * http://en.wikipedia.org/wiki/Stack_(abstract_data_type)
 *
 ******************************************************************************/

#ifndef ALGO_STACK_H__
#define ALGO_STACK_H__

#include <stdint.h>
#include <stdbool.h>
#include <exception>

namespace alg {
	/** 
	 * Stack has three properties. capacity stands for the maximum number of
	 * elements stack can hold. Size stands for the current size of the stack and elements 
	 * is the array of elements 
	 */
	template<typename T=uintptr_t>
		class Stack {
			private:
				class StackEmptyException: public std::exception {
					public:
						virtual const char * what() const throw()
						{
							return "stack is empty";
						}
				} excp_empty;

				class StackIndexOutOfBoundException: public std::exception {
					public:
						virtual const char * what() const throw()
						{
							return "Index out of bound.";
						}
				} excp_ioob;

				uint32_t m_capacity;		// the total capacity
				uint32_t m_size;			// current stack size
				T * m_elements;		// the elements

			public:
				/**
				 * capcity is the maximum elements the stack can hold.
				 */
				Stack(uint32_t capacity) {
					this->m_capacity = capacity;
					this->m_size = 0;
					this->m_elements = new T[capacity];
				}

				~Stack() {
					delete [] m_elements;
				}


			private:
				Stack(const Stack&);
				Stack& operator=(const Stack&);


			public:
				/**
				 * test whether the stack is empty
				 */
				inline bool is_empty() const { return m_size==0?true:false; } 

				/**
				 * pop stack
				 */
				inline void pop() {
					if(m_size!=0) m_size--;
					return;
				}

				/**
				 * get the top element
				 */
				inline const T& top() const {
					if (m_size==0) throw excp_empty;
					return m_elements[m_size-1]; 
				}

				/**
				 * push an element into the stack
				 * returns false when stack is full.
				 */
				inline bool push(const T & value) {
					if(m_size==m_capacity) { return false; }
					else {
						m_elements[m_size++] = value;
						return true;
					}
				}

				/**
				 * return the stack size count.
				 */
				inline uint32_t count() const { return m_size; }

				/**
				 * return value by index
				 */
				inline const T& operator[] (uint32_t idx) const {
					if (idx >= m_capacity) throw excp_ioob;
					return m_elements[m_size-1-idx]; 
				}
		};
}

#endif //
