#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue.h"

int main()
{
	Queue *Q = createQueue(5);
	Enqueue(Q,1);
	Enqueue(Q,2);
	Enqueue(Q,3);
	Enqueue(Q,4);
	int rval;
	front(Q, &rval);
	printf("Front element is %d\n",rval);
	Enqueue(Q,5);
	Dequeue(Q);
	Enqueue(Q,6);
	front(Q, &rval);
	printf("Front element is %d\n",rval);
	exit(0);
}
