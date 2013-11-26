/*******************************************************************************
 * ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * BUBBLE SORT
 *
 *   Bubble sort, sometimes incorrectly referred to as sinking sort, is a simple
 * sorting algorithm that works by repeatedly stepping through the list to be 
 * sorted, comparing each pair of adjacent items and swapping them if they are 
 * in the wrong order. The pass through the list is repeated until no swaps are
 * needed, which indicates that the list is sorted. The algorithm gets its name
 * from the way smaller elements "bubble" to the top of the list. Because it 
 * only uses comparisons to operate on elements, it is a comparison sort. 
 * Although the algorithm is simple, most of the other sorting algorithms are 
 * more efficient for large lists.
 *
 * http://en.wikipedia.org/wiki/Bubble_sort
 ******************************************************************************/

#ifndef _BUBBLE_SORT_H_
#define _BUBBLE_SORT_H_

#include <assert.h>
#include <generic.h>

namespace alg {
	template<typename T>
		static void	BubbleSort(T list[], int start, int end){
			int i;
			bool swapped;

			assert(start < end);

			do {
				swapped = false;
				for(i = start+1; i <= end; i++) {
					if(list[i-1] > list[i]) {
						// swap them and remember something changed
						swap(list[i-1], list[i]);
						swapped = true;
					}
				}
			} while(swapped);
		}
}


#endif // _BUBBLE_SORT_H_
