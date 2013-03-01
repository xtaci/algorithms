#include <stdio.h>
#include "skip_list.h"

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
		printf("get: %d->%d\n",r, ss[r]); 
	}
	
	printf("random deleteion:\n");
	for(i = 0; i < MAX_ELEMENTS; i++ ){
		int r = rand()%100;
		printf("delete key :%d\n",r); 
		ss.delete_key(r);
	}

	printf("The skip list after deletion:\n");

	ss.print();
	exit(0);
}
