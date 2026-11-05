/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * BLOOM FILTER
 *
 * Features:
 *   A Bloom filter with 1% error and an optimal value of k, in contrast,
 * requires only about 9.6 bits per element — regardless of the size of the 
 * elements. This advantage comes partly from its compactness, inherited from
 * arrays, and partly from its probabilistic nature. If a 1% false-positive rate
 * seems too high, adding about 4.8 bits per element decreases it by ten times.
 *
 * http://en.wikipedia.org/wiki/Bloom_filter
 * 
 ******************************************************************************/

#ifndef ALGO_BLOOM_FILTER_H__
#define ALGO_BLOOM_FILTER_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "hash_string.h"
#include "bitset.h"
#include "universal_hash.h"

namespace alg
{
	/**
	 * definiton of bloom filter structure
	 */
	template<uint32_t K=8>
	class BloomFilter {
	private:
		uint32_t m_bits;	// num of bits
		uint32_t m_probset;	// total elements
		BitSet m_bitset;	// the bit set structure.
		struct UHash m_hash[K];	// universal hash parameters
	public:
		/**
		 * check false positive rate here, for setting up:
		 * http://pages.cs.wisc.edu/~cao/papers/summary-cache/node8.html
		 * Examples:
		 * Table 3: False positive rate under various m/n and k combinations.
			m/n k(opt)	k=1		k=2		k=3		k=4			k=5			k=6			k=7			k=8
			2	1.39	0.393	0.400	 	 	 	 	 	 
			3	2.08	0.283	0.237	0.253	 	 	 	 	 
			4	2.77	0.221	0.155	0.147	0.160	 	 	 	 
			5	3.46	0.181	0.109	0.092	0.092		0.101	 	 	 
			6	4.16	0.154	0.0804	0.0609	0.0561		0.0578		0.0638	 	 
			7	4.85	0.133	0.0618	0.0423	0.0359		0.0347		0.0364	 	 
			8	5.55	0.118	0.0489	0.0306	0.024		0.0217		0.0216		0.0229	 
			9	6.24	0.105	0.0397	0.0228	0.0166		0.0141		0.0133		0.0135		0.0145
			10	6.93	0.0952	0.0329	0.0174	0.0118		0.00943		0.00844		0.00819		0.00846
			11	7.62	0.0869	0.0276	0.0136	0.00864		0.0065		0.00552		0.00513		0.00509
			12	8.32	0.08	0.0236	0.0108	0.00646		0.00459		0.00371		0.00329		0.00314
			13	9.01	0.074	0.0203	0.00875	0.00492		0.00332		0.00255		0.00217		0.00199
			14	9.7		0.0689	0.0177	0.00718	0.00381		0.00244		0.00179		0.00146		0.00129
			15	10.4	0.0645	0.0156	0.00596	0.003		0.00183		0.00128		0.001		0.000852
			16	11.1	0.0606	0.0138	0.005	0.00239		0.00139		0.000935	0.000702	0.000574
			17	11.8	0.0571	0.0123	0.00423	0.00193		0.00107		0.000692	0.000499	0.000394
			18	12.5	0.054	0.0111	0.00362	0.00158		0.000839	0.000519	0.00036		0.000275
			19	13.2	0.0513	0.00998	0.00312	0.0013		0.000663	0.000394	0.000264	0.000194
			20	13.9	0.0488	0.00906	0.0027	0.00108		0.00053		0.000303	0.000196	0.00014
			21	14.6	0.0465	0.00825	0.00236	0.000905	0.000427	0.000236	0.000147	0.000101

		 * as we can see:
		 * to reach 1% positive rate, you can set k=8, m 10 times larger than n.
		 * to reach 0.1% positive rate, set k=8, m 15 times larger than n.
		 * 
		 * k-->num of hash functions
		 * m--> bit set size
		 * n--> problem set size
		*/
		BloomFilter(uint32_t m, uint32_t n):m_bitset(m)
		{
			assert(m>n);
			m_bits=m;
			m_probset=n;
			
			for(uint32_t i=0;i<K;i++) {
				uhash_init(&m_hash[i], m_bits);
			} 
		}

		/**
		 * hash a string, and set the corresponding bits
		 */
		void set(const char * str) 
		{
			uint32_t len = strlen(str);
			uint32_t strhash = hash_fnv1a(str, len);
	
			for(uint32_t i=0;i<K;i++) {
				uint32_t hash = uhash_integer(&m_hash[i], strhash);
				m_bitset.set(hash);
			}
		}

		/**
		 * test whether a string is in the bloom filter
		 */
		bool test(const char * str)
		{
			uint32_t len = strlen(str);
			uint32_t strhash = hash_fnv1a(str, len);
			
			for(uint32_t i=0;i<K;i++) {
				uint32_t hash = uhash_integer(&m_hash[i], strhash);
				if (!m_bitset.test(hash)) return false;
			}

			return true;
		}
	};
}

#endif //
