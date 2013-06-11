/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * PRIME TEST FUNCTION
 *
 * http://en.wikipedia.org/wiki/Primality_test
 * http://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
 *
 ******************************************************************************/
#ifndef __PRIME_H__
#define __PRIME_H__

#include <stdlib.h>
#include <math.h>
#include "imath.h"

namespace alg
{
	/**
	 * check whether a given number is a prime number.
	 * using naive method.
	 */
	static bool test_prime(unsigned int n)
	{
		if (n <=1) {
			return false;
		}

		if (n==2) {
			return true;
		}

		unsigned sqrtn = sqrt(n);
 		for (unsigned int i = 2; i <= sqrtn; ++i) {
        	if (n % i == 0) {
            	return false;
			}
		}
		return true;
	}

	/**
	 * http://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test 
	 */
	static bool miller_rabin_test(unsigned int n) {
		switch (n) {
		case 0:
		case 1:
			return false;
		}
	
		unsigned s = ZerosR(n-1);
		unsigned d = (n-1) >> s;

		// test 3-times
		for (int k=0;k<3;k++){
			unsigned a = rand()%(n-1) + 1;
		
			unsigned x = Exp(a, d, n);
			if (x == 1 || x == n - 1) {
				continue;
			}

			for (unsigned i=0;i<s;i++) {
				x = Exp(x, 2, n);
				if (x == 1) return false;
				if (x == n-1) break;
			}
		}

		return true;
	}
	
	/**
	 * mixed implementation
	 */
	static bool is_prime(unsigned int n) {
		if (miller_rabin_test(n)) {
			return test_prime(n);
		}
		return false;
	}
}

#endif //
