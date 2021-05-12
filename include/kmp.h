/*******************************************************************************
 * ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * KNUTH-MORRIS-PRATT ALGORITHMS
 *
 * Features:
 * Complexity is O(n + k), where n is the target string length, 
 * and k is the pattern length
 *
 * http://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
 *
 ******************************************************************************/

#ifndef ALGO_KMP_H__
#define ALGO_KMP_H__
#include <string.h>

namespace alg {
	static void kmp_table(const char *W, int * T, int len);
	/**
	 * S -> the text to be searched
	 * W -> the word to search 
	 * return the position where W is found S
	 */
	static int kmp_search(const char * S, const char * W) {
		int LEN_S = strlen(S);
		int LEN_W = strlen(W);

		int m = 0;
		int i = 0;
		int T[LEN_W];

		kmp_table(W,T, LEN_W);

		while (m+i < LEN_S) {
			if (W[i] == S[m+i]) {
				if (i == LEN_W -1) {
					return m;
				}
				i++;
			} else {
				m = m+i-T[i];
				if (T[i] > -1) {
					i = T[i];
				} else {
					i = 0;
				}
			}
		}
		return -1;
	}

	/**
	 * build a table for the word to be searched  
	 * eg:
	 * i		0 	1 	2 	3 	4 	5 	6
	 * W[i] 	A 	B 	C 	D 	A 	B 	D
	 * T[i] 	-1 	0 	0 	0 	0 	1 	2
	 */
	static void kmp_table(const char *W, int * T, int len) {
		int pos = 2; // the current position we are computing in T 
		int cnd = 0; // the next character of the current candidate substring
		T[0] = -1;
		T[1] = 0;

		while (pos < len) {
			// first case: the substring continues
			if (W[pos-1] == W[cnd]) {
				cnd++;
				T[pos] = cnd;
				pos++;
			} else if (cnd >0) { // second case: it doesn't, but we can fall back
				cnd = T[cnd];
			} else { // third case: we have run out of candidates.  Note cnd = 0
				T[pos] = 0;
				pos++;
			}
		}
	}
}

#endif //
