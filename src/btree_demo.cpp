#include <stdio.h>
#include "btree.h"

using namespace alg;
int main(void) {
	BTree x("./btree.dat");
	int32_t i;

	for (i=0;i<510;i++) {
		x.Insert(i);	
	}

	for(i=0;i<509;i++) {
		BTree::search_r r = x.Search(i);
		printf("block[%x] idx[%d]\n", r.n, r.i);
	}
}
