/*******************************************************************************
 * ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * BUBBLE SORT
 *
 *   Bubble sort, sometimes incorrectly referred to as sinking sort, is a simple
 * sorting algorithm that works by repeatedly stepping through the list to be 
 * sorted, comparing each pair of adjacent items and swapping them if they are 
 * in the wrong order. The pass through the list is repeated until no swaps are
 * needed, which indicates that the list is sorted. The algorithm gets its name
 * from the way smaller elements "bubble" to the top of the list. Because it 
 * only uses comparisons to operate on elements, it is a comparison sort. 
 * Although the algorithm is simple, most of the other sorting algorithms are 
 * more efficient for large lists.
 *
 * http://en.wikipedia.org/wiki/Bubble_sort
 ******************************************************************************/
# Python program for implementation of Bubble Sort 

def bubbleSort(arr): 
	n = len(arr) 

	# Traverse through all array elements 
	for i in range(n): 

		# Last i elements are already in place 
		for j in range(0, n-i-1): 

			# traverse the array from 0 to n-i-1 
			# Swap if the element found is greater 
			# than the next element 
			if arr[j] > arr[j+1] : 
				arr[j], arr[j+1] = arr[j+1], arr[j] 

# Driver code to test above 
arr = [64, 34, 25, 12, 22, 11, 90] 

bubbleSort(arr) 

print ("Sorted array is:") 
for i in range(len(arr)): 
	print ("%d" %arr[i]), 


#endif // _BUBBLE_SORT_H_
