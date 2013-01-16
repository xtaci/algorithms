/*******************************************
 * DANIEL'S PRIVATE ALGORITHM IMPLEMENTAIONS
 * Perfect Hashing 
 * Features:
 * 1. based on Universal Hashing
 * 2. O(1) query
 * 3. Some applications naturally have !!!STATIC SETS OF KEYS!!!:
	  consider the set of reserved words in a programming language,
	  or the set of file names on a CD-ROM. We call a hashing technique perfect
      hashingif the worst-case number of memory accesses required 
	  to perform a search is O(1).
 *******************************************/

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "generic.h"
#include "perfect_hash.h"

int main(void)
{
	int MAXELEMENT = 100;

	uint32_t keys[MAXELEMENT];
	uint32_t values[MAXELEMENT];

	srand(time(NULL));	
	int i;
	for (i = 0; i < MAXELEMENT; i++) {
		keys[i] = rand()%1000;
		values[i] = rand()%10000;
	}

	struct PerfHT * ht = perfect_hash_init(keys, MAXELEMENT);	

	for (i = 0; i < MAXELEMENT; i++) {
		printf("set %d --> %d\n", keys[i],values[i]);
		perfect_hash_set(ht, keys[i], (void*)values[i]);
	}
	
	for (i = 0; i < MAXELEMENT; i++) {
		uint32_t value = (uint32_t)perfect_hash_get(ht, keys[i]);
		printf("get %d <-- %d\n", keys[i], value);
	}

	perfect_hash_destroy(ht);

	exit(0);
}
