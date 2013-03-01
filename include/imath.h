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
	#define dot_product(k,a,len,SUM) \
	do { \
		int32_t incr; \
		SUM = 0; \
		for (incr=0; incr<len;incr++) { \
			SUM += k[incr]*a[incr]; \
		} \
	} while(0)

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
