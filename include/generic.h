/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * GENERIC METHODS FOR ALGORITHMS
 *
 ******************************************************************************/
 
#ifndef __ALG_INC_H__
#define __ALG_INC_H__
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>

#include "utils/gb18030.h"
#include "utils/byteorder.h"

/**
 * print all of the elements in `list` with size `n`
 */
#define printlist(list,n) \
do { \
	int __list_counter; \
	for(__list_counter=0;__list_counter<n;__list_counter++) \
		printf("%d\t ",list[__list_counter]); \
	printf("\n"); \
} while(0)

/**
 * swap 2-element, orignal value 
 */
#define swap(x,y) \
do { \
	typeof(x) _t = x; \
	x = y;	\
	y = _t; 	\
} while(0)

#define Max(a, b) ( (a > b) ? a : b )

/**
 * select a random number between i and j
 */
static inline int 
choose_pivot(int i,int j)
{
	assert(j>=i);
	typeof(i) length = j - i;
	return i+(rand()%length);
}

/**
 * pass in array with *len
 * set newlen
 */
#define remove_dup(a,len, newlen) 	\
do {								\
	int i;							\
	newlen = len;					\
	for (i=0; i<newlen; i++) {		\
		int key = a[i];				\
		int j;						\
		for (j=i+1;j<newlen;j++) {	\
			if(key == a[j]) {		\
				/* found dup, move left one position. */ \
				int k;				\
				for (k=j;k<newlen-1;k++) {	\
					a[k] = a[k+1];			\
				}							\
				newlen--;					\
			}						\
		}							\
	}								\
} while (0)
#endif //
