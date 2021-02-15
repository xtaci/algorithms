#include<iostream>
#include<list>
using namespace std;
class node{
	public:
		int first;
		int second;
};
int main()
{
	list<node>l;
	node node1;
	node1.first=1;
	node1.second=5;
	l.push_back(node1);
	cout<< float((*l.begin()).second);
	
}

