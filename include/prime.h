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
#ifndef ALGO_PRIME_H__
#define ALGO_PRIME_H__

#include <stdlib.h>
#include <math.h>
#include "imath.h"

namespace alg {
	/**
	 * check whether a given number is a prime number.
	 * using naive method.
	 */
	static bool test_prime(unsigned int n) {
		switch (n) {
			case 0:
			case 1:
				return false;
			case 2:
				return true;
		}

		if (n%2	== 0) return false;

		unsigned sqrtn = sqrt((double)n);
		for (unsigned int i = 3; i <= sqrtn; i+=2) {
			if (n % i == 0) {
				return false;
			}
		}
		return true;
	}

	/**
	 * http://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test 
	 */
	static inline bool miller_rabin_test(unsigned int n) {
		switch (n) {
			case 0:
			case 1:
				return false;
			case 2:
			case 3:
				return true;
		}

		if (n%2	== 0) return false;

		unsigned s = ZerosR(n-1);
		unsigned d = (n-1) >> s;

		// test 3-times
		for (int k=0;k<3;k++){
			unsigned a = rand()%(n-4) + 2;

			unsigned x = Exp(a, d, n);
			//printf("%u %u %u %u\n", a,d, n,x);
			if (x == 1 || x == n - 1) {
				continue;
			}

			for (unsigned i=1;i<=s-1;i++) {
				x = Exp(x, 2, n);
				if (x == 1) return false;
				if (x == n-1) continue;
			}

			return false;
		}

		return true;
	}

	/**
	 * mixed implementation
	 */
	static inline bool is_prime(unsigned int n) {
		if (miller_rabin_test(n)) {
			return test_prime(n);
		}
		return false;
	}
}

#endif //
