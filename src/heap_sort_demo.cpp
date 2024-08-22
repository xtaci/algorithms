#include<iostream>
using namespace std;

// Heap Sort by Heapify - Time Comp. -> O(N*logN)
void printArr(int arr[], int n){

	for(int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;
}

void heapify(int arr[], int n, int i){

    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // left = 2*i + 1
    int right = 2 * i + 2; // right = 2*i + 2
 
    // If left child is larger than root
    if(left < n && arr[left] > arr[largest])
        largest = left;
 
    // If right child is larger than largest so far
    if(right < n && arr[right] > arr[largest])
        largest = right;
 
    // If largest is not root
    if(largest != i){

        swap(arr[i], arr[largest]);
        heapify(arr, n, largest); // Recursively heapify the affected sub-tree
    }
}

void heapSort(int arr[], int n){

	// Build heap (rearrange array)
	for(int i = n/2 - 1; i >= 0; i--){
		heapify(arr, n, i);
	}
	// One by one extract an element from heap
	for(int i = n - 1; i >= 0; i--){

		// Move current root to end
		swap(arr[i], arr[0]);
		// call max heapify on the reduced heap
		heapify(arr, i, 0);
	}
}

int main(){

	int arr[5] = {54, 53, 55, 52, 50};
	int n = sizeof(arr) / sizeof(arr[0]);

	printArr(arr, n);

	heapSort(arr, n);

	printArr(arr, n);

	return 0;
}
