#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include "generic.h"
#include "radix_sort.h"

int main()
{
	using namespace alg;
	const int MAX_ELEMENTS = 10;
	uint32_t list[MAX_ELEMENTS];

	int i = 0;
	srand(time(NULL));
	// generate random numbers and fill them to the list
	for(i = 0; i < MAX_ELEMENTS; i++ ){
		list[i] = rand()%100;
	}

	printf("The list before sorting is:\n");
	printlist(list,MAX_ELEMENTS);

	// sort the list using insertion sort
	radix_sort(list, MAX_ELEMENTS);  
	check_order(list, MAX_ELEMENTS);

	// print the result
	printf("The list after sorting using radix sort algorithm:\n");
	printlist(list,MAX_ELEMENTS);

	return 0;
}
