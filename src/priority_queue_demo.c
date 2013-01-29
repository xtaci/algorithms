#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "priority_queue.h"

int main(void)
{
	struct PQ * pq = pq_create();

	srand(time(NULL));

	int MAXELEMENT = 20;
	int i;

	for (i=0;i<MAXELEMENT;i++) {
		uint32_t pri = rand()%1000;
		pq_queue(pq, (uintptr_t)i, pri);
		printf("queueing: value:%u-> pri: %d\n", i, pri);
	}

	while(!pq_is_empty(pq)){
		int value = (int)pq_dequeue(pq);
		printf("dequeue: %d\n", value);
	}

	exit(0);
}
