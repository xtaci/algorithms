#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "kmp.h"
using namespace alg;
int main(void)
{
	srand(time(NULL));
	char * S = (char*)malloc(10000);
	char * W = (char*)malloc(6);

	memset(S,0, 10000);
	memset(W,0, 6);

	// random genrate a pattern for A, G, C,T
	const char P[] = {'A', 'G','C','T'};

	for (int i=0;i<10000;i++) {
		int k = rand()%4;
		S[i] = P[k];
	}

	for (int i=0;i<6;i++) {
		int k = rand()%4;
		W[i] = P[k];
	}

	// do a search for W from S
	int pos = kmp_search(S, W);

	printf("text:\n%s\n", S);
	if (pos > 0) {
		printf("found %s from text, pos %d\n", W, pos);
	} else {
		printf("cannot found %s from text\n", W);
	}
}
