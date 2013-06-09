#include <stdio.h>
#include <string.h>
#include "simhash.h"

using namespace alg;
void addsentence(char * str, SimHash &h);

int main(void) {
	char strA[] = {"the cat sat on the mat"};
	char strB[] = {"the cat sat on a mat"};
	char strC[] = {"we all scream for ice cream"};
	printf("%s\n", strA);
	printf("%s\n", strB);
	printf("%s\n", strC);

	SimHash h1, h2, h3;

	addsentence(strA, h1);
	addsentence(strB, h2);
	addsentence(strC, h3);

	printf("%u\n", h1.Hash());
	printf("%u\n", h2.Hash());
	printf("%u\n", h3.Hash());

	printf("hamming distance:\n");
	printf("h1, h2 : %d\n", SimHash::Distance(h1.Hash(), h2.Hash()));
	printf("h1, h3 : %d\n", SimHash::Distance(h1.Hash(), h3.Hash()));
	printf("h2, h3 : %d\n", SimHash::Distance(h2.Hash(), h3.Hash()));
}

void addsentence(char * str, SimHash &h) {
	char *ptr;
	for (ptr=str;;ptr=NULL) {
		char *token = strtok(ptr, " ");
		if (token == NULL) {
			break;
		}
		h.AddWord(token, strlen(token));
	}
}
