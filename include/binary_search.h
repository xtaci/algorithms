/*******************************************************************************
 * ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * BINARY SEARCH
 *
 * Features:
 * 1. find a target value within a sorted list using O(log n) time.
 * 2. binary search is for sorted list, the input list must be sorted in non
 *.   descending order.
 *
 * https://en.wikipedia.org/wiki/Binary_search_algorithm
 *
 ******************************************************************************/

#ifndef ALGO_BINARYSEARCH_H__
#define ALGO_BINARYSEARCH_H__

namespace alg {
	/**
	 * Binary search, return the position of the target value.
	 * if not found, return -1.
	 */
	template<typename T>
		static int binary_search(T list[],int l, int r, T target)
		{
			while (l <= r)
			{
				// Compute the middle position
				int m = (l + r)/2;

				// Check if target is present at mid
				if (list[m] == target)
					return m;

				// If target greater, ignore left half
				if (list[m] < target)
					l = m + 1;

				// If target is smaller, ignore right half
				else
					r = m - 1;
			}

			// If not found
			return -1;
		}

	/**
	 * A recursive binary search implementation
	 */
	template<typename T>
		static int binary_search_r(T list[],int l, int r, T target)
		{
			if (r >= l)
			{
				int m = (l + r)/2;
				if (list[m] == target)  return m;
				if (list[m] > target) return binary_search_r(list, l, m-1, target);
				return binary_search_r(list, m+1, r, target);
			}

			// if not found
			return -1;
		}
}

#endif //