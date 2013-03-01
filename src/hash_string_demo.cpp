#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_string.h"
using namespace alg;
int main(void)
{
	const char * strs[] = {
			"first string",
			"second string",
			"third string",
			"this is the fourth string",
			"and finally this is the fifth string"
			};

	int i;
	for (i=0;i<sizeof(strs)/sizeof(char*);i++) {
		printf("hash string: %s --> %u\n", strs[i], hash_string(strs[i], strlen(strs[i])));
	}
	exit(0);
}
