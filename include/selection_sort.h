/*******************************************************************************
 * ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * SELECTION SORT
 *
 * In computer science, selection sort is a sorting algorithm, specifically an 
 * in-place comparison sort. It has O(n2) time complexity, making it inefficient
 * on large lists, and generally performs worse than the similar insertion sort.
 * Selection sort is noted for its simplicity, and it has performance advantages 
 * over more complicated algorithms in certain situations, particularly where 
 * auxiliary memory is limited.
 *
 * http://en.wikipedia.org/wiki/Selection_sort
 ******************************************************************************/

#ifndef ALGO_SELECTION_SORT_H__
#define ALGO_SELECTION_SORT_H__

#include <assert.h>
#include <generic.h>

namespace alg {
	template<typename T>
		static void SelectionSort(T list[], int start, int end) {
			int i,j;
			int iMin;

			assert(start <= end);

			for(j = start; j <= end-1; j++) {
				// assume the min is the first element */
				iMin = j;
				// test against elements after i to find the smallest
				for(i = j+1; i <= end; i++) {
					if (list[i] < list[iMin]) {
						iMin = i;
					}
				}

				// iMin is the index of the minimum element. Swap it with the current position
				if (iMin != j) {
					swap(list[j], list[iMin]);
				}
			}
		}
}

#endif //ALGO_SELECTION_SORT_H__
