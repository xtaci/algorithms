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
inline int choose_pivot(int i,int j)
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

/**
 * Read from the string encoded in GB18030 into WORD
 * return the length of the WORD
 */
inline short gb18030_read(char * str, int start, uint32_t * WORD)
{
	unsigned char * w = (unsigned char *)&str[start];

	if (w[0] <= 0x7F) {	// 1-byte
		*WORD = w[0];
		return 1;
	} else if (w[0] >= 0x81 && w[0] <=0xFE) {
		if (w[1] >=0x40 && w[1] <=0xFE) {	// 2-byte
			*WORD = (w[0] << 8) | w[1];
			return 2;
		} else {	// 4-byte
			*WORD = (w[0]<<24)|(w[1]<< 16)|(w[2]<<8)|w[3];
			return 4;
		}
	}
	return 0;
}

/**
 * print a gb18030 char
 */
inline void gb18030_putchar(uint32_t WORD)
{
	unsigned char w0 = (WORD&0xFF000000)>>24;
	unsigned char w1 = (WORD&0xFF0000)>>16;
	unsigned char w2 = (WORD&0xFF00)>>8;
	unsigned char w3 = WORD&0xFF;
	
	if (w0) {
		putchar(w0);putchar(w1);putchar(w2);putchar(w3);		
	} else if (w2) {
		putchar(w2);putchar(w3);
	} else {
		putchar(w3);
	}
}

#endif //
