#include<bits/stdc++.h>
using namespace std;

int main()
{
	int n, k, x,counter=0;
	cin>>n>>k;
	int a[n];
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	
	// reverse(a, a + (n-1)); 
	for(int j=0;j<n;j++)
	{
		x=a[k-1];

		if(a[j]>=x)
		{   if(a[j]<=0)
			break;
			counter++;
		}
	}
	
		cout<<counter;
	


		// 10 9 8 7 7 7 5 5

}