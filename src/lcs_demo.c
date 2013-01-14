#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lcs.h"

#define printlistC(list,n) \
do { \
	int __list_counter; \
	for(__list_counter=0;__list_counter<n;__list_counter++) \
		printf("%c\t ",list[__list_counter]); \
	printf("\n"); \
} while(0)

int main(void)
{
	int MAXN = 10;
	int X[MAXN];
	int Y[MAXN];

	int i;
	srand(time(NULL));
	for(i=0; i< MAXN; i++){
		X[i] = 'A' + rand()%26;
		Y[i] = 'A' + rand()%26;
	}

	printf("The list->A is:\n");
	printlistC(X,MAXN);
	printf("The list->B is:\n");
	printlistC(Y,MAXN);
	
	struct Array2D * arr = lcs_length(X, MAXN, Y, MAXN);
	
	Stack * s = createStack(100);	
	lcs_backtrack(s, arr, X, Y, MAXN, MAXN);

	printf("the largest common sequence is : \n");
	void * v;
	while((v=top(s))!=NULL) {
		int e = (int)v;
		printf("%c->", (char)e);
		pop(s);
	}

	printf("\n");
	exit(0);		
}
