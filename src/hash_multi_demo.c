#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "hash_multi.h"

int main()
{
	const int MAX_ELEMENTS = 50;
	srand(time(NULL));
	
	struct MultiHash * ht =  multi_hash_init(MAX_ELEMENTS);

	printf("required space for storage is %d\n", MULTI_HASH_TABLE_SIZE(ht));

	int i;
	for(i = 0; i < MAX_ELEMENTS; i++ ){
		uint32_t key = rand()%1000;
		printf("hash %d --> %d\n", key, multi_hash_hash(ht, key) );
	}
	
	exit(0);
}
