#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_string.h"
using namespace alg;
int main(void)
{
	const char * strs[] = {
			"",
			"a",
			"foobar",
			"first string",
			"second string",
			"third string",
			"this is the fourth string",
			"and finally this is the fifth string"
			};

	printf("using java hash\n");
	for (uint32_t i=0;i<sizeof(strs)/sizeof(char*);i++) {
		printf("java hash: %s --> %x\n", strs[i], hash_string(strs[i], strlen(strs[i])));
	}
	
	printf("using FNV hash\n");
	for (uint32_t i=0;i<sizeof(strs)/sizeof(char*);i++) {
		printf("fnv hash: %s --> %x\n", strs[i], hash_fnv1a(strs[i], strlen(strs[i])));
	}

	return 0;
}
