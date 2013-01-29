#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "hash_table.h"

int main()
{
	const int MAX_ELEMENTS = 50;
	srand(time(NULL));
	
	struct HashTable * ht = hash_table_create(MAX_ELEMENTS);

	printf("Hash Table Demo: \n");
	int i;
	for(i = 0; i < MAX_ELEMENTS; i++ ){
		int32_t value = rand()%1000;
		hash_table_set(ht, i, (uintptr_t)value);

		printf("setting %d->%d\n", i, value);
	}
	
	for(i = 0; i < MAX_ELEMENTS; i++ ){
		int32_t value = (int32_t)hash_table_get(ht, i);
		printf("getting %d->%d\n", i, value);
	}

	hash_table_destroy(ht);

	exit(0);
}
