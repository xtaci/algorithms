/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * COMMON MATH OPS
 *
 ******************************************************************************/

#ifndef ALGO_IMATH_H__
#define ALGO_IMATH_H__

#include <stdint.h>
#include <string.h>
#include <limits.h>

namespace alg {
	/**
	 * dot product of given arrays K and A of len, saved in SUM
	 */
	static uint32_t dot_product(const uint32_t * K, const uint32_t * A, uint32_t len) { 
		uint32_t i; 
		uint32_t sum = 0; 
		for (i=0; i<len;i++) {
			sum += K[i]*A[i];
		}

		return sum;
	}

	/**
	 * divide key into m-based integer array
	 * m -- must be a prime number larger than 2(3 least)
	 * k -- must be size of KLEN * sizeof(uint32_t)
	 */
#define KLEN 64
	static void m_based(uint64_t key, int m, uint32_t k[]) {
		memset(k,0,sizeof(uint32_t) * KLEN);

		int quotient;
		int i = 0;
		while((quotient = key/m)!=0)
		{
			k[i] = key%m;
			key = quotient;
			i++;
		}
		k[i] = key;
	}

	/**
	 * based on Applied Cryptography by Bruce Schneier.[1] 
	 * http://en.wikipedia.org/wiki/Modular_exponentiation
	 */
	static unsigned Exp(unsigned base, unsigned exponent, unsigned modulus) {
		unsigned result = 1;
		while (exponent >0) {
			if (exponent%2 == 1) {
				result = (uint64_t(result)*base)%modulus;
			}
			exponent = exponent >> 1 ;
			base = (uint64_t(base)*base) % modulus;
		}
		return result;
	}

	/**
	 * Count the consecutive zero bits (trailing) on the right linearly
	 */
	static inline int ZerosR(unsigned int v) {
		int c;  // output: c will count v's trailing zero bits,
		// so if v is 1101000 (base 2), then c will be 3
		if (v)
		{
			v = (v ^ (v - 1)) >> 1;  // Set v's trailing 0s to 1s and zero rest
			for (c = 0; v; c++) {
				v >>= 1;
			}
		}
		else
		{
			c = CHAR_BIT * sizeof(v);
		}

		return c;
	}
}

#endif //
