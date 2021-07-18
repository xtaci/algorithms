/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 * 
 * SHELL SORT 
 *
 * 1. sort array in O(n^(3/2)) time.
 * 
 * https://en.wikipedia.org/wiki/Shellsort
 *
 ******************************************************************************/

#ifndef ALGO_SHELL_SORT_H__
#define ALGO_SHELL_SORT_H__

namespace alg {
	/**
	 * shell sort an array
	 */
	template<typename T>
		static void shell_sort(T *array, int len) {
			int h = 1;
			while (h < len / 3) {
				h = 3 * h + 1; // 1, 4, 13, 40, 121, ...
			}
			while (h >= 1) {
				for (int i = h; i < len; i++) {
					int cur = array[i];
					int j = i - h;
					while (j >= 0 && array[j] > cur) {
						array[j + h] = array[j];
						j = j - h;
					}
					array[j + h] = cur;
				}
				h = h / 3;
			}
		}
}

#endif //
