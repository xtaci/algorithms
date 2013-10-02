#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue.h"

int main()
{
	using alg::Queue;
	const int MAXELEMENT = 20;
	Queue<int> Q(MAXELEMENT);
	int i;

	for (i=0;i<MAXELEMENT;i++) {
		int value = rand()%1000;
		printf("queuing %d\n", value);
		Q.enqueue(value);
	}

	printf("queue count:%u\n", Q.count());

	printf("> DEQUEUE\n");
	while(!Q.is_empty()) {
		printf("dequeue %d\n",Q.front());
		Q.dequeue();
	}

	return 0;
}
