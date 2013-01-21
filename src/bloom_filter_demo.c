#include <stdio.h>
#include <stdlib.h>
#include "bloom_filter.h"

int main(void)
{
	const char * strs[] = {
			"purple_lover_04@msn.com",
			"hollie.smith@yahoo.com",
			"hollister.susan @gmail.com",
			"alexptre@gmail.com",
			"cfo@sjtu-edp.cn",
			"abms@n23h22.rev.sprintdatacenter.pl"
			};

	const char * strs2[] = {
			"admin@facebook.com",
			"xtaci@163.com"
			};

	int len = sizeof(strs)/sizeof(char*);
	struct BloomFilter * bf = bloom_filter_create(8, len*10, len);
	int i;
	for (i=0;i<len;i++) {
		bloom_filter_set(bf, strs[i], strlen(strs[i]));
	}

	for (i=0;i<len;i++) {
		printf("checking %s->%s\n", strs[i], bloom_filter_test(bf, strs[i], strlen(strs[i]))?"true":"false");
	}

	for (i=0;i<sizeof(strs2)/sizeof(char*);i++) {
		printf("checking %s->%s\n", strs2[i], bloom_filter_test(bf, strs2[i], strlen(strs2[i]))?"true":"false");
	}

	exit(0);

}
