#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lcs.h"
#include "stack.h"

#define printlistC(list,n) \
do { \
	int list_counter_; \
	for(list_counter_=0;list_counter_<n;list_counter_++) \
		printf("%c\t ",list[list_counter_]); \
	printf("\n"); \
} while(0)

int main(void)
{
	using namespace alg;
	const int MAXN = 10;
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
	
	Array2D<uint32_t> * A = lcs_length(X, MAXN, Y, MAXN);
	
	Stack<int> S(100);	
	lcs_backtrack(S, *A, X, Y, MAXN, MAXN);

	printf("the largest common sequence is : \n");
	while(!S.is_empty()) {
		int e = S.top();
		printf("%c->", (char)e);
		S.pop();
	}

	delete A;

	printf("\n");
	return 0;		
}
