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
 
#ifndef __IMATH_H__
#define __IMATH_H__

#include <stdint.h>
#include <string.h>

namespace alg
{
	/**
	 * dot product of given arrays K and A of len, saved in SUM
	 */
	static uint32_t dot_product(const uint32_t * K, const uint32_t * A, uint32_t len)
	{ 
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
	static void m_based(uint64_t key, int m, uint32_t k[]) 
	{
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
}

#endif //
