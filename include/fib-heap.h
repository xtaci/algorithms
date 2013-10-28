/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * FIBONACCI HEAP
 *
 * In computer science, a Fibonacci heap is a heap data structure consisting of 
 * a collection of trees. It has a better amortized running time than a binomial
 * heap. Fibonacci heaps were developed by Michael L. Fredman and Robert E. Tarjan
 * in 1984 and first published in a scientific journal in 1987. The name of 
 * Fibonacci heap comes from Fibonacci numbers which are used in the 
 * running time analysis.
 *
 * http://en.wikipedia.org/wiki/Fibonacci_heap
 ******************************************************************************/

#ifndef __FIB_HEAP_H__
#define __FIB_HEAP_H__
#include <stdint.h>
namespace alg {
	template<typename _Key,typename _Val>
	class FibHeap {
	public:
		typedef _Key key_type;
		typedef _Val value_type;
		typedef struct node_t {
			int32_t degree;
			node_t * parent;
			node_t * child;	
			bool mark;
			key_type key;
			value_type value;
		} *Node;
	private:
		FibHeap(const FibHeap &);
		FibHeap& operator=(const FibHeap&);
	private:
		int32_t n;	
		Node min;
	public:
		FibHeap() {
		}
	};
}

#endif //
