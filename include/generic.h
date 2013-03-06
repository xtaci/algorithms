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


#define Max(a, b) ( (a > b) ? a : b )
#define Min(a, b) ( (a < b) ? a : b )

namespace alg 
{
	/**
	 * swap 2-element, orignal value 
	 */
	template<typename T>
	static inline void swap(T &x, T &y)
	{
		T _t(x);
		x = y;
		y = _t;
	}

	/**
	 * print all of the elements in `list` with size `n`
	 */
	template<typename T>
	static void printlist(T & list,int count)
	{
		int i;
		for(i=0;i<count;i++)
			printf("%d\t ",list[i]);
		printf("\n");
	}

	/**
	 * select a random number between i and j
	 */
	static inline int choose_pivot(int i,int j)
	{
		assert(j>=i);
		typeof(i) length = j - i;
		return i+(rand()%length);
	}

	/**
	 * pass in array with *len
	 * return new length
	 */
	template<typename T>
	static uint32_t remove_dup(T a[], uint32_t len) 
	{
		uint32_t i;
		uint32_t newlen = len;
		for (i=0; i<newlen; i++) {
			T key = a[i];
			uint32_t j;
			for (j=i+1;j<newlen;j++) {
				if(key == a[j]) {
					/* found dup, move left one position. */ 
					uint32_t k;
					for (k=j;k<newlen-1;k++) {
						a[k] = a[k+1];
					}
					newlen--;
				}
			}
		}

		return newlen;
	}
}

#endif //
