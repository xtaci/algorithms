#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sha1.h" 

#define TESTA   "abc\n"

int main(void)
{
	SHA1Context sha;

	sha1_reset(&sha);
	sha1_input(&sha, (const unsigned char *) TESTA, strlen(TESTA));

	if (sha1_final(&sha))
    {
        printf("sha %s --> ", TESTA);
		int i;
        for(i = 0; i < 5 ; i++)
        {
            printf("%x", sha.digest[i]);
        }
        printf("\n");
    }

	return 0;
}
