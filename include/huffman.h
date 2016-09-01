/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * HUFFMAN CODING  
 *
 * Features:
 *   In computer science and information theory, Huffman coding is an entropy 
 * encoding algorithm used for lossless data compression. The term refers to the
 * use of a variable-length code table for encoding a source symbol (such as a
 * character in a file) where the variable-length code table has been derived in
 * a particular way based on the estimated probability of occurrence for each
 * possible value of the source symbol. It was developed by David A. Huffman
 * while he was a Ph.D. student at MIT, and published in the 1952 paper 
 * "A Method for the Construction of Minimum-Redundancy Codes"
 * 
 * http://en.wikipedia.org/wiki/Huffman_coding
 *
 ******************************************************************************/

#ifndef ALGO_HUFFMAN_CODING_H__
#define ALGO_HUFFMAN_CODING_H__

#include <stdint.h>
#include <stdlib.h>

#include "priority_queue.h"
#include "hash_table.h"
#include "stack.h"

namespace alg {
	/**
	 * The Huffman tree definition
	 */
	class HuffTree {
		private:
			/**
			 * The Huffman tree node definition
			 */
			struct HuffNode{
				unsigned char symbol;
				struct HuffNode *left, *right;
			};

			/**
			 * The code for a symbol of huffman
			 */
			struct HuffCode {
				char code[256];		// max length is 256
				uint32_t length;	// the length of the code;
			};

		private:
			HashTable<uint32_t, HuffCode> m_symbol;		// hash table for encoding 
			HuffNode * m_root;					// the root node for decoding
			uint32_t m_freqs[256];				// frequency array, you can pass this array 
			// to the peer for constructing huffman
			// tree.
		public:
			/**
			 * Construct a Huffman Tree with a sample string.
			 * the string is either the characteristic of the text
			 * or simply the original text to compress.
			 */
			HuffTree(const char * sample) : m_symbol(256) {	
				// count frequency for each char(8-bit).
				memset(m_freqs, 0, sizeof(m_freqs));

				int i;	
				for(i=0; sample[i]!='\0'; i++)
					m_freqs[(unsigned char) sample[i]]++;

				recreate_from_freqs();	
			};

			~HuffTree() {
				// TODO: free HuffNodes	
			};

		private:
			HuffTree(const HuffTree&);
			HuffTree& operator=(const HuffTree&);
		public:

			/**
			 * Encoding 
			 * encode a message into codes, codes should be large enough to hold the output
			 * eg:. the length of string
			 * the length in BITS will be returned.
			 */
			uint32_t encode(const char * msg, char * codes) {
				uint32_t cursor = 0;
				for (uint32_t i=0; msg[i]!='\0'; i++) {
					HuffCode & hcode = m_symbol[(uint32_t)msg[i]];

					for (uint32_t j=0;j<hcode.length;j++) {
						uint32_t off = cursor%8;
						uint32_t base= cursor/8;

						if (hcode.code[j] =='0') {
							codes[base] &= ~(1<<(7-off));
						} else {
							codes[base] |= 1<<(7-off);
						}
						cursor++;
					}
				}

				return cursor;
			};

			/**
			 * Decoding
			 * decoding is based on tree traversal
			 * pass length of Bits
			 */
			void decode(const char * codes, uint32_t length) {
				HuffNode * node = m_root;

				//For each "bit" of the string to decode
				//we take a step to the left for 0
				//or ont to the right for 1
				uint32_t cursor;

				for (cursor=0;cursor<length;cursor++) {
					if(node->left == NULL && node->right == NULL) {
						printf("%c",node->symbol);
						node = m_root; //reset tree
					}

					uint32_t off = cursor%8;
					uint32_t base= cursor/8;

					char bit = codes[base] & (1<<(7-off));

					if (bit == 0) {
						node = node->left;
					} else {
						node = node->right;
					}
				}

				if(node->left == NULL && node->right == NULL) {
					printf("%c",node->symbol);
				}

				printf("\n");
			};

		private:
			/**
			 * recreate the huff tree from an array[256] i.e. 8bit 
			 * useful for peer reconstructing decoding tree.
			 */
			void recreate_from_freqs() {
				// construct a priority queue for huffman tree building
				PQ<HuffNode *> pq;

				int i;
				for(i=0; i<256; i++)
					if(m_freqs[i] !=0) {
						HuffNode * n = new HuffNode();
						n->left = NULL;
						n->right = NULL;
						n->symbol = (unsigned char) i;

						pq.queue(n, m_freqs[i]); // freq. as priority
					}

				// tree building subroutine 
				while(pq.count()>1) {
					int prio1, prio2, newprio;
					HuffNode * node1, *node2, *new_node;	

					node1 = pq.top(&prio1); pq.dequeue();
					node2 = pq.top(&prio2); pq.dequeue();

					newprio = prio1+prio2;

					new_node =  new HuffNode;
					new_node->left = node1;
					new_node->right = node2;

					pq.queue(new_node, newprio);
				}

				// set root
				int prio;
				m_root = pq.top(&prio);
				pq.dequeue();

				// construct symbol lookup table
				char code[256];
				build_symbol(m_root, 0, code); 
			};

			/**
			 * building symbol lookup table
			 */
			void build_symbol(struct HuffNode * node, int k, char code[256]) {
				//If we reach the leaf node we introduce the code in the table
				if(node->left == NULL && node->right == NULL) {
					code[k] = '\0';
					HuffCode hcode;
					strncpy(hcode.code, code, k);
					hcode.length = k;
					m_symbol[(uint32_t)node->symbol] = hcode;
					//	printf("k %d, code :%s symbol %d-> %c\n",k, hcode->code, node->symbol, node->symbol);
				}

				//We concatenate a 0 for each step to the left
				if(node->left!=NULL) {
					code[k] = '0';
					build_symbol(node->left, k+1,code);
				}

				//We concatenate a 1 for each step to the right
				if(node->right!=NULL) {
					code[k] = '1';
					build_symbol(node->right, k+1,code);
				}
			};
	};
}

#endif //
