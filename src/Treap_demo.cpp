#include <algorithm>
#include "../include/Treap.h"
using namespace std;
using namespace alg;

int main()
{
	Treap < int > T;
	Treap < int > T2;
	string str;

	T.push_back( 1 );
	T.push_back( 2 );
	T.push_back( 3 );
	T.push_back( 4 );
	T.push_back( 6 );
	T.push_back( 7 );
	T.push_back( 8 );
	T.push_back( 9 );
	T.insert(5,5);

	T2 = T;

	Treap < int > T3 = T2.get( 5 , 8 );

	Treap < int > T4 = T3.get(2,3);

	cout << T4 << endl;

	T4.set(2,5);

	cout << T4 << endl;

	return 0;
}