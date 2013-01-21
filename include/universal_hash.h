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
#include <string.h>

#include <prime.h>
#include <imath.h>
#include <random.h>

struct UHash {
	uint32_t a[KLEN];
	uint32_t prime;	
};

/**
 * init an universal hash struct
 */
inline void uhash_init(struct UHash * params, uint32_t max_element)
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
inline int uhash_integer(const struct UHash * params, uint32_t key)
{
	uint32_t k[KLEN];
	uint32_t sum;
	m_based(key, params->prime, k);
	dot_product(k,params->a,KLEN,sum);
	return sum%params->prime;
}

#endif //
