#include <stdio.h>
#include <stdlib.h>
#include "bitset.h"

using namespace alg;
int main(void)
{
	int MAXELEMENT = 100;	

	BitSet bs(MAXELEMENT);	

	int i;
	printf("\nsetting bits: \n");
	for (i=0;i < MAXELEMENT;i++) {
		int v = rand()%2;
		if (v==0) {
			bs.set(i);
			printf("1");
		}
		else printf("0");
	}

	printf("\ntesting bits: \n");
	for (i=0;i< MAXELEMENT;i++) {
		printf("%d", bs.test(i)?1:0);
	}
	printf("\nunsetting bits: \n");
	for (i=0;i< MAXELEMENT;i++) {
		int v = rand()%5;
		if (v==0) {
			bs.unset(i);
			printf("0");
		}
		else printf("1");
	}
	
	printf("\ntesting bits: \n");
	for (i=0;i< MAXELEMENT;i++) {
		printf("%d", bs.test(i)?1:0);
	}
	printf("\n");

	return 0;
}
