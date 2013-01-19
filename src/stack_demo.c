#include <stdio.h>
#include "stack.h"

int main()
{
	Stack * S = create_stack(4);
	push(S,(void *)7);
	push(S,(void *)5);
	push(S,(void *)-1);
	printf("push return value when has capacity: %d\n",push(S,(void *)9));
	printf("push return value when full: %d\n",push(S,(void *)10));
	int i;
	for (i=0; i< S->size;i++) {
		printf("element %d, %d\n",i, (int)S->elements[i]);
	}
	int rval;
	rval=(int)top(S);pop(S);
	printf("Top element is %d\n",rval);
	rval=(int)top(S);pop(S);
	printf("Top element is %d\n",rval);
	rval=(int)top(S);pop(S);
	printf("Top element is %d\n",rval);
	rval=(int)top(S);pop(S);
	printf("Top element is %d\n",rval);
	destroyStack(S);
	exit(0);
}
