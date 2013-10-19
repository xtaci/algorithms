#include <stdio.h>
#include "btree.h"

using namespace alg;
int main(void) {
	BTree x("./btree.dat");
	int32_t i;

	for (i=0;i<100000;i++) {
		x.Insert(i);	
		BTree::nr r = x.Search(i);
		printf("offset[%x] idx[%d]\n", r.offset, r.idx);
	}
}
