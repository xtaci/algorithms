/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * RANDOM NUMBER GENERATOR
 *
 * http://en.wikipedia.org/wiki/Pseudorandom_number_generator
 *
 ******************************************************************************/

#ifndef ALGO_RANDOM_H__
#define ALGO_RANDOM_H__

#include <stdio.h>
#include <stdint.h>

namespace alg {
	/**
	 * Linear congruential generator
	 * [0, 4294967295]
	 */
	static uint32_t LCG() {
		static uint32_t a = 1664525U;
		static uint32_t c = 1013904223U;
		static uint32_t X0 = 0;

		X0 = a*X0+c;
		return X0;
	}
}

#endif //
