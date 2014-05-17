/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * PALINDROMES
 *
 * WORDS LIKE:
 * 	RACECAR	DEED	LEVEL	PIP
 * 	ROTOR	CIVIC	POP		MADAM
 * 	EYE		NUN		RADAR	TOOT
 * 
 * This program will find the longest part of mirror.
 *
 * http://en.wikipedia.org/wiki/Palindrome
 ******************************************************************************/

#ifndef _PALINDROME_H_
#define _PALINDROME_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace alg {
	static void palindrome(const char * S) {
		char *R= strdup(S);
		int len = strlen(S);
		// reverse
		for(int i=0;i<len;i++) {
			R[len-i-1] = S[i];
		}

		int middle = 0;
		int maxlen = 0;
		for(int i=0;i<len;i++) {
			// compare S[0:i] with R[0:length-i-1] in reverse order
			int offset = 0;
			int curlen = 0;

			// try odd
			while (i-offset>= 0 && len-i-1-offset >= 0) {
				if (S[i-offset] == R[len-i-1-offset]) {
					curlen++;
				} else {
					break;
				}
				offset++;
			}

			if (curlen > maxlen) {
				maxlen = curlen;
				middle = i;
			}

			// try even
			while (i-offset>= 0 && len-i-2-offset >= 0) {
				if (S[i-offset] == R[len-i-2-offset]) {
					curlen++;
				} else {
					break;
				}
				offset++;
			}

			if (curlen > maxlen) {
				maxlen = curlen;
				middle = i;
			}
		}

		printf("str:%s len:%d middle:%d\n",S, maxlen, middle);
		free(R);
	}
}

#endif //
