#include <stdio.h>
#include <stdlib.h>
#include "bloom_filter.h"

int main(void)
{
	using namespace alg;
	const char * strs[] = {
			"purple_lover_04@msn.com",
			"hollie.smith@yahoo.com",
			"hollister.susan @gmail.com",
			"alexptre@gmail.com",
			"cfo@sjtu-edp.cn",
			"abms@n23h22.rev.sprintdatacenter.pl",
			"admin@facebook.com",
			"xtaci@163.com"
			};

	const char * strs2[] = {
			"admin@facebook.com",
			"xtaci@163.com"
			};

	uint32_t len = sizeof(strs)/sizeof(char*);
	BloomFilter<8> bf(len*10, len);

	for (uint32_t i=0;i<len;i++) {
		bf.set(strs[i]);
		printf("adding %s\n", strs[i]);
	}

	for (uint32_t i=0;i<sizeof(strs2)/sizeof(char*);i++) {
		printf("checking %s->%s\n", strs2[i], bf.test(strs2[i])?"true":"false");
	}

	return 0;
}
