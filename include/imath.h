#ifndef __IMATH_H__
#define __IMATH_H__

#include <stdint.h>
#include <string.h>

/**
 * dot product of given arrays K and A of len, saved in SUM
 */
#define dot_product(k,a,len,SUM) \
do { \
	int32_t __dot_product_incr; \
	SUM = 0; \
	for (__dot_product_incr=0; __dot_product_incr<len;__dot_product_incr++) { \
		SUM += k[__dot_product_incr]*a[__dot_product_incr]; \
	} \
} while(0)

/**
 * divide key into m-based integer array
 * m -- must be a prime number larger than 2
 * k -- must be size of KLEN * sizeof(uint32_t)
 */
#define KLEN 32
inline void m_based(uint64_t key, int m, uint32_t k[]) 
{
	memset(k,0,sizeof(uint32_t) * KLEN);

	int quotient;
	int i = KLEN-1;
	while((quotient = key/m)!=0)
	{
		k[i] = key%m;
		key/=m;
		i--;
	}
	k[i] = key;
}

#endif //
