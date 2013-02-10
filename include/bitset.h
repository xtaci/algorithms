/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * BIT-SET
 *
 * a bit-set data structure
 *
 ******************************************************************************/

#ifndef __BIT_SET_H__
#define __BIT_SET_H__

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

struct BitSet {
	uint32_t size;	//size in bits
	uint32_t bytes;
	unsigned char * bits;
};

/**
 * size -- in bits
 */
static inline struct BitSet * bitset_create(uint32_t size)
{
	struct BitSet * bs = (struct BitSet *)malloc(sizeof(struct BitSet));

	// round up
	bs->bytes = size/8+1;
	bs->size = bs->bytes * 8;
	bs->bits = (unsigned char *)malloc(bs->bytes);
	memset(bs->bits, 0, bs->bytes);
	
	return bs;
}

/**
 * set 1 to position [bit]
 */
static inline void bitset_set(struct BitSet * bs, uint32_t bit)
{
	if (bit>=bs->size) return;

	uint32_t n = bit/8;
	uint32_t off = bit%8;

	bs->bits[n] |= 128U>>off;
}

/**
 * set 0 to position [bit]
 */
static inline void bitset_unset(struct BitSet * bs, uint32_t bit)
{
	if (bit>=bs->size) return;

	uint32_t n = bit/8;
	uint32_t off = bit%8;

	bs->bits[n] &= ~(128U>>off);
}

/**
 * test a bit , true if set, false if not.
 */
static inline bool bitset_test(struct BitSet * bs, uint32_t bit)
{
	if (bit>=bs->size) return false;

	uint32_t n = bit/8;
	uint32_t off = bit%8;

	if (bs->bits[n] & (128U>>off))return true;
	return false;
}

/**
 * safely free
 */
static inline void bitset_destroy(struct BitSet *bs)
{
	if(bs->bits)free(bs->bits);
	free(bs);
}

#endif //
