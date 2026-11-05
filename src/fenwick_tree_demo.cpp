#include <cstdio>
#include "fenwick_tree.h"

int main()
{
	Fenwick ft(5);

	ft.update(2, 1);
	ft.update(4, 10);

	printf("%d\n", ft.rsq(1));

	ft.update(1, 5);	
	printf("%d\n", ft.rsq(1));
	return 0;
}