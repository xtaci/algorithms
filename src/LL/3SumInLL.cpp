#include<iostream>
#include<list>
#include<algorithm>
using namespace std;
void threeSum(list<int>&l1,list<int>&l2,list<int>&l3,int k);
int main()
{
	list<int>l1,l2,l3;
	
	l1.push_back(12);
	l1.push_back(6);
	l1.push_back(29);
	
	l2.push_back(23);
	l2.push_back(5);
	l2.push_back(8);
	
	l3.push_back(90);
	l3.push_back(20);
	l3.push_back(59);
	
	int x;
	cout<<"enter sum value"<<endl;
	cin>>x;
	threeSum(l1,l2,l3,x);
}
void threeSum(list<int>&l1,list<int>&l2,list<int>&l3,int k)
{
	l2.sort();
	l3.sort();
	l3.reverse();
	list<int>::iterator i1,i2,i3;
	i1=l1.begin();
	while(i1!=l1.end())
	{
		i2=l2.begin();
		i3=l3.begin();
		while(i2!=l2.end()&&i3!=l3.end())
		{
			if(*i1+*i2+*i3==k)
			{
				cout<<*i1<<" "<<*i2<<" "<<*i3;
				return;
			}
			else if(*i1+*i2+*i3<k)
				i2++;
			else
				i3++;		
		}
		i1++;
	}
	cout<<"no triplet exists";
}


