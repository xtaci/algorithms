#include <stdio.h>
#include <stdlib.h>

#include "huffman.h"
#define STR "Huffman coding uses a specific method for choosing the representation for each symbol, resulting in a prefix code (sometimes called 'prefix-free codes', that is, the bit string representing some particular symbol is never a prefix of the bit string representing any other symbol) that expresses the most common source symbols using shorter strings of bits than are used for less common source symbols. Huffman was able to design the most efficient compression method of this type: no other mapping of individual source symbols to unique strings of bits will produce a smaller average output size when the actual symbol frequencies agree with those used to create the code."

int main(void)
{
	using namespace alg;
	HuffTree tree(STR);

	char codes[strlen(STR)];
	uint32_t length;

	printf("encoding message: \n%s\n", STR);

	printf("<<< before huffman coding : length:%lu bytes\n", strlen(STR));
	memset(codes, 0, sizeof(codes));
	length = tree.encode(STR, codes); 

	printf(">>> after huffman coding : length:%u bytes\n", length/8);
	printf("decoding messsage:\n");
	tree.decode(codes, length);

	return 0;
}
