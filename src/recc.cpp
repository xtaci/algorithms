#include<iostream>
using namespace std;

int rec(int n)
{
	if(n<=0)
		return 0;
	rec(n-1);
	cout<<n;
		
	}

int main()
{	
	int n;
	cout<<"enter numner: ";
	cin >> n;
	rec(n);
}