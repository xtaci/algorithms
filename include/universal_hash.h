/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * UNIVERSAL HASH FUNCTION
 *
 * http://en.wikipedia.org/wiki/Universal_hash
 *
 ******************************************************************************/

#ifndef __UNIVERSAL_HASH_H__
#define __UNIVERSAL_HASH_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "prime.h"
#include "imath.h"
#include "random.h"
#include "integer.h"

struct UHash {
	uint32_t a[KLEN];
	uint32_t prime;	
};

/**
 * init an universal hash struct
 */
static inline void uhash_init(struct UHash * params, uint32_t max_element)
{
	int i;
	// the size of the hash bucket is the prime larger than 2 * max_element
	for(i=max_element+1;;i++) {
		if (is_prime(i)) {
			params->prime = i;
			break;
		}
	}

	for (i = 0; i < KLEN;i++) {
		params->a[i] = rand()%params->prime;
	}
}

/**
 * hash a key
 */
static inline uint32_t uhash_integer(const struct UHash * params, uint64_t key)
{
	uint32_t k[KLEN];
	uint32_t sum;

	m_based(key, params->prime, k);
	dot_product(k,params->a,KLEN,sum);
	return sum%params->prime;
}

/**
 * hash an arbitary length integer.
 * len, number of 32-bit integer, max len is 32
 */
static inline uint32_t uhash_bigint(const struct UHash * params, uint32_t * key, uint32_t len)
{
	assert(len <=32);

	uint32_t k[len*32];
	integer big_sum = create_integer(len);set_zero_integer(big_sum);
	integer big_key = create_integer(len);
	integer tmp = create_integer(1);
	integer quotient = create_integer(len);

	int i;
	for (i=0;i<len;i++) {
		big_key.c[i] = key[i];
	}

	i = 0;
	while(true)
	{
		divide_small_integer(big_key, params->prime, quotient);
		if (is_zero_integer(quotient)) break;
		k[i] = mod_small_integer(big_key, params->prime);
		mod_small_integer(big_key, params->prime);
		copy_integer(quotient, big_key);
		i++;
	}
	k[i] = big_key.c[0];

	// Dot Product
	integer tmp_sum = create_integer(len);
	for (i=0;i<len;i++) {
		tmp.c[0] = k[i] * params->a[i];
		add_integer(big_sum, tmp, tmp_sum);
		copy_integer(tmp_sum, big_sum);
	}

	// Mod Sum	
	uint32_t result = mod_small_integer(big_sum, params->prime);
	free_integer(big_sum);
	free_integer(big_key);
	free_integer(tmp);
	free_integer(tmp_sum);
	free_integer(quotient);
	
	return result;
}
#endif //
