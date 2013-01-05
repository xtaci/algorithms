#include <stdio.h>
#include <generic.h>
#include <time.h>

#include "shuffle.h"
#include "binary_search_tree.h"

int main()
{
	const int MAX_ELEMENTS = 10;
	int list[MAX_ELEMENTS];

	treeNode * root = NULL;

	int i = 0;
	srand(time(NULL));
	// generate random numbers and fill them to the list
	for(i = 0; i < MAX_ELEMENTS; i++ ){
		list[i] = rand()%100; 
	}

	shuffle(list, MAX_ELEMENTS);
	printlist(list,MAX_ELEMENTS);

	root = bst_insert(NULL, list[0]);
	for(i = 1; i < MAX_ELEMENTS; i++ ){
		bst_insert(root, list[i]);
	}

	int min =  bst_find_min(root)->data;
	int max =  bst_find_max(root)->data;
	printf("min: %d, max %d\n", min,max);

	exit(0);
}

