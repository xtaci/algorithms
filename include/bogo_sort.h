/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 * 
 * INSERTION SORT 
 *
 * 1. sort array in O((n-1)*n!) time.
 * 
 * https://en.wikipedia.org/wiki/Bogosort
 *
 ******************************************************************************/

#ifndef ALGO_BOGO_SORT_H__
#define ALGO_BOGO_SORT_H__

#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

namespace alg {
	/**
	 * bogo sort an array
	 */

	template<typename T>
		static bool is_sorted(T *array, int number_of_elements);

	template<typename T>
		static void bogo_sort(T *array , int number_of_elements) {
			std::random_device rd;
			std::mt19937 generator(rd());
			while(!is_sorted<int>(array, number_of_elements)) {
				std::shuffle(array, array+number_of_elements, generator);
			}
		}

	template<typename T>
		static bool is_sorted(T *array, int number_of_elements) {
			int iter;
			for(iter=1;iter<number_of_elements;iter++) {
				if(array[iter]<array[iter-1]) {
					return false;
				}
			}
			return true;
		}
}

#endif //
