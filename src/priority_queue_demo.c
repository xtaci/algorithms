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

	printf("count# %d\n", pq_count(pq));
	while(!pq_is_empty(pq)){
		uint32_t pri;
		int value = (int)pq_dequeue(pq, &pri);
		printf("dequeue: %d --> pri: %d\n", value, pri);
	}
	printf("count# %d\n", pq_count(pq));
	pq_destroy(pq);
	exit(0);
}
