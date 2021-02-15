/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 * 
 * INSERTION SORT 
 *
 * 1. sort array in O(n^2) time.
 * 
 * http://en.wikipedia.org/wiki/Insertion_sort
 *
 ******************************************************************************/

#ifndef ALGO_INSERTION_SORT_H__
#define ALGO_INSERTION_SORT_H__

namespace alg {
	/**
	 * insertion sort an array
	 */
	template<typename T>
		static void insertion_sort(T *array , int number_of_elements) {
			int iter,jter;
			for(iter=1;iter<number_of_elements;iter++) {
				T current_element = array[iter];
				jter = iter-1;
				while(jter>=0 && array[jter] > current_element) {
					array[jter+1] = array[jter];
					jter--;
				}
				array[jter+1] = current_element;
			}
		}
}

#endif //

// *************************one other way of insertion sort using c++***********************************
#include <bits/stdc++.h> 
using namespace std; 

/* Function to sort an array using insertion sort*/
void insertionSort(int arr[], int n) 
{ 
	int i, key, j; 
	for (i = 1; i < n; i++) 
	{ 
		key = arr[i]; 
		j = i - 1; 
		while (j >= 0 && arr[j] > key) 
		{ 
			arr[j + 1] = arr[j]; 
			j = j - 1; } 
		arr[j + 1] = key; }} 

//function to print an array of size n 
void printArray(int arr[], int n) 
{ int i; 
	for (i = 0; i < n; i++) 
	cout << arr[i] << " "; 
	cout << endl; 
} 
int main() 
{ 
	int arr[] = { 12, 11, 13, 5, 6 }; 
	int n = sizeof(arr) / sizeof(arr[0]); 
	insertionSort(arr, n); 
	printArray(arr, n); 
	return 0; 
} 
 

