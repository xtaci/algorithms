/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * MERGE SORT
 *
 * Features:
 *   This is divide and conquer algorithm. This works as follows.
 *   (1) Divide the input which we have to sort into two parts in the middle. Call it the left part 
 *       and right part.
 *           Example: Say the input is  -10 32 45 -78 91 1 0 -16 then the left part will be  
 *           -10 32 45 -78 and the right part will be  91 1 0 6.
 *   (2) Sort Each of them separately. Note that here sort does not mean to sort it using some other
 *            method. We already wrote function to sort it. Use the same.
 *   (3) Then merge the two sorted parts.
 *
 * ------------
 * Worst case performance		O(n log n)
 * Best case performance	
 * 								O(n log n) typical,
 * 								O(n) natural variant
 * Average case performance		O(n log n)
 * Worst case space complexity	O(n) auxiliary
 * ------------
 *
 * Merge sort can easily be optmized for parallized computing.
 *
 * http://en.wikipedia.org/wiki/Merge_sort
 *
 ******************************************************************************/

#ifndef ALGO_MERGE_SORT_H__
#define ALGO_MERGE_SORT_H__

namespace alg {
	/**
	 * Merge functions merges the two sorted parts. Sorted parts will be from [left, mid] and [mid+1, right].
	 */
	template<typename T>
		static void merge_(T *array, int left, int mid, int right) {
			/*We need a Temporary array to store the new sorted part*/
			T tempArray[right-left+1];
			int pos=0,lpos = left,rpos = mid + 1;
			while(lpos <= mid && rpos <= right) {
				if(array[lpos] < array[rpos]) {
					tempArray[pos++] = array[lpos++];
				}
				else {
					tempArray[pos++] = array[rpos++];
				}
			}
			while(lpos <= mid)  tempArray[pos++] = array[lpos++];
			while(rpos <= right)tempArray[pos++] = array[rpos++];
			int iter;
			/* Copy back the sorted array to the original array */
			for(iter = 0;iter < pos; iter++) {
				array[iter+left] = tempArray[iter];
			}
			return;
		}

	/**
	 * sort an array from left->right 
	 */
	template<typename T>
		static void merge_sort(T *array, int left, int right) {
			int mid = (left+right)/2;
			/* We have to sort only when left<right because when left=right it is anyhow sorted*/
			if(left<right) {
				/* Sort the left part */
				merge_sort(array,left,mid);
				/* Sort the right part */
				merge_sort(array,mid+1,right);
				/* Merge the two sorted parts */
				merge_(array,left,mid,right);
			}
		}

}

#endif //
