/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * SIMHASH FUNCTIONS
 *
 * http://matpalm.com/resemblance/simhash/
 * http://en.wikipedia.org/wiki/Hamming_distance
 *
 ******************************************************************************/

#ifndef ALGO_SIMHASH_H__
#define ALGO_SIMHASH_H__

#include <string.h>
#include <stdint.h>
#include "hash_string.h"

namespace alg {
	class SimHash {
		private:
			int V[32];
		public:
			SimHash() {
				memset(V, 0, sizeof(V));
			}

			/**
			 * hash a single word 
			 */
			void AddWord(const char * word, uint32_t len) {
				uint32_t hash = hash_fnv1a(word,len);
				for(int i=0;i<32;i++) {
					if (hash&(1<<i)) {
						V[i]++;
					} else {
						V[i]--;
					}
				}
			}

			/**
			 * get the hash of the document
			 */
			uint32_t Hash() {
				uint32_t hash=0;
				for(int i=0;i<32;i++) {
					if (V[i] > 0) {
						hash|= (1<<i);
					}
				}

				return hash;
			}

			/**
			 * calc the hamming distance of two hash.
			 */
			static int Distance(uint32_t hash1, uint32_t hash2) {
				uint32_t diff = hash1^hash2;
				int dist = 0;

				while(diff) {
					dist++;
					diff &=diff-1;
				}

				return dist;
			}
	};
}

#endif //
