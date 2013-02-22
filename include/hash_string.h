/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * STRING HASH FUNCTION
 *
 * code taken from: 
 * http://en.wikipedia.org/wiki/Java_hashCode()
 *
 ******************************************************************************/

#ifndef __STRING_HASH_H__
#define __STRING_HASH_H__

#include <stdint.h>

/**
 * hash a string into integer
 * using java's hashCode() implementation
 */
static inline uint32_t 
hash_string(const char * str, uint32_t len)
{
	uint32_t hash=0;	
	uint32_t i;	
	for (i=0;i<len;i++) {
		hash = 31*hash + (unsigned char)str[i];
	}

	return hash;
}


#endif //
