#include <stdio.h>
#include <stdlib.h>
#include "integer.h"
using namespace alg;

int main(void)
{
	Integer a = Integer::from_string("1234567890");
	Integer b = Integer::from_string("9876543210");

	Integer c = a+b;

	printf("%s + %s = %s\n", a.to_string(), b.to_string(), c.to_string());
	printf("%s - %s = %s\n", a.to_string(), b.to_string(), (a-b).to_string());
	printf("%s - %s = %s\n", b.to_string(), a.to_string(), (b-a).to_string());

	printf("%s %% 50 = %d\n", a.to_string(), a%50);
	printf("%s / 10 = %s\n", a.to_string(), (a/10).to_string());
	printf("%s * 50 = %s\n", a.to_string(), (a*50).to_string());
	printf("%s * %s = %s\n", a.to_string(), b.to_string(), (a*b).to_string());

	return 0;
}
