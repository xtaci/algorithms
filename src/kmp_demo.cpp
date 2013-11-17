#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "kmp.h"
using namespace alg;
int main(void)
{
	srand(time(NULL));
	char * S = (char*)malloc(1001);
	char * W = (char*)malloc(5);

	memset(S,0, 1001);
	memset(W,0, 5);

	// random genrate a pattern for A, G, C,T
	const char P[] = {'A', 'G','C','T'};

	for (int i=0;i<1000;i++) {
		int k = rand()%4;
		S[i] = P[k];
	}

	for (int i=0;i<4;i++) {
		int k = rand()%4;
		W[i] = P[k];
	}

	// do a search for W from S
	int pos = kmp_search(S, W);
	printf("to be searched:%s\n", W);

	if (pos > 0) {
		printf("found in pos:%d\n", pos);
		printf("text:\n%.*s", pos, S);
		printf("\033[31m%s\033[0m", W);
		printf("%s\n",&S[pos + strlen(W)]);
	}
}
