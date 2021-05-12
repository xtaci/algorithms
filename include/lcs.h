/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * LARGEST COMMON SEQUENCE
 *
 * http://en.wikipedia.org/wiki/Longest_common_subsequence_problem
 *
 ******************************************************************************/

#ifndef ALGO_LCS_H__
#define ALGO_LCS_H__

#include "generic.h"
#include "2darray.h"
#include "stack.h"

namespace alg {
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
	template<typename T>
		static Array2D<uint32_t> * lcs_length(const T X[], uint32_t m, const T Y[], uint32_t n) {
			Array2D<uint32_t> & A = *new Array2D<uint32_t>(m+1,n+1);

			uint32_t i,j;

			// set initial state
			for(i=0; i<=m; i++) {
				A(i,0) = 0; 
			}

			for(j=0; j<=n; j++) {
				A(0,j) = 0;
			}

			for(i=1;i<=m;i++) {
				for(j=1;j<=n;j++) {
					if(X[i-1]==Y[j-1]) A(i,j) = A(i-1,j-1) + 1;
					else A(i,j) = Max(A(i,j-1), A(i-1,j));
				}
			}

			return &A;
		};

	/**
	 * pass an empty stack, pop out the result in sequential order. 
	 */
	template<typename T>
		static void lcs_backtrack(Stack<int> & S, Array2D<uint32_t> & A,
				const T X[], const T Y[], 
				const uint32_t i, uint32_t j) {
			if (i==0 || j==0) return;
			else if (X[i-1] == Y[j-1]) { 
				S.push(X[i-1]);
				lcs_backtrack(S, A, X, Y, i-1, j-1);
			}
			else {
				if (A(i, j-1) > A(i-1, j))
					lcs_backtrack(S, A, X, Y, i, j-1);
				else
					lcs_backtrack(S, A, X, Y, i-1, j);
			}
		}
}

#endif //
