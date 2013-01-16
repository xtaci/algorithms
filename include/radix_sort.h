/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * RADIX SORT 
 *
 * Features: 
 *  1. sort unsigned 32-bit array in O(n) time
 *  2. subset sorted with couting sort.
 *
 * http://en.wikipedia.org/wiki/Radix_sort
 *
 ******************************************************************************/

#ifndef __RADIX_SORT_H__
#define __RADIX_SORT_H__

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <generic.h>

/**
 * couting sort
 */
inline static void radix(int byte, const unsigned N, const uint32_t *source, uint32_t *dest)
{
	unsigned count[256];
	unsigned index[256];
	memset(count, 0, sizeof (count));

	unsigned i;
	for(i=0; i<N; ++i)
		count[((source[i])>>(byte*8))&0xff]++;

	index[0]=0;
	for(i=1; i<256; ++i)
		index[i] = index[i-1] + count[i-1];

	for(i=0; i<N; ++i)
		dest[index[((source[i])>>(byte*8))&0xff]++] = source[i];
}

/**
 * radix sort a given unsigned 32-bit integer array of size N
 */
inline void radixsort(uint32_t *source, const unsigned N)
{
	uint32_t *temp = (uint32_t *)malloc(sizeof(uint32_t)*N);
	radix(0, N, source, temp);
	radix(1, N, temp, source);
	radix(2, N, source, temp);
	radix(3, N, temp, source);
	free(temp);
}

/**
 * check whether the array is in order
 */
inline static void check_order(const uint32_t *data, unsigned N)
{
	for(--N ; N > 0; --N, ++data)
		assert(data[0] <= data[1]);
}

#endif //
