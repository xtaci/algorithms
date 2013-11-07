#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heap.h"

int main()
{	
	using namespace alg;
	int MAXELEMENTS=50;
	Heap<int> heap(MAXELEMENTS);

	int32_t i;
	srand(time(NULL));
	for (i=0;i < MAXELEMENTS; i++) {
		int value = rand()%1000;
		heap.insert(i, value);
		printf("inserting: %d->%d\n", 100-i, value);
	}

	int index = 20;
	printf("decrease a key[%d] to %d\n", index, -1);
	heap.decrease_key(index, -1);
	while(!heap.is_empty()) {
		printf("deleting min: %d->%d\n", heap.min_key(), heap.min_value());
		heap.delete_min();
	}

	return 0;
}
