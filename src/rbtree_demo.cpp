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

using namespace alg;

#define INDENT_STEP  4

int main() {
    int i;
	RBTree<int,int> t;
	t.print();

	srand(time(NULL));

	int MAXELEMENT = 50;
	printf("Inserting: \t");
    for(i=0; i<MAXELEMENT; i++) {
        int key  = i;
        int value = rand() % 10000;
        printf("[%d, %d]\t", key, value);
		t.insert(key, value);
        assert(t[key] == value);
    }

	printf("\n");
	t.print();

    printf("\nDeleting: \t");
    for(i=0; i<MAXELEMENT; i++) {
        int key = i;
        printf("[%d]\t", key);
        t.delete_key(key);
    }

	printf("\n");
	t.print();
    return 0;
}

