/* Copyright (c) 2013 the authors listed at the following URL, and/or
the authors of referenced articles or incorporated external code:
http://en.literateprograms.org/Red-black_tree_(C)?action=history&offset=20120524204657

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Retrieved from: http://en.literateprograms.org/Red-black_tree_(C)?oldid=18555
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h> /* rand() */

#include "rbtree.h"

static int compare_int(uintptr_t left, uintptr_t right);
static void print_tree(rbtree t);
static void print_tree_helper(rbtree_node n, int indent);

int compare_int(uintptr_t leftp, uintptr_t rightp) {
    int left = (int)leftp;
    int right = (int)rightp;
    if (left < right) 
        return -1;
    else if (left > right)
        return 1;
    else {
        assert (left == right);
        return 0;
    }
}

#define INDENT_STEP  4

void print_tree_helper(rbtree_node n, int indent);

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
        printf("%d\n", (int)n->key);
    else
        printf("<%d>\n", (int)n->key);
    if (n->left != NULL) {
        print_tree_helper(n->left, indent + INDENT_STEP);
    }
}


int main() {
    int i;
    rbtree t = rbtree_create();
    print_tree(t);

	srand(time(NULL));

	int MAXELEMENT = 50;
	printf("Inserting: \t");
    for(i=0; i<MAXELEMENT; i++) {
        int key  = rand() % 100;
        int value = rand() % 10000;
        printf("[%d, %d]\t", key, value);
        rbtree_insert(t, (uintptr_t)key, (uintptr_t)value, compare_int);
        assert(rbtree_lookup(t, (uintptr_t)key, compare_int) == (uintptr_t)value);
    }

	printf("\n");
    print_tree(t);

    printf("\nDeleting: \t");
    for(i=0; i<MAXELEMENT; i++) {
        int key = rand() % 100;
        printf("[%d]\t", key);
        rbtree_delete(t, (uintptr_t)key, compare_int);
    }

	printf("\n");
    print_tree(t);
    return 0;
}

