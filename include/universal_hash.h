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

#ifndef ALGO_UNIVERSAL_HASH_H__
#define ALGO_UNIVERSAL_HASH_H__

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

namespace alg {
	struct UHash {
		uint32_t a[KLEN];
		uint32_t prime;	
	};

	/**
	 * init an universal hash struct
	 */
	static inline void uhash_init(struct UHash * params, uint32_t max_element) {
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
	static inline uint32_t uhash_integer(const struct UHash * params, uint64_t key) {
		uint32_t k[KLEN];
		uint32_t sum;

		m_based(key, params->prime, k);
		sum = dot_product(k,params->a,KLEN);
		return sum%params->prime;
	}

	/**
	 * hash an arbitrary length integer.
	 * len, number of 32-bit integer, max len is 32
	 */
	static uint32_t uhash_bigint(const struct UHash * params, uint32_t * key, uint32_t len) {
		// TODO : need a better algorithm, or NOT?
		return key[0]%params->prime;
	}
}
#endif //
