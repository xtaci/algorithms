#include <stdio.h>
#include <stdlib.h>
#include "fib-heap.h"

int main(void) {
	alg::FibHeap<int32_t, int32_t> heap;
	int32_t i; 
	for (i=0;i<100;i++) {
		heap.Insert(rand(), i);
	}

	for (i=0;i<100;i++) {
		alg::FibHeap<int32_t, int32_t>::Node n;
		n = heap.ExtractMin();
	}
}
