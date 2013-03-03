#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "priority_queue.h"

int main(void)
{
	using namespace alg;
	PQ<int> pq;

	srand(time(NULL));

	int MAXELEMENT = 20;
	int i;

	for (i=0;i<MAXELEMENT;i++) {
		int pri = rand()%1000;
		pq.queue(i, pri);
		printf("queueing: value:%u-> pri: %d\n", i, pri);
	}

	printf("count# %d\n", pq.count());
	while(!pq.is_empty()){
		int pri;
		int value = pq.top(&pri);
		printf("dequeue: %d --> pri: %d\n", value, pri);
		pq.dequeue();
	}
	printf("count# %d\n", pq.count());
	return 0;
}
