/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * Quickselect
 *   In computer science, a quickselect is a selection algorithm related to the
 * quicksort sorting algorithm. Like quicksort, it was developed by Tony Hoare, 
 * and thus is also known as Hoare's selection algorithm. Like quicksort, it is
 * efficient in practice and has good average-case performance, but has poor
 * worst-case performance. Quickselect and variants is the selection algorithm  
 * most often used in efficient real-world implementations.
 *
 * http://en.wikipedia.org/wiki/Quickselect
 *
 ******************************************************************************/

#ifndef ALGO_RANDOM_SELECT_H__
#define ALGO_RANDOM_SELECT_H__

#include <generic.h> 

namespace alg {
	/**
	 * the random_select partition routine
	 */
	template<typename T>
		static int partition_(T list[],int begin, int end) {
			int pivot_idx = RANDOM(begin,end);
			T pivot = list[pivot_idx];
			swap(list[begin],list[pivot_idx]);

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
	 * select the k-th smallest number in 'list' of range [begin, end]
	 */
	template<typename T>
		static int random_select(T list[], int begin, int end, int k) {
			if(begin == end)
				return begin;

			int pivot_idx = partition_<T>(list, begin, end);
			int human_idx = pivot_idx - begin + 1;

			if(k < human_idx)
				return random_select(list, begin, pivot_idx - 1, k);
			else if(k > human_idx)
				return random_select(list, pivot_idx+1, end, k - human_idx);

			return pivot_idx;
		}
}

#endif //
