/*****************************************
 * DANIEL'S PRIVATE ALGORITHM IMPLEMENTAIONS
 * Fisher Yates's shuffle algorithm
 * Features:
 * 1. shuffle list in O(n) time.
 *******************************************/

#ifndef __SHUFFLE_H__
#define __SHUFFLE_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * shuffle the 'list' of length 'len'
 */
inline void shuffle(int * list, int len)
{
	srand(time(NULL));
	int i = len, j;
	int temp;

	if ( i == 0 ) return;
	while ( --i ) {
		j = rand() % (i+1);
		temp = list[i];
		list[i] = list[j];
		list[j] = temp;
	}
}

#endif //
