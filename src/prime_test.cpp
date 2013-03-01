#include <stdio.h>
#include <prime.h>

using namespace alg;
int main()
{
	int i;
	for (i = 0; i<100; i++) {
		printf("number: %d, prime %d\n", i, is_prime(i));
	}
	return 0;
}
