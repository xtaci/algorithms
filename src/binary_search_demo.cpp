#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <iostream>

#include "generic.h"
#include "binary_search.h"
#include "insertion_sort.h"

int main()
{
	RANDOM_INIT();
	using namespace alg;
	const int MAX_ELEMENTS = 10;
	int list[MAX_ELEMENTS];

	int i = 0;
	srand(time(NULL));
	// generate random numbers and fill them to the list
	for(i = 0; i < MAX_ELEMENTS; i++ ){
		list[i] = rand()%100;
	}
	// sort the list using insertion_sort
	insertion_sort(list, MAX_ELEMENTS);

	printf("The list is:\n");
	printlist(list,MAX_ELEMENTS);

	// wait for user input
	int input;

	while(true){
		printf("Type your target: ");
		std::cin >> input;
		printf("The postion of target is: %d\n", binary_search(list, 0, MAX_ELEMENTS - 1, input));
		printf("Press Ctrl + C to STOP\n");
	}
	
	return 0;
}