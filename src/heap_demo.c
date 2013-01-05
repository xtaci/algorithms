#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heap.h"

int main()
{	
	int MAXELEMENTS=100;
	struct Heap * heap = heap_init(MAXELEMENTS);
	
	int i;
	srand(time(NULL));
	for (i=0;i < MAXELEMENTS; i++) {
		int element = rand()%1000;
		heap_insert(heap, element);

		printf("inserting: %d\n", element);
	}

	for (i=0;i < MAXELEMENTS; i++) {
		printf("deleting min: %d\n", heap_delete_min(heap));
	}

	return 0;
}
