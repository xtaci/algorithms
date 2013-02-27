#include <stdio.h>
#include <stdlib.h>
#include "bitset.h"

int main(void)
{
	int MAXELEMENT = 100;	

	struct BitSet * bs = bitset_create(MAXELEMENT);	

	int i;
	printf("\nsetting bits: \n");
	for (i=0;i < MAXELEMENT;i++) {
		int v = rand()%2;
		if (v==0) {
			bitset_set(bs, i);
			printf("1");
		}
		else printf("0");
	}

	printf("\ntesting bits: \n");
	for (i=0;i< MAXELEMENT;i++) {
		printf("%d", bitset_test(bs,i)?1:0);
	}
	printf("\nunsetting bits: \n");
	for (i=0;i< MAXELEMENT;i++) {
		int v = rand()%5;
		if (v==0) {
			bitset_unset(bs, i);
			printf("0");
		}
		else printf("1");
	}
	
	printf("\ntesting bits: \n");
	for (i=0;i< MAXELEMENT;i++) {
		printf("%d", bitset_test(bs,i)?1:0);
	}
	printf("\n");

	bitset_destroy(bs);

	exit(0);
}
