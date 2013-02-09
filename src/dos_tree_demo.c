#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h> /* rand() */
#include "dos_tree.h"

void print_tree(dostree t);
void print_tree_helper(dostree t, dostree_node n, int indent);

#define INDENT_STEP  4

void print_tree_helper(dostree t, dostree_node n, int indent);

void print_tree(dostree t) {
    print_tree_helper(t, t->root, 0);
    puts("");
}

void print_tree_helper(dostree t, dostree_node n, int indent) {
    int i;
    if (n == t->nil) {
        fputs("<empty tree>", stdout);
        return;
    }
    if (n->right != t->nil) {
        print_tree_helper(t, n->right, indent + INDENT_STEP);
    }
    for(i=0; i<indent; i++)
        fputs(" ", stdout);
    if (n->color == BLACK)
        printf("[key:%d size:%d]\n", n->key,n->size);
    else
        printf("*[key:%d size:%d]\n", n->key, n->size);
    if (n->left != t->nil) {
        print_tree_helper(t, n->left, indent + INDENT_STEP);
    }
}


int main(void)
{
	dostree t = dostree_create();
    print_tree(t);

	srand(time(NULL));
	int MAXELEMENT = 50;
	int i;
    for(i=0; i<MAXELEMENT; i++) {
        int key = rand() % 1000;
        printf("Inserting [%d]\n\n", key);
        dostree_insert(t, key);
    }

    print_tree(t);

	for(i=0; i<MAXELEMENT; i++) {
		dostree_node n = dostree_lookup(t, t->root,i+1);
		if(n!=t->nil) printf("the %dth element is %d\n\n", i+1, n->key);
    }
    
	print_tree(t);

	printf("deleteing %d smallest elements\n", MAXELEMENT/2);
	for(i=0; i<MAXELEMENT/2; i++) {
		// deleting half elements
		dostree_node n = dostree_lookup(t, t->root,1);
		dostree_delete(t, n);
    }

    print_tree(t);

	for(i=0; i<MAXELEMENT/2; i++) {
		dostree_node n = dostree_lookup(t, t->root,i+1);
		if(n!=t->nil) printf("the %dth element is %d\n\n", i+1, n->key);
    }

	exit(0);
}
