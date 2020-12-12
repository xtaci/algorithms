#include<bits/stdc++.h>
using namespace std;

int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		string s;
		cin>>s;
		if(s.length()>10)
			cout<<s.at(0)<<s.length()-2<<s.at((s.length()-1));
		else cout<<s;
	}
	

}