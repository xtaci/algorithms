#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fib-heap.h"

int main(void) {
	srand(time(NULL));
	alg::FibHeap<int32_t, int32_t> heap;
	int32_t i; 
	for (i=0;i<10;i++) {
		heap.Insert(rand(), i);
	}

	for (i=0;i<10;i++) {
		alg::FibHeap<int32_t, int32_t>::Node n;
		n = heap.ExtractMin();
		if (n!= NULL) {
			printf("%d %d\n", n->key, n->value);
		}
	}
}
