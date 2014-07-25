/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * QUICKSORT
 *
 * Features:
 * 1. sort array in O(nlogn) time.
 * 2. most generic fast sorting algorithm
 *
 * http://en.wikipedia.org/wiki/Quick_sort
 *
 ******************************************************************************/

#ifndef __QUICKSORT_H__
#define __QUICKSORT_H__

#include <generic.h> 
#include <cassert>

namespace alg {

	/**
     * Return median of begin, middle, and end.
	 * Order these and hide the pivot.
     */
	template<typename T>
	static const T & __median3(T list[], int begin, int end) {
		assert(begin + 2 <= end);
		int middle = end - (end - begin) / 2;
		if (list[middle] < list[begin])
			swap(list[middle], list[begin]);
		if (list[end] < list[begin])
			swap(list[end], list[begin]);
		if (list[end] < list[middle])
			swap(list[end], list[middle]);
	
		//Place pivot at position [end - 1]
		swap(list[middle], list[end - 1]);
		return list[end - 1];
	}
	
	/**
	 * the quick-sort partition routine
	 */
	template<typename T>
		static int __partition(T list[],int begin, int end) {
			T pivot = __median3<T>(list, begin, end);

			int i = begin;
			int j = end - 1;

			while(i < j) {
				while(list[++i] < pivot) {}
				while(pivot < list[--j]) {}
				if(i < j)
					swap(list[i],list[j]);
			}

			swap(list[i],list[end - 1]);
			return i; // final pivot position
		}

	/**
	 * quick sort an array of range [begin, end]
	 */
	template<typename T>
		static void quicksort(T list[],int begin,int end) {
			if( begin + 1 < end) {
				int pivot_idx = __partition<T>(list, begin, end);
				quicksort(list, begin, pivot_idx-1);
				quicksort(list, pivot_idx+1, end);
			} else if ( begin + 1 == end) {
				if (list[begin] > list[end])
					swap(list[begin], list[end]);
			}
		}
}

#endif //
