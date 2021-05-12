/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * STRING HASH FUNCTIONS
 *
 * 1. http://en.wikipedia.org/wiki/Java_hashCode()
 * 2. http://www.isthe.com/chongo/tech/comp/fnv/
 *
 ******************************************************************************/

#ifndef ALGO_STRING_HASH_H__
#define ALGO_STRING_HASH_H__

#include <stdint.h>

namespace alg {
	/**
	 * hash a string into integer
	 * using java's hashCode() implementation
	 */
	static uint32_t hash_string(const char * str, uint32_t len) {
		uint32_t hash=0;	
		uint32_t i;	
		for (i=0;i<len;i++) {
			hash = 31*hash + (unsigned char)str[i];
		}

		return hash;
	}

	static uint32_t hash_fnv1a(const char * str, uint32_t len) {
		uint32_t prime = 16777619U;
		uint32_t hash = 2166136261U;

		for (uint32_t  i=0;i<len;i++) {
			hash = hash ^ str[i];
			hash = hash * prime;
		}

		return hash;
	}
}

#endif //
