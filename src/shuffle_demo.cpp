/*******************************************
 * DANIEL'S PRIVATE ALGORITHM IMPLEMENTAIONS
 * Fisher Yates's shuffle algorithm
 * Features:
 * 1. shuffle list in O(n) time.
 *******************************************/

#include <stdio.h>
#include <stdlib.h>

#include "generic.h"
#include "shuffle.h"
using namespace alg;
int main()
{
	const int MAX_ELEMENTS = 10;
	int list[MAX_ELEMENTS];

	int i = 0;

	// generate random numbers and fill them to the list
	for(i = 0; i < MAX_ELEMENTS; i++ ){
		list[i] = i;
	}
	printf("The list before Shuffle is:\n");
	printlist(list,MAX_ELEMENTS);

	// shuffle the list
	shuffle<int>(list,MAX_ELEMENTS);

	// print the result
	printf("The list after using Yates' shuffle algorithm:\n");
	printlist(list,MAX_ELEMENTS);
	return 0;
}

