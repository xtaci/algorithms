#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "hash_table.h"
using namespace alg;
int main()
{
	const int MAX_ELEMENTS = 50;
	srand(time(NULL));
	
	HashTable<uint32_t, uint32_t> ht(MAX_ELEMENTS);

	printf("Hash Table Demo: \n");
	int i;
	for(i = 0; i < MAX_ELEMENTS; i++ ){
		int32_t value = rand()%1000;
		ht[i] = value;
		printf("setting %d->%d\n", i, value);
	}
	
	for(i = 0; i < MAX_ELEMENTS; i++ ){
		printf("getting %d->%d\n", i, ht[i]);
	}

	for(i = 0; i < MAX_ELEMENTS; i++ ){
		printf("deleting %d\n", ht.delete_key(i));
	}

	for(i = 0; i < MAX_ELEMENTS; i++ ){
		printf("testing %d->%s\n", i, ht.contains(i)?"true":"false");
	}

	return 0;
}
