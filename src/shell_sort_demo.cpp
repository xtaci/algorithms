#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>

#include "generic.h"
#include "shell_sort.h"

using namespace alg;

int main()
{
	const int MAX_ELEMENTS = 10;
	int list[MAX_ELEMENTS];

	int i = 0;

	srand(time(NULL));
	// generate random numbers and fill them to the list
	for(i = 0; i < MAX_ELEMENTS; i++ ){
		list[i] = rand()%100;
	}
	printf("The list before sorting is:\n");
	printlist(list,MAX_ELEMENTS);

	// sort the list using shell sort
	shell_sort<int>(&list[0],MAX_ELEMENTS);  

	// print the result
	printf("The list after sorting using shell sort algorithm:\n");
	printlist(list,MAX_ELEMENTS);
	return 0;
}
