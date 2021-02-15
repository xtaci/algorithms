#include "segment_tree.h"
#include <cstdio>

int values[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

/*
 * Subscripts of segment tree starts from 1 and ends at size().
 * When passing an array to build(), its first argument (*array) will be ignored.
 */
int main() {
	alg::SegmentTree seg(values - 1, 10);
	printf("total value in [1, 10]: %d\n", seg.query(1, 10));
	//adds 5 to every element in [1, 7]
	seg.add(1, 7, 5);
	printf("total value in [2, 9]: %d\n", seg.query(2, 9));
	//multiplies 3 to every element in [2, 6]
	seg.multiply(2, 6, 3);
	printf("total value in [3, 8]: %d\n", seg.query(3, 8));
	return 0;
}
