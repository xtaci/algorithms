#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;

ll fastExpo(int x,int n)
{	
	if (n==0) return 1;
	if (n & 1)
		return fastExpo(x,n-1) *  x;
	int y = fastExpo(x,n/2);
	return y*y;
}

int main()
{
	int base,power;
	cin>>base>>power;
	cout<<fastExpo(base,power)<<endl;

	return 0;
}