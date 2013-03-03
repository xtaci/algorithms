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

#include "sha1.h"

#include "universal_hash.h"
#define TEST "this is a string"

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
		int key = rand()%100;
		
		printf("hashing %d --> %d\n", key, uhash_integer(&params, key));
	}

	SHA1Context sha;

	sha1_reset(&sha);
	sha1_input(&sha, (const unsigned char *) TEST, strlen(TEST));

	if (sha1_final(&sha))
    {
		int i;
        for(i = 0; i < 5 ; i++)
        {
            printf("%x", sha.digest[i]);
        }
	}
	
	printf("\n -- hashing big int into %d\n", uhash_bigint(&params, sha.digest,5)); 

	return 0;
}
