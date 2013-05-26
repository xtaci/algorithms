#include "trie.h"

int main(void) {
	alg::Trie trie;	
	const char *strs[] = {"sap", "sat", "sad", "rat", "ram", "rag", "rap", "sat", "ram","rag", "nap", "Nat", "lap"};

	for (uint32_t i=0;i<sizeof(strs)/sizeof(char*);i++) {
		char * str = strdup(strs[i]);
		trie.Add(str);
		free(str);
	}

	printf("count of :%s %d\n", "sat", trie.Count("sat"));
	printf("count of prefix :%s %d\n", "ra", trie.CountPrefix("ra"));
}
