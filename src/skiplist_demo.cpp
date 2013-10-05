#include <stdio.h>
#include "skiplist.h"

using namespace alg;

int main()
{

	SkipList<int, int> ss;

	const int MAX_ELEMENTS = 20;

	int i = 0;
	srand(time(NULL));
	
	for(i = 0; i < MAX_ELEMENTS; i++ ){
		ss.insert(i, rand()%100);
	}

	printf("The skip list :\n");
	ss.print();

	printf("Random get keys :\n");
	for(i = 0; i < MAX_ELEMENTS; i++ ){
		int r = rand()%100;
		try {
			printf("get: %d->%d\n",r, ss[r]); 
		} catch (std::exception &e) {
			printf("%s\n", e.what());
		}
	}
	
	printf("random deleteion:\n");
	for(i = 0; i < MAX_ELEMENTS; i++ ){
		int r = rand()%100;
		printf("delete key :%d\n",r); 
		ss.delete_key(r);
	}

	printf("The skip list after deletion:\n");

	ss.print();
	return 0;
}
