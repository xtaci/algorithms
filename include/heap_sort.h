/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _
 * /--\ | (_| (_) |  |  |_ | | | | | _>
 *         _|
 *
 * HEAPSORT
 *
 * Features:
 * 1. Although somewhat slower in practice on most machines than a well-implemented quicksort,
      it has the advantage of a more favorable worst-case O(n log n) runtime
 *
 * http://en.wikipedia.org/wiki/Heapsort
 *
 ******************************************************************************/

#ifndef __HEAPSORT_H__
#define __HEAPSORT_H__

#include <heap.h>

namespace alg
{


	/**
	 * heap sort an array
	 */
	template<typename T>
	static void heapsort(T *array,int number_of_elements)
	{
		Heap<T> heap(number_of_elements);
		int i;

		// In order to build a heap structure from input array
		for(i=0;i<number_of_elements;i++)
		{
			heap.insert(array[i],0);    //set key with the value of the array,value to 0(no use)
		}
		
		// Temporary array to store the minkey of each step,which is deleted from the heap
		T tempArray[number_of_elements];
		for(i=0;i<number_of_elements;i++)
		{
			tempArray[i]=heap.min_key();    //find the min key
			heap.delete_min();
		}

		for(i=0;i<number_of_elements;i++)
		{
			array[i]=tempArray[i];      //copy back to the original array
		}
	}
}

#endif //

