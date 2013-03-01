#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generic.h"
#include "word_seg.h"

using namespace alg;

/**
 * the state transition probability matrix. 
 * the 2-d array is in the format of :
 * SINGLE	-> S B M E
 * ... 		-> S B M E
 */
const float WordSeg::TP[4][4] = {
		{0.5f, 0.5f, 0.0f, 0.0f}, // S
		{0.0f, 0.0f, 0.5f, 0.5f}, // B
		{0.0f, 0.0f, 0.5f, 0.5f}, // M
		{0.5f, 0.5f, 0.0f, 0.0f}  // E
};

/**
 * the start probability of state
 */
const float WordSeg::SP[4] = {0.5f, 0.5f, 0.0f, 0.0f};

int main(void)
{
	WordSeg ws("./src/dict.txt.sogou");
	
	char buf[1024];
	printf("input a sentence in GB18030 encoding, no more than 256 words:\n");
	
	while(1){
		scanf("%s", buf);
		char *part, *brkt;
		const char *sep=" ";
		
	    for (part = strtok_r(buf, sep, &brkt);
	             part;
	             part = strtok_r(NULL, sep, &brkt))
	    {
			Queue<uint32_t> * q = ws.run(part);
			short cursor = 0;
			while(!q->is_empty()) {
				int state = q->front();
				uint32_t CH;
				cursor += gb18030_read(part,cursor,&CH);
				gb18030_putchar(CH);
				putchar(state);
				if(state=='0') printf(" ");
				if(state=='3') printf(" ");
				q->dequeue();
			}
			printf("\n");
			delete q;
		}
	}
	
	exit(0);
}
