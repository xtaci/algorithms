#include <stdio.h>
#include <prime.h>
#include <time.h>

using namespace alg;
int main()
{
	unsigned i;
	int miller = 0;
	time_t t1 = time(NULL);
	int prime;
	for (i = 1000000000; i<1001000000; i++) {
		if (miller_rabin_test(i)) {
			miller++;
			prime=i;
		}
	}

	time_t t2 = time(NULL);
	printf("found %d miller-primes , cost %ld secs\n", miller,t2-t1);
	printf("last prime %d\n", prime);

	int count = 0;
	t1 = time(NULL);
	for (i = 1000000000; i<1001000000; i++) {
		if (test_prime(i)) count++;
	}
	t2 = time(NULL);
	printf("found %d primes using raw_test, cost %ld secs\n", count,t2-t1);

	return 0;
}
