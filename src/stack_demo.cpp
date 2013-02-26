#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main()
{
	Stack<int> &S = *new Stack<int>(4);
	S.push(7);
	S.push(5);
	S.push(-1);

	printf("push return value when has capacity: %d\n",S.push(9));
	printf("push return value when full: %d\n",S.push(10));
	int i;
	for (i=0; i< S.count();i++) {
		printf("element %d, %d\n",i, S[i]);
	}
	
	while(!S.is_empty()) {
		printf("poping: %d\n", S.top());
		S.pop();
	}
	exit(0);
}
