/*******************************************
 * DANIEL'S PRIVATE ALGORITHM IMPLEMENTAIONS
 * Largest Common Sequence
 * Features:
 * 1. Implementation of 
 http://en.wikipedia.org/wiki/Longest_common_subsequence_problem
 *******************************************/

#ifndef __LCS_H__
#define __LCS_H__

#include "generic.h"
#include "2darray.h"
#include "stack.h"

/**
 * calculate Length matrix
 * X -- array of size m
 * Y -- array of size n
 * eg:
			0	1	2	3	4	5	6	7
			Ø	M	Z	J	A	W	X	U
	0	Ø	0	0	0	0	0	0	0	0
	1	X	0	0	0	0	0	0	1	1
	2	M	0	1	1	1	1	1	1	1
	3	J	0	1	1	2	2	2	2	2
	4	Y	0	1	1	2	2	2	2	2
	5	A	0	1	1	2	3	3	3	3
	6	U	0	1	1	2	3	3	3	4
	7	Z	0	1	2	2	3	3	3	4
 */
inline struct Array2D * lcs_length(const int32_t * X, uint32_t m, const int32_t * Y, uint32_t n)
{
	struct Array2D * arr = array2d_create(m+1, n+1);
	uint32_t i,j;

	for(i=0; i<=m; i++) {
		array2d_set(arr, i, 0, 0);
	}
	
	for(j=0; j<=n; j++) {
		array2d_set(arr, 0, j, 0);
	}

	for(i=1;i<=m;i++) {
		for(j=1;j<=n;j++) {
			if(X[i-1]==Y[j-1]) array2d_set(arr,i,j, array2d_get(arr,i-1,j-1)+1);
			else array2d_set(arr,i,j, Max(array2d_get(arr,i,j-1),array2d_get(arr,i-1,j)));
		}
	}
	return arr;
}

/**
 * pass an empty stack,  pop out the result in sequential order. 
 */
inline void lcs_backtrack(Stack * s, struct Array2D * C, const int32_t * X, int32_t * Y, const uint32_t i, uint32_t j)
{
	if (i==0 || j==0) return;
	else if (X[i-1] == Y[j-1]) { 
		push(s, (void *)X[i-1]);
		lcs_backtrack(s, C, X, Y, i-1, j-1);
	}
	else {
		if (array2d_get(C, i, j-1) > array2d_get(C, i-1, j))
			lcs_backtrack(s, C, X, Y, i, j-1);
		else
			lcs_backtrack(s, C, X, Y, i-1, j);
	}
}

#endif //
