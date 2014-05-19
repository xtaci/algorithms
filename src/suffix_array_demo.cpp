#include <iostream>
#include <string>
#include <math.h>

#include "suffix_array.h"

using namespace std;
using namespace alg;

void print(string::iterator b, string::iterator e) {
	for(auto it=b;it!=e;++it) cout<<*it;
}

int main()
{
	string str;
	while(cin>>str) {
		SuffixArray sa(str);
		cout<<endl;
		cout<<"sorted suffixs are:"<<endl;
		for(size_t i=0;i<str.size();i++) {
			print(str.begin()+sa[i], str.end());
			cout<<endl;
		}
		cout<<endl;
		cout<<"The length of the longest common prefix of two suffixs ";
		int i=rand()%str.size();
		int j=rand()%str.size();
		print(str.begin()+i,str.end());
		cout<<" and ";
		print(str.begin()+j,str.end());
		cout<<" is ";
		cout<<sa.lcp_length(i,j)<<endl;
		cout<<endl;
	}
	return 0;
}
