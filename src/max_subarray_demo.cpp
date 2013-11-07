#include <stdio.h>
#include "max_subarray.h"

using namespace alg;
int main() {
	int arr[] = {13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
	int arr2[] = {1,-1,-2,-3,-4};

	int begin;
	int end;
	int i;

	printf("the array:\n");
	for (i=0;i<int(sizeof(arr)/sizeof(int));i++) {
		printf("%d\t", arr[i]);
	}

	printf("\n");
	max_subarray(arr, sizeof(arr)/sizeof(int), &begin, &end);
	printf("the maximum subarray [%d %d]:\n", begin, end);
	for (i=begin;i<=end;i++) {
		printf("%d\t", arr[i]);
	}
	printf("\n");
	
	max_subarray(arr2, sizeof(arr2)/sizeof(int), &begin, &end);
	printf("%d %d\n", begin, end);
	for (i=begin;i<=end;i++) {
		printf("%d\t", arr2[i]);
	}
	printf("\n");
}
