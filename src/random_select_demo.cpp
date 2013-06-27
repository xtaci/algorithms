#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "generic.h"
#include "random_select.h"

int main()
{
	RANDOM_INIT();
	using namespace alg;
	const int MAX_ELEMENTS = 10;
	int list[MAX_ELEMENTS];

	int i = 0;
   
	// generate numbers and fill them to the list
	for(i = 0; i < MAX_ELEMENTS; i++ ){
		list[i] = rand()%100; 
	}
	
	printf("The list is:\n");
	printlist(list,MAX_ELEMENTS);
   
	// random-select k-th element
	srand(time(NULL));
	int k = rand()%MAX_ELEMENTS + 1;
	int result = random_select(list,0,MAX_ELEMENTS-1,k);

	// print the result
	printf("random select the %dth smallest number %d:\n", k, list[result]);

	return 0;
}
