#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h> /* rand() */

#include "interval_tree.h"

DEFINE_INTTREE_NIL_NODE;

void print_tree(inttree t);
void print_tree_helper(inttree t, inttree_node n, int indent);

#define INDENT_STEP  4

void print_tree_helper(inttree t, inttree_node n, int indent);

void print_tree(inttree t) {
    print_tree_helper(t, t->root, 0);
    puts("");
}

void print_tree_helper(inttree t, inttree_node n, int indent) {
    int i;
    if (n == nil) {
        fputs("<empty tree>", stdout);
        return;
    }
    if (n->right != nil) {
        print_tree_helper(t, n->right, indent + INDENT_STEP);
    }
    for(i=0; i<indent; i++)
        fputs(" ", stdout);
    if (n->color == BLACK)
        printf("[%d %d, m->%d]\n", n->low,n->high,n->m);
    else
        printf("*[%d %d, m->%d]\n", n->low, n->high,n->m);
    if (n->left != nil) {
        print_tree_helper(t, n->left, indent + INDENT_STEP);
    }
}


int main() {
    int i;
    inttree t = inttree_create();
    print_tree(t);

	srand(time(NULL));
	int MAXELEMENT = 50;
    for(i=0; i<MAXELEMENT; i++) {
        int low = rand() % 100;
        int high = low + rand() % 100;
        printf("Inserting [%d,%d]\n\n", low, high);
        inttree_insert(t, low, high);
    }

    print_tree(t);
	printf("search interval: [%d %d]\n", 5, 10);
	
    int low = 5;
    int high = 10;

	for(i=0; i<MAXELEMENT; i++) {
		inttree_node n = inttree_lookup(t,low,high);
		if (n!=nil) {
			printf("found & delete: [%d %d]\n", n->low, n->high);
			inttree_delete(t,n);	
		}
    }

    print_tree(t);

    return 0;
}

