/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 * 
 * HASH BY MULTIPLICATION
 *
 * Features:
 * 	1. h(k) = (A*k mod 2^w) >> (w-r)
 *  2. bucket size(m): 2^r, eg, m = 8 = 2^3
 *	3. w: word size (usually 32-bit)
 * 	4. the value of A is chosen between 2^(w-r) and 2^w odd number.
 *
 ******************************************************************************/

#ifndef ALGO_HASH_MULTIPLICATION_H__
#define ALGO_HASH_MULTIPLICATION_H__

#include <math.h>
#include <string.h>
#include "generic.h"
#include "prime.h"

namespace alg {
	struct MultiHash {
		uint64_t A;
		uint32_t r; // prime, init your hash table with size -> r
	};

	static const short BITWIDTH = 32;
	static inline uint32_t multi_hash_table_size(const struct MultiHash * ht) { return 1<<(ht->r); } 

	/**
	 * multi_hash.
	 */
	static inline uint32_t multi_hash(const struct MultiHash * ht, uint32_t key) {
		uint32_t hash;
		hash = ((ht->A * key)&0xFFFFFFFF)>>(BITWIDTH-ht->r); //mod 2^w equals logic bitmask ops
		return hash;
	}

#ifdef _MSC_VER
#define log2(x) (log(x) / log(2.0))
#endif

	/**
	 * init a hash table with size specified.
	 */
	static MultiHash * multi_hash_init(uint32_t size) {
		// find prime larger than log2(size)
		uint32_t r = ceil(log2((double)size));
		int i;
		for (i = r; ;i++) {
			if (is_prime(i)) {
				r = i;
				break;
			}
		}

		MultiHash * ht = new MultiHash;
		uint32_t a = 1 << (BITWIDTH-r);
		ht->A = a+1;
		ht->r = r;

		return ht;
	}
}
#endif //
