#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heap.h"

int main()
{	
	using namespace alg;
	int MAXELEMENTS=10;
	Heap<int> heap(MAXELEMENTS);

	int i;
	srand(time(NULL));
	for (i=0;i < MAXELEMENTS; i++) {
		heap.push(100-i, i);
		printf("push: key:%d->value:%d\n", 100-i, i);
	}
	heap.print_heap();

	for (i=0;i<MAXELEMENTS/2;i++) {
		heap.remove(i);
		printf("remove value:%d\n", i);
	}
	heap.print_heap();

	while(!heap.is_empty()) {
		Heap<int>::elem e = heap.pop();
		printf("pop: key:%d->value:%d\n", e.key, e.data);
	}
	heap.print_heap();

	return 0;
}
