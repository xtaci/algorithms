#include <stdio.h>
#include <prime.h>
#include <time.h>

using namespace alg;
int main()
{
	unsigned i;
	int count = 0;
	time_t t1 = time(NULL);
	for (i = 1000000000; i<1000100000; i++) {
		if (is_prime(i)) count++;
	}

	time_t t2 = time(NULL);
	printf("found %d primes, cost %ld secs\n", count, t2-t1);
	return 0;
}
