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
		int value = rand()%1000;
		heap_insert(heap, i, (void *)value);

		printf("inserting: %d->%d\n", i, value);
	}

	for (i=0;i < MAXELEMENTS; i++) {
		printf("deleting min: %d->%d\n", HEAP_MIN_KEY(heap), (int)HEAP_MIN_VALUE(heap));
		heap_delete_min(heap);
	}

	return 0;
}
