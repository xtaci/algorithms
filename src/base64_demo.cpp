#include <iostream>
#include "base64.h"
#include <string.h>

using namespace std;

int main() {
	const char *s="Man is distinguished not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure..";

	cout << " INPUT: " << endl;
	cout << s << endl << endl;

	string base=alg::CBase64::encodeBase64((unsigned char *) s, strlen(s));
	cout << " encodeBase64: " << endl;
	cout << base << endl << endl;

	cout << " decodeBase64: " << endl;
	cout << alg::CBase64::decodeBase64(base) << endl;
}
