/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * BIT-SET
 *
 * a bit-set data structure
 *
 ******************************************************************************/

#ifndef ALGO_BIT_SET_H__
#define ALGO_BIT_SET_H__

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

namespace alg {
	/**
	 * definition of bitset class
	 */
	class BitSet {
		private:
			uint32_t m_size;	//size in bits
			uint32_t m_bytes; // size in bytes
			unsigned char * m_bits; // the bits

		public:
			/**
			 * construct BitSet by a give number of bits 
			 */
			BitSet(uint32_t num_bits) {
				// round up
				m_bytes = num_bits/8+1;
				m_size = m_bytes * 8;
				m_bits = new unsigned char[m_bytes];
				memset(m_bits, 0, m_bytes);
			}

			/**
			 * safely free
			 */
			~BitSet() {
				delete [] m_bits;
			}

		private:
			BitSet(const BitSet&);
			BitSet& operator=(const BitSet&);

		public:

			/**
			 * set 1 to position [bit]
			 */
			inline void set(uint32_t bit) {
				if (bit>=m_size) return;

				uint32_t n = bit/8;
				uint32_t off = bit%8;

				m_bits[n] |= 128U>>off;
			}

			/**
			 * set 0 to position [bit]
			 */
			inline void unset(uint32_t bit) {
				if (bit>=m_size) return;

				uint32_t n = bit/8;
				uint32_t off = bit%8;

				m_bits[n] &= ~(128U>>off);
			}

			/**
			 * test a bit , true if set, false if not.
			 */
			inline bool test(uint32_t bit) {
				if (bit>=m_size) return false;

				uint32_t n = bit/8;
				uint32_t off = bit%8;

				if (m_bits[n] & (128U>>off))return true;
				return false;
			}
	};
}

#endif //
