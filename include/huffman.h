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

#ifndef __HUFFMAN_CODING_H__
#define __HUFFMAN_CODING_H__

#include <stdint.h>
#include <stdlib.h>

#include "priority_queue.h"
#include "hash_table.h"
#include "stack.h"

/**
 * The Huffman tree node definition
 */
struct HuffNode{
	unsigned char symbol;
	struct HuffNode *left, *right;
};

/**
 * The Huffman tree definition
 */
struct HuffTree {
	struct HuffNode *root;	// the root node.
	struct HashTable * ht;	// hash table for encoding lookup
	uint32_t freqs[256];		// frequency array, you can pass this array 
								// to the peer for constructing huffman
								// tree.
};

/**
 * The code for huffman
 */
typedef struct {
	char * code;
	uint32_t length;	// the length of the code;
}HuffCode;


/**
 * for building symbol lookup table
 */
static void 
__huffman_traverse(struct HuffNode * node, struct HashTable * ht, int k, char code[256])
{
	//If we reach the end we introduce the code in the table
	if(node->left == NULL && node->right == NULL)
	{
		code[k] = '\0';
		HuffCode * hcode = (HuffCode *)malloc(sizeof(HuffCode));
		hcode->code = (char *)malloc(sizeof(char) * (k+1));
		strcpy(hcode->code, code);
		hcode->length = k;

		hash_table_set(ht, node->symbol, (uintptr_t)hcode);
	//	printf("k %d, code :%s symbol %d-> %c\n",k, hcode->code, node->symbol, node->symbol);
	}
	
	//We concatenate a 0 for each step to the left
	if(node->left!=NULL)
	{
		code[k] = '0';
		__huffman_traverse(node->left,ht, k+1,code);
	}

	//We concatenate a 1 for each step to the right
	if(node->right!=NULL)
	{
		code[k] = '1';
		__huffman_traverse(node->right,ht, k+1,code);
	}
}  

/**
 * Symbol Table Initialization for encoding proc.
 */
static inline void 
__huffman_sym_init(struct HuffTree *tree)
{
	// init
	tree->ht = hash_table_create(256);	
	char code[256];
	__huffman_traverse(tree->root, tree->ht, 0, code); 
}

/**
 * recreate the huff tree from an array[256] i.e. 8bit 
 * useful for peer reconstructing decoding tree.
 */
static struct HuffTree * 
huffman_recreate(uint32_t freqs[])
{
	// we create the tree
	struct HuffTree * tree = (struct HuffTree *)malloc(sizeof(struct HuffTree));
	memcpy(tree->freqs, freqs, sizeof(tree->freqs));

	// construct a priority queue for huffman tree building
	struct PQ * pq =  pq_create();

	int i;
	for(i=0; i<256; i++)
		if(tree->freqs[i] !=0)
		{
			struct HuffNode * n = 
					(struct HuffNode *)malloc(sizeof(struct HuffNode));
			n->left = NULL;
			n->right = NULL;
			n->symbol = (unsigned char) i;
			
			pq_queue(pq,(uintptr_t)n, tree->freqs[i]); // freq. as priority
		}

	// tree building subroutine 
	while(pq_count(pq)>1)
	{
		uint32_t prio1, prio2, newprio;
		struct HuffNode * node1, *node2, *new_node;	

		node1 = (struct HuffNode *)pq_dequeue(pq, &prio1);
		node2 = (struct HuffNode *)pq_dequeue(pq, &prio2);

		newprio = prio1+prio2;

		new_node = (struct HuffNode*)malloc(sizeof(struct HuffNode));
		new_node->left = node1;
		new_node->right = node2;

		pq_queue(pq, (uintptr_t)new_node, newprio);
	}

	// set root & destory prio queue.
	uint32_t prio;
	tree->root = (struct HuffNode *)pq_dequeue(pq, &prio);
	pq_destroy(pq);

	// construct symbol lookup table
	__huffman_sym_init(tree);
			
	return tree;

}

/**
 * Construct a Huffman Tree with a sample string, the string must contain 
 * every characters passing to encode function.
 */
static inline struct HuffTree * 
huffman_create(char * sample)
{
	// count frequency for each char(8-bit).
	uint32_t freqs[256];
	memset(freqs, 0, sizeof(freqs));
	
	int i;	
	for(i=0; sample[i]!='\0'; i++)
		freqs[(unsigned char) sample[i]]++;

	return huffman_recreate(freqs);	
}

/**
 * Encoding 
 * encode a message into codes, codes should be large enough to hold the output
 * ie. the length of string
 * the length in BITS will be returned.
 */
static uint32_t
huffman_encode(struct HashTable * ht, char * msg, char * codes)
{
	int i;
	uint32_t cursor = 0;
	for(i=0; msg[i]!='\0'; i++)
	{
		HuffCode * hcode = (HuffCode *)hash_table_get(ht, msg[i]);
		
		int j;
		for (j=0;j<hcode->length;j++) {
			uint32_t off = cursor%8;
			uint32_t base= cursor/8;
					
			if (hcode->code[j] =='0') {
				codes[base] &= ~(1<<(7-off));
			} else {
				codes[base] |= 1<<(7-off);
			}
			cursor++;
		}
	}

	return cursor;
}

/**
 * Decoding
 * decoding is based on tree traversal
 * pass length of Bits
 */
static void 
huffman_decode(struct HuffTree * tree, char * codes, uint32_t length)
{
	struct HuffNode * node = tree->root;

	//For each "bit" of the string to decode
	//we take a step to the left for 0
	//or ont to the right for 1
	uint32_t cursor;

	for(cursor=0;cursor<length;cursor++) {
		if(node->left == NULL && node->right == NULL) {
			printf("%c",node->symbol);
			node = tree->root; //reset tree
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
} 

#endif //
