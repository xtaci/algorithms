/*******************************************************************************
 * ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * LINEAR SEARCH
 *
 * Features:
 * 1. find a target value within a unsorted list using O(n) time.
 *
 * https://en.wikipedia.org/wiki/Linear_search
 *
 ******************************************************************************/

#ifndef ALGO_LINEARSEARCH_H__
#define ALGO_LINEARSEARCH_H__

namespace alg {
	/**
	 * linear search, return the position of the target value.
	 * if not found, return -1.
	 */
	template<typename T>
		static int linear_search(T list[],int list_size, T target)
		{
			for(int i = 0; i < list_size; i++)
			{
				// return target position if found
				if(list[i] == target)
					return i;
			}
			// if target not found
			return -1;
		}
}

#endif //