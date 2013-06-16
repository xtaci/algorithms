#include <stdio.h>
#include "random.h"

int main(void) {
	printf("generate random numbers\n");
	for (int i=0;i<100;i++) {
		printf("%u\n",alg::LCG());
	}
}
