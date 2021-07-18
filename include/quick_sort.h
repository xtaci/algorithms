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

#ifndef ALGO_QUICKSORT_H__
#define ALGO_QUICKSORT_H__

#include <generic.h> 

namespace alg {
	/**
	 * the quick-sort partition routine
	 */
	template<typename T>
		static int partition_(T list[],int begin, int end) {
			int pivot_idx = RANDOM(begin,end);
			T pivot = list[pivot_idx];
			swap(list[begin], list[pivot_idx]);

			int i = begin + 1;
			int j = end;

			while(i <= j) {
				while((i <= end) && (list[i] <= pivot))
					i++;
				while((j >= begin) && (list[j] > pivot))
					j--;
				if(i < j)
					swap(list[i],list[j]);
			}

			swap(list[begin],list[j]);
			return j; // final pivot position
		}

	/**
	 * quick sort an array of range [begin, end]
	 */
	template<typename T>
		static void quicksort(T list[],int begin,int end) {
			if( begin < end) {
				int pivot_idx = partition_<T>(list, begin, end);
				quicksort(list, begin, pivot_idx-1);
				quicksort(list, pivot_idx+1, end);
			}
		}
}

#endif //
