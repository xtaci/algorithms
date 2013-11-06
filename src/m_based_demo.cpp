#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "imath.h"
#include "prime.h"

using namespace alg;
int main()
{
	uint32_t k[KLEN];

	int i;
	int m;	

	for(i=9;;i+=2)
	{
		if (is_prime(i))
		{
			m=i;
			break;
		}
	}
	srand(time(NULL));
	int key = rand()%1000;
	m_based(key, m , k);
	printf("turning %d into %d-based number:\n", key, m);
	for (i=0;i < KLEN;i++)
	{
		printf("k[%d] = %d\n",i,k[i]);
	}
}
