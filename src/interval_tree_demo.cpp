#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h> /* rand() */

#include "interval_tree.h"

void print_tree(rbtree t);
void print_tree_helper(rbtree_node n, int indent);

#define INDENT_STEP  4

void print_tree(rbtree t) {
    print_tree_helper(t->root, 0);
    puts("");
}

void print_tree_helper(rbtree_node n, int indent) {
    int i;

    if (n == NULL) {
        fputs("<empty tree>", stdout);
        return;
    }

    if (n->right != NULL) {
        print_tree_helper(n->right, indent + INDENT_STEP);
    }
    for(i=0; i<indent; i++)
        fputs(" ", stdout);
    if (n->color == BLACK)
        printf("[%d %d, m->%d]\n", IVLNODE(n)->low,IVLNODE(n)->high,IVLNODE(n)->m);
    else
        printf("*[%d %d, m->%d]\n", IVLNODE(n)->low, IVLNODE(n)->high,IVLNODE(n)->m);
    if (n->left != NULL) {
        print_tree_helper(n->left, indent + INDENT_STEP);
    }
}


int main() {
    int i;
    rbtree t = ivltree_create();
    print_tree(t);

	srand(time(NULL));
	int MAXELEMENT = 50;
    for(i=0; i<MAXELEMENT; i++) {
        int low = rand() % 100;
        int high = low + rand() % 100;
        printf("Inserting [%d,%d]\n\n", low, high);
        ivltree_insert(t, low, high);
    }

    print_tree(t);
	printf("search interval: [%d %d]\n", 5, 10);
	
    int low = 5;
    int high = 10;

	for(i=0; i<MAXELEMENT; i++) {
		ivltree_node n = ivltree_lookup(t,low,high);
		if (n!=NULL) {
			printf("found & delete: [%d %d]\n", n->low, n->high);
			ivltree_delete(t,n);	
		}
    }

    print_tree(t);

    return 0;
}

