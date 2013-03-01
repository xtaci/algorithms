#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h> /* rand() */

#include "interval_tree.h"
using namespace alg;
int main() {
    int i;
	IntervalTree t;
	t.print();

	srand(time(NULL));
	int MAXELEMENT = 50;
    for(i=0; i<MAXELEMENT; i++) {
        int low = rand() % 100;
        int high = low + rand() % 100;
        printf("Inserting [%d,%d]\n\n", low, high);
        t.insert(low, high);
    }

	t.print();
	printf("search interval: [%d %d]\n", 5, 10);
	
    int low = 5;
    int high = 10;

	for(i=0; i<MAXELEMENT; i++) {
		IntervalTree::ivltree_node n = t.lookup(low,high);
		if (n!=NULL) {
			printf("found & delete: [%d %d]\n", n->low, n->high);
			t.delete_key(n);
		}
    }
	t.print();

    return 0;
}

