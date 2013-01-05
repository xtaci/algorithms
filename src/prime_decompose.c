#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
 
typedef uint32_t pint;
typedef uint64_t xint;
typedef unsigned int uint;
#define PRIuPINT PRIu32		/* printf macro for pint */
#define PRIuXINT PRIu64		/* printf macro for xint */
#define MAX_FACTORS 63		/* because 2^64 is too large for xint */
 
uint8_t *pbits;
 
#define MAX_PRIME (~(pint)0)
#define MAX_PRIME_SQ 65535U
#define PBITS (MAX_PRIME / 30 + 1)
 
pint next_prime(pint);
int is_prime(xint);
void sieve(pint);
 
uint8_t bit_pos[30] = {
	0, 1<<0, 0, 0, 0,    0,
	0, 1<<1, 0, 0, 0, 1<<2,
	0, 1<<3, 0, 0, 0, 1<<4,
	0, 1<<5, 0, 0, 0, 1<<6,
	0,    0, 0, 0, 0, 1<<7,
};
 
uint8_t rem_num[] = { 1, 7, 11, 13, 17, 19, 23, 29 };
 
void init_primes()
{
	FILE *fp;
	pint s, tgt = 4;
 
	if (!(pbits = malloc(PBITS))) {
		perror("malloc");
		exit(1);
	}
 
	if ((fp = fopen("primebits", "r"))) {
		fread(pbits, 1, PBITS, fp);
		fclose(fp);
		return;
	}
 
	memset(pbits, 255, PBITS);
	for (s = 7; s <= MAX_PRIME_SQ; s = next_prime(s)) {
		if (s > tgt) {
			tgt *= 2;
			fprintf(stderr, "sieve %"PRIuPINT"\n", s);
		}
		sieve(s);
	}
	fp = fopen("primebits", "w");
	fwrite(pbits, 1, PBITS, fp);
	fclose(fp);
}
 
int is_prime(xint x)
{
	pint p;
	if (x > 5) {
		if (x < MAX_PRIME)
			return pbits[x/30] & bit_pos[x % 30];
 
		for (p = 2; p && (xint)p * p <= x; p = next_prime(p))
			if (x % p == 0) return 0;
 
		return 1;
	}
	return x == 2 || x == 3 || x == 5;
}
 
void sieve(pint p)
{
	unsigned char b[8];
	off_t ofs[8];
	int i, q;
 
	for (i = 0; i < 8; i++) {
		q = rem_num[i] * p;
		b[i] = ~bit_pos[q % 30];
		ofs[i] = q / 30;
	}
 
	for (q = ofs[1], i = 7; i; i--)
		ofs[i] -= ofs[i-1];
 
	for (ofs[0] = p, i = 1; i < 8; i++)
		ofs[0] -= ofs[i];
 
	for (i = 1; q < PBITS; q += ofs[i = (i + 1) & 7])
		pbits[q] &= b[i];
}
 
pint next_prime(pint p)
{
	off_t addr;
	uint8_t bits, rem;
 
	if (p > 5) {
		addr = p / 30;
		bits = bit_pos[ p % 30 ] << 1;
		for (rem = 0; (1 << rem) < bits; rem++);
		while (pbits[addr] < bits || !bits) {
			if (++addr >= PBITS) return 0;
			bits = 1;
			rem = 0;
		}
		if (addr >= PBITS) return 0;
		while (!(pbits[addr] & bits)) {
			rem++;
			bits <<= 1;
		}
		return p = addr * 30 + rem_num[rem];
	}
 
	switch(p) {
		case 2: return 3;
		case 3: return 5;
		case 5: return 7;
	}
	return 2;
}
 
int decompose(xint n, xint *f)
{
	pint p = 0;
	int i = 0;
 
	/* check small primes: not strictly necessary */
	if (n <= MAX_PRIME && is_prime(n)) {
		f[0] = n;
		return 1;
	}
 
	while (n >= (xint)p * p) {
		if (!(p = next_prime(p))) break;
		while (n % p == 0) {
			n /= p;
			f[i++] = p;
		}
	}
	if (n > 1) f[i++] = n;
	return i;
}
 
int main()
{
	int i, len;
	pint p = 0;
	xint f[MAX_FACTORS], po;
 
	init_primes();
 
	for (p = 1; p < 64; p++) {
		po = (1LLU << p) - 1;
		printf("2^%"PRIuPINT" - 1 = %"PRIuXINT, p, po);
		fflush(stdout);
		if ((len = decompose(po, f)) > 1)
			for (i = 0; i < len; i++)
				printf(" %c %"PRIuXINT, i?'x':'=', f[i]);
		putchar('\n');
	}
 
	return 0;
}
