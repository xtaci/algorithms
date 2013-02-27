#include <stdio.h>
#include "skip_list.h"

void print_skipset(struct SkipSet * ss)
{
    struct SkipNode* x = ss->header->forward[0];
    printf("{");
    while(x != NULL) {
        printf("%d->%d", x->key, x->value);
        x = x->forward[0];
        if(x != NULL)
            printf(", ");
    }    
    printf("}\n");
}

int main()
{
	struct SkipSet* ss = sl_make_skipset();

	const int MAX_ELEMENTS = 20;

	int i = 0;
	srand(time(NULL));
	
	for(i = 0; i < MAX_ELEMENTS; i++ ){
		sl_insert(ss, i, rand()%100);
	}

	printf("The skip list :\n");
	print_skipset(ss);

	printf("Random get keys :\n");
	for(i = 0; i < MAX_ELEMENTS; i++ ){
		int r = rand()%100;
		printf("get: %d->%d\n",r, sl_get(ss, r)); 
	}
	
	printf("random deleteion:\n");
	for(i = 0; i < MAX_ELEMENTS; i++ ){
		int r = rand()%100;
		printf("delete key :%d\n",r); 
		sl_delete(ss, r);
	}

	printf("The skip list after deletion:\n");

	print_skipset(ss);
	exit(0);
}
