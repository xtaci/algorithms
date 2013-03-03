#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h> /* rand() */
#include "dos_tree.h"

using namespace alg;
int main(void)
{
	DosTree t;
    t.print();

	srand(time(NULL));
	int MAXELEMENT = 50;
	int i;
    for(i=0; i<MAXELEMENT; i++) {
        int key = rand() % 1000;
        printf("Inserting [%d]\n\n", key);
        t.insert(key);
    }

	t.print();

	for(i=0; i<MAXELEMENT; i++) {
		DosTree::dostree_node n = t.index(i+1);
		if(n!=NULL) printf("the %dth element is %d\n\n", i+1, n->key);
    }
    
	t.print();

	printf("deleteing %d smallest elements\n", MAXELEMENT/2);
	for(i=0; i<MAXELEMENT/2; i++) {
		// deleting half elements
		DosTree::dostree_node n = t.index(1);
		t.delete_key(n);
    }

    t.print();

	for(i=0; i<MAXELEMENT/2+1; i++) {
		DosTree::dostree_node n = t.index(i+1);
		if(n!=NULL) printf("the %dth element is %d\n\n", i+1, n->key);
    }

	t.print();
	return 0;
}
