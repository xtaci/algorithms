#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include "generic.h"
#include "bubble_sort.h"



using namespace alg;
int main (int argc, char const *argv[])
{
	const int MAX_ELEMENTS = 10;
	int list[MAX_ELEMENTS];
	for(int i = 0; i < MAX_ELEMENTS; i++ ){
		list[i] = rand()%100;
	}
	printf("The list before sorting is:\n");
	printlist(list,MAX_ELEMENTS);

	// sort the list using quicksort
	aglo::BubbleSort(list,0,MAX_ELEMENTS-1);

	// print the result
	printf("The list after sorting using quicksort algorithm:\n");
	printlist(list,MAX_ELEMENTS);
	
	return 0;
}