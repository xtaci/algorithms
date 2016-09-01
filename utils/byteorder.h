#ifndef ALGO_BYTEORDER_H__
#define ALGO_BYTEORDER_H__
#include <stdint.h>
#include <stdbool.h>

/**
 * test endianness of current machine 
 * mem: 0D 0C 0B 0A //big endian 
 * mem: 0A 0B 0C 0D //little endian 
 * V=0x0D0C0B0A
 */
static inline bool 
is_big_endian()
{
	int v=0x0D0C0B0A;
	char c = *(char*)&v;

	if (c == 0x0A)	return false;
	return true;
}

/**
 * uint16_t byte swap mask
 */
#define BYTE_MASK_A_	0xff00
#define BYTE_MASK__B	0x00ff

/**
 *  byte swap 2-byte
 */
static inline uint16_t 
byte_swap2(uint16_t original)
{
	uint16_t swapped;

	swapped = (( (original) & BYTE_MASK_A_) >> 8)
				|
				(( (original) & BYTE_MASK__B) <<8);

	return swapped;
}

/**
 * uint32_t byte swap mask
 */
#define BYTE_MASK_A_C_  0xff00ff00
#define BYTE_MASK__B_D  0x00ff00ff
#define BYTE_MASK_AB__  0xffff0000
#define BYTE_MASK___CD  0x0000ffff

/**
 *  byte swap 4-byte
 */
static inline uint32_t 
byte_swap4(uint32_t original)
{
	uint32_t swapped;

	// ABCD => BADC
	swapped = (( (original) & BYTE_MASK_A_C_ ) >> 8 ) 
				|   
				(( (original) & BYTE_MASK__B_D ) << 8 );

	// BADC => DCBA
	swapped = (( swapped & BYTE_MASK_AB__ ) >> 16 )
				|   
				(( swapped & BYTE_MASK___CD ) << 16 );

	return swapped;
}

/*
 * uint64_t byte swap mask
 */
#define BYTE_MASK_A_C_E_G_  0xff00ff00ff00ff00ULL
#define BYTE_MASK__B_D_F_H  0x00ff00ff00ff00ffULL
#define BYTE_MASK_AB__EF__  0xffff0000ffff0000ULL
#define BYTE_MASK___CD__GH  0x0000ffff0000ffffULL
#define BYTE_MASK_ABCD____  0xffffffff00000000ULL
#define BYTE_MASK_____EFGH  0x00000000ffffffffULL

/**
 * byte swap 8-byte
 */
static inline uint64_t 
byte_swap8( uint64_t original )
{
	uint64_t swapped;

	// ABCDEFGH => BADCFEHG
	swapped = (( (original) & BYTE_MASK_A_C_E_G_ ) >> 8 )
				|
				(( (original) & BYTE_MASK__B_D_F_H ) << 8 );

	// BADCFEHG => DCBAHGFE
	swapped = (( swapped & BYTE_MASK_AB__EF__ ) >> 16 )
				|
				(( swapped & BYTE_MASK___CD__GH ) << 16 );

	// DCBAHGFE => HGFEDCBA
	swapped = (( swapped & BYTE_MASK_ABCD____ ) >> 32 )
				|
				(( swapped & BYTE_MASK_____EFGH ) << 32 );

	return swapped;
}

#endif //
