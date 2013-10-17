#include <stdio.h>
#include "btree.h"

using namespace alg;
int main(void) {
	BTree x("./btree.dat");
	int32_t i;

	for (i=0;i<1024;i++) {
		x.Insert(i);
	}

	for(i=0;i<1024;i++) {
		int32_t r = x.Search(i);
		printf("idx[%d]\n", r);
	}
}
