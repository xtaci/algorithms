/*******************************************
 * DANIEL'S PRIVATE ALGORITHM IMPLEMENTAIONS
 * Universal Hashing 
 * Features:
 * 1. randomized hash function, random a1,a2.. a32
 * 2. alloc your storage larger than uhash_params->prime 
 * 3. the collsion expectation:
	  E[Cx] = (n - 1 ) / m (n: number of elements, m: bucket size--prime number)
 * 4. this set has m^(r+1) different hash functions.
 *******************************************/
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "universal_hash.h"

int main(void)
{
	int MAXELEMENT = 7;
	struct uhash_params params;
	uhash_init(&params, MAXELEMENT);

	srand(time(NULL));
	int i;
	for (i = 0; i < MAXELEMENT; i++)
	{
		int key = rand()%100;
		
		printf("hashing %d --> %d\n", key, uhash_integer(&params, key));
	}

	exit(0);
}
