#include <iostream>
#include "base64.h"
#include <string.h>

using namespace std;

int main() {
	const char *s = "Matthew 7:24-27 Therefore everyone who hears these words of mine and puts them into practice is like a wise man who built his house on the rock. 25 The rain came down, the streams rose, and the winds blew and beat against that house; yet it did not fall, because it had its foundation on the rock. 26 But everyone who hears these words of mine and does not put them into practice is like a foolish man who built his house on sand. 27 The rain came down, the streams rose, and the winds blew and beat against that house, and it fell with a great crash.";
	cout << " INPUT: " << endl;
	cout << s << endl << endl;

	string base=alg::CBase64::encodeBase64((unsigned char *) s, strlen(s));
	cout << " encodeBase64: " << endl;
	cout << base << endl << endl;

	cout << " decodeBase64: " << endl;
	cout << alg::CBase64::decodeBase64(base) << endl;
}
