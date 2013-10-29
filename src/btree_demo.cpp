#include <stdio.h>
#include "btree.h"

using namespace alg;
int main(void) {
	BTree x("./btree.dat");
	int32_t i;

	for (i=0;i<1000;i++) {
		x.Insert(i);	
		printf("insert %d\n", i);
		BTree::Res r = x.Search(i);
		if (r.idx == -1) {
			printf("key[%d] insert failed\n", i);
		}
	}
	
	for (i=0;i<1000;i++) {
		x.DeleteKey(i);
		BTree::Res r = x.Search(i);
		if (r.idx == -1) {
			printf("key[%d] removed\n", i);
		}
	}
}
