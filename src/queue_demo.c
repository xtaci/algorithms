#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue.h"

int main()
{
	const int MAXELEMENT = 20;
	Queue *Q = create_queue(MAXELEMENT);
	int i;

	for (i=0;i<MAXELEMENT;i++) {
		int value = rand()%1000;
		printf("queuing %d\n", value);
		enqueue(Q,(uintptr_t)value);
	}

	printf("> DEQUEUE\n");
	while(!queue_is_empty(Q)) {
		int rval = (int)queue_front(Q);
		printf("dequeue %d\n",rval);
		dequeue(Q);
	}

	exit(0);
}
