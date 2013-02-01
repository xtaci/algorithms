#include <stdio.h>
#include <stdlib.h>

#include "generic.h"
#include "word_seg.h"

int main(void)
{
	struct WordSeg * ws = word_seg_init("./src/dict.txt");
	
	char buf[128];
	printf("input a sentence in GB18030 encoding :\n");
	
	while(1){
		scanf("%s", buf);

		Queue * q = word_seg_run(ws, buf);
		short cursor = 0;
		while(!queue_is_empty(q)) {
			int state = queue_front(q);
			uint32_t CH;
			cursor += gb18030_read(buf,cursor,&CH);
			gb18030_putchar(CH);
			putchar(state);
			if(state=='0') printf(" ");
			if(state=='3') printf(" ");
			dequeue(q);
		}
		printf("\n");
	}
	
	exit(0);
}
