/*******************************************
 * DANIEL'S PRIVATE ALGORITHM IMPLEMENTAIONS
 * Prime Sieve of Eratosthenes 
 * Features:
 * 1. find the largest prime below given - maxn
 *******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
 
#define GET(b) ((sieve[(b)>>5]>>((b)&31))&1)
 
inline int isprime(uint32_t  * sieve, int p) { return p==2 || (p>2 && (p&1)==1 && (GET((p-1)>>1)==0)); }

int prime(int maxn)
{
	uint32_t * sieve;
	float MAXN = maxn;
	uint32_t P1 = ceil(MAXN/64); 
	uint32_t P2 = ceil(MAXN/2);
	uint32_t P3 = ceil(ceil(sqrt(MAXN))/2);

	sieve = (uint32_t *) malloc(sizeof(uint32_t) * P1);
	memset(sieve, 0, sizeof(uint32_t) * P1);

	// sieve
	uint32_t i, j, k;
	for (k = 1; k <= P3; k++)
		if (GET(k)==0) for(j=2*k+1,i=2*k*(k+1);i<P2;i+=j) sieve[i>>5]|=1<<(i&31);

	// get the largest prime
	int result = -1;
	int r;
	for (r = maxn; r >=0; r--) {
		if(isprime(sieve, r)) { result = r; break;}
	}

	free(sieve);
	return result;
}
 
int main()
{
	int maxn = 100;
    printf("The largest prime below %d is %d.\n", maxn,prime(maxn));
	maxn = 500;
    printf("The largest prime below %d is %d.\n", maxn,prime(maxn));
	maxn = 1000;
    printf("The largest prime below %d is %d.\n", maxn,prime(maxn));
    return 0;
}
