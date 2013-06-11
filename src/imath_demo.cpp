#include <stdio.h>

#include "imath.h"

int main() {
	for (int i=10000;i<10100;i++) {
		for (int j=100000;j<100010;j++) {
			printf("%d^%d mod %d = %d\n", i,j,997, alg::Exp(i, j, 997));
		}
	}

	unsigned int n = 104;
	printf("%x has %d zeros on the right side\n", n, alg::ZerosR(n));
}
