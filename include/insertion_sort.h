/*******************************************
 * DANIEL'S PRIVATE ALGORITHM IMPLEMENTAIONS
 * Insertion Sort 
 * 1. sort array in O(n^2) time.
 *******************************************/
#ifndef __INSERTION_SORT_H__
#define __INSERTION_SORT_H__

/**
 * insertion sort an array
 */
inline void insertion_sort(int *array , int number_of_elements)
{
	int iter,jter;
	for(iter=1;iter<number_of_elements;iter++)
	{
		int current_element = array[iter];
		jter = iter-1;
		while(jter>=0 && array[jter] > current_element)
		{
			array[jter+1] = array[jter];
			jter--;
		}
		array[jter+1] = current_element;
	}
}

#endif //
