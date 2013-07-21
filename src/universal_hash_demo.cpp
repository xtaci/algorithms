/*******************************************
 * DANIEL'S PRIVATE ALGORITHM IMPLEMENTAIONS
 * Universal Hashing 
 * Features:
 * 1. randomized hash function, random a1,a2.. a32
 * 2. alloc your storage larger than UHash->prime 
 * 3. the collsion expectation:
	  E[Cx] = (n - 1 ) / m (n: number of elements, m: bucket size--prime number)
 * 4. this set has m^(r+1) different hash functions.
 *******************************************/
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "universal_hash.h"

using namespace alg;
int main(void)
{
	int MAXELEMENT = 1000;
	struct UHash params;

	srand(time(NULL));
	uhash_init(&params, MAXELEMENT);

	int i;
	for (i = 0; i < MAXELEMENT; i++)
	{
		printf("hashing %d --> %d\n", i, uhash_integer(&params, i));
	}

	printf("prime %d\n", params.prime);
}
